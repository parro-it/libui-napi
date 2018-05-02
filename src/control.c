#include "napi_utils.h"
#include "control.h"
#include "events.h"

struct ctrl_map controls_map;

static void control_on_destroy(uiControl *control) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, control, &handle);
	handle->original_destroy(control);
	ctrl_map_remove(&controls_map, control);
	clear_all_events(handle->events);
	DEBUG_F("Control %p destroyed.", handle);
	if (handle->is_garbage_collected) {
		free(handle->events);
		free(handle);
		DEBUG_F("Control %p freed.", handle);
	} else {
		handle->is_destroyed = true;
	}
}

static void on_control_gc(napi_env env, void* finalize_data, void* finalize_hint) {
	struct control_handle *handle = (struct control_handle *) finalize_data;
	DEBUG_F("Control %p garbage collected.", handle);

	if (handle->is_destroyed) {
		free(handle->events);
		free(handle);
		DEBUG_F("Control %p freed.", handle);
	} else {
		handle->is_garbage_collected = true;
	}
}

napi_value control_handle_new(napi_env env, uiControl *control) {
	struct control_handle *handle = calloc(1, sizeof(struct control_handle));
	handle->events = calloc(1, sizeof(struct events_list));
	handle->control = control;
	handle->original_destroy = control->Destroy;
	control->Destroy = control_on_destroy;
	ctrl_map_insert(&controls_map, handle, control);
	DEBUG_F("Control %p created.", handle);
	RETURN_EXTERNAL(handle, on_control_gc)
}

void add_child(struct control_handle *control, struct control_handle *child) {
	if (control->children_list->children_head == NULL) {
		// First child for this control
		struct events_node *new_node = new_events_node(event);
		events->events_head = new_node;
		events->events_tail = new_node;
		return;
	}

	// TODO: we need to remove existing events_node for the same event
	// and support NULL event to only remove event.

	// Control already has other events. Append to tail
	struct events_node *new_node = new_events_node(event);
	events->events_tail->next = new_node;

	// set this node as the new tail
	events->events_tail = new_node;
}

void clear_children(struct control_handle *control) {

}

void install_event(struct events_list *events, struct event_t *event) {

}


void clear_all_events(struct events_list *events) {
	if (events->events_head == NULL) {
		// This control has no events
		return;
	}

	struct events_node *node = events->events_head;
	struct events_node *node_to_free;

	while (node != NULL) {
		clear_event(node->event);
		node_to_free = node;
		node = node->next;
		free(node_to_free);
	}

	events->events_head = NULL;
	events->events_tail = NULL;
}
