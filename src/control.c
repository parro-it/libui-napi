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
	handle->events = calloc(1, sizeof(struct events_list));
	handle->children = calloc(1, sizeof(struct children_list));
	handle->control = control;
	handle->original_destroy = control->Destroy;
	control->Destroy = control_on_destroy;
	ctrl_map_insert(&controls_map, handle, control);
	DEBUG_F("Control %p created.", handle);
	RETURN_EXTERNAL(handle, on_control_gc)
}

static struct children_node *new_child_node(struct control_handle *handle) {
	struct children_node *new_node = malloc(sizeof(struct children_node));
	new_node->next = NULL;
	new_node->handle = handle;
	return new_node;
}

void add_child(struct control_handle *control, struct control_handle *child) {
	if (control->children->children_head == NULL) {
		// First child for this control
		struct children_node *new_node = new_child_node(control);
		control->children->children_head = new_node;
		control->children->children_tail = new_node;
		return;
	}

	// TODO: add a reference to child control to
	// avoid it being GCed

	// Control already has other children. Append to tail
	struct children_node *new_node = new_child_node(child);
	control->children->children_tail->next = new_node;

	// set this node as the new tail
	control->children->children_tail = new_node;
}

void clear_control(struct control_handle *control) {
	// TODO: release reference to child control to
	// allow ii being GCed
}

void clear_children(struct control_handle *control) {
	if (control->children->children_head == NULL) {
		// This control has no events
		return;
	}

	struct children_node *node = control->children->children_head;
	struct children_node *node_to_free;

	while (node != NULL) {
		clear_control(node->handle);
		node_to_free = node;
		node = node->next;
		free(node_to_free);
	}

	control->children->children_head = NULL;
	control->children->children_tail = NULL;
}
