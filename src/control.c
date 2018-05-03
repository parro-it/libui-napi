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
	clear_children(handle);

	DEBUG_F("Control %p destroyed.", handle);
	if (handle->is_garbage_collected) {
		free(handle->children);
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
	handle->env = env;
	handle->events = calloc(1, sizeof(struct events_list));
	handle->children = calloc(1, sizeof(struct children_list));
	handle->control = control;
	handle->original_destroy = control->Destroy;
	control->Destroy = control_on_destroy;
	ctrl_map_insert(&controls_map, handle, control);
	DEBUG_F("Control %p created.", handle);

	napi_value handle_external;
	napi_status status = napi_create_external(env, handle, on_control_gc, NULL, &handle_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	handle->external = handle_external;

	return handle_external;
}

napi_value add_child(struct control_handle *control, struct control_handle *child) {
	napi_env env = control->env;

	struct children_node *new_node = malloc(sizeof(struct children_node));
	new_node->next = NULL;
	new_node->handle = child;

	napi_status status = napi_create_reference(env, child->external, 1, &(new_node->ctrl_ref));
	CHECK_STATUS_THROW(status, napi_create_reference);

	if (control->children->children_head == NULL) {
		// First child for this control
		control->children->children_head = new_node;
		control->children->children_tail = new_node;
		return NULL;
	}

	// Control already has other children. Append to tail
	control->children->children_tail->next = new_node;

	// set this node as the new tail
	control->children->children_tail = new_node;

	return NULL;
}


napi_value clear_children(struct control_handle *control) {
	if (control->children->children_head == NULL) {
		// This control has no events
		return NULL;
	}

	napi_env env = control->env;

	struct children_node *node = control->children->children_head;
	struct children_node *node_to_free;

	while (node != NULL) {
		uint32_t new_ref_count;
		napi_status status = napi_reference_unref(
			env,
			node->ctrl_ref,
			&new_ref_count
		);
		DEBUG_F("new reference count for %p: %d", node->handle, new_ref_count);
		CHECK_STATUS_THROW(status, napi_reference_unref);

		node_to_free = node;
		node = node->next;
		free(node_to_free);
	}

	control->children->children_head = NULL;
	control->children->children_tail = NULL;

	return NULL;
}
