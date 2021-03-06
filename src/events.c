#include "events.h"

#if UI_NODE_DEBUG
static const char *MODULE = "EventsInternal";
#endif

napi_value fire_event_args_unscoped(struct event_t *event, int argc, napi_value *argv) {
	if (event->is_empty) {
		return NULL;
	}

	napi_status status;
	napi_env env = event->env;

	napi_value resource_object;
	status = napi_create_object(env, &resource_object);
	CHECK_STATUS_UNCAUGHT(status, napi_create_object, NULL);

	napi_value cb;
	status = napi_get_reference_value(env, event->cb_ref, &cb);
	CHECK_STATUS_UNCAUGHT(status, napi_get_reference_value, NULL);

	LIBUI_NODE_DEBUG_F("Firing event %s %p", event->name, event);

	napi_value result;
	status = napi_make_callback(env, event->context, resource_object, cb, argc, argv, &result);

	if (status == napi_pending_exception) {
		napi_value last_exception;
		napi_get_and_clear_last_exception(env, &last_exception);
		napi_fatal_exception(env, last_exception);
		return NULL;
	}

	CHECK_STATUS_UNCAUGHT(status, napi_make_callback, NULL);

	return result;
}

napi_value fire_event_args(struct event_t *event, int argc, napi_value *argv) {
	napi_status status;
	napi_env env = event->env;

	napi_handle_scope handle_scope;
	status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, NULL);

	napi_value result = fire_event_args_unscoped(event, argc, argv);

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, NULL);

	return result;
}

napi_value fire_event(struct event_t *event) {
	return fire_event_args(event, 0, NULL);
};

struct event_t *create_event(napi_env env, napi_ref cb_ref, const char *name) {
	napi_status status;

	napi_value async_resource_name;
	status = napi_create_string_utf8(env, name, NAPI_AUTO_LENGTH, &async_resource_name);
	CHECK_STATUS_THROW(status, napi_create_string_utf8);

	napi_async_context async_context;
	if (cb_ref != null_ref) {
		status = napi_async_init(env, NULL, async_resource_name, &async_context);
		CHECK_STATUS_THROW(status, napi_async_init);
	} else {
		async_context = NULL;
	}

	struct event_t *event = calloc(1, sizeof(struct event_t));
	event->cb_ref = cb_ref;
	event->name = name;
	event->env = env;
	event->context = async_context;
	if (cb_ref == null_ref) {
		event->is_empty = true;
	}
	LIBUI_NODE_DEBUG_F("Create event %s %p", event->name, event);
	return event;
}

napi_value clear_event(struct event_t *event) {
	uint32_t new_ref_count;
	napi_env env = event->env;

	napi_status status = napi_reference_unref(env, event->cb_ref, &new_ref_count);
	CHECK_STATUS_THROW(status, napi_reference_unref);

	free(event);

	LIBUI_NODE_DEBUG_F("Destroy event %s %p", event->name, event);
	return NULL;
}

static struct events_node *new_events_node(struct event_t *event) {
	struct events_node *new_node = malloc(sizeof(struct events_node));
	new_node->next = NULL;
	new_node->event = event;
	return new_node;
}

void install_event(struct events_list *events, struct event_t *event) {
	struct events_node *new_node = NULL;
	if (!event->is_empty) {
		new_node = new_events_node(event);
	}

	if (events->head == NULL) {
		// First event for this control
		events->head = new_node;
		events->tail = new_node;
		return;
	}

	if (event->name == events->head->event->name) {
		clear_event(events->head->event);
		struct events_node *new_head = events->head->next;
		free(events->head);
		events->head = new_head;

		if (events->head == NULL) {
			// The only event got removed
			events->head = new_node;
			events->tail = new_node;
			return;
		}
	} else {
		struct events_node *current = events->head->next;
		struct events_node *previous = events->head;

		while (current != NULL && previous != NULL) {
			if (event->name == current->event->name) {
				previous->next = current->next;
				clear_event(current->event);
				free(current);
				if (previous->next == NULL) {
					events->tail = previous;
				}
				break;
			}
			previous = current;
			current = current->next;
		}
	}

	if (new_node != NULL) {
		// Control already has other events. Append to tail
		events->tail->next = new_node;
		// and set this node as the new tail
		events->tail = new_node;
	}
}

void clear_all_events(struct events_list *events) {
	if (events->head == NULL) {
		// This control has no events
		return;
	}

	struct events_node *node = events->head;
	struct events_node *node_to_free;

	while (node != NULL) {
		clear_event(node->event);
		node_to_free = node;
		node = node->next;
		free(node_to_free);
	}

	events->head = NULL;
	events->tail = NULL;
}
