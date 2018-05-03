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
	clear_children(handle->env, handle->children);

	DEBUG_F("Control %s %p destroyed.", handle->ctrl_type_name, handle);
	if (handle->is_garbage_collected) {
		free(handle->children);
		free(handle->events);
		free(handle);
		DEBUG_F("%s %p handle freed.", handle->ctrl_type_name, handle);
	} else {
		handle->is_destroyed = true;
	}
}

static void on_control_gc(napi_env env, void* finalize_data, void* finalize_hint) {
	struct control_handle *handle = (struct control_handle *) finalize_data;
	DEBUG_F("Control %s %p garbage collected.", handle->ctrl_type_name, handle);

	if (handle->is_destroyed) {
		free(handle->children);
		free(handle->events);
		free(handle);
		DEBUG_F("%s %p handle freed.", handle->ctrl_type_name, handle);
	} else {
		handle->is_garbage_collected = true;
	}
}

napi_value control_handle_new(napi_env env, uiControl *control, const char* ctrl_type_name) {
	struct control_handle *handle = calloc(1, sizeof(struct control_handle));
	handle->env = env;
	handle->events = calloc(1, sizeof(struct events_list));
	handle->children = calloc(1, sizeof(struct children_list));
	handle->control = control;
	handle->ctrl_type_name = ctrl_type_name;
	handle->original_destroy = control->Destroy;
	control->Destroy = control_on_destroy;
	ctrl_map_insert(&controls_map, handle, control);
	DEBUG_F("%s %p created.", handle->ctrl_type_name, handle);

	napi_value handle_external;
	napi_status status = napi_create_external(env, handle, on_control_gc, NULL, &handle_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	handle->external = handle_external;

	return handle_external;
}

napi_value add_child(napi_env env, struct children_list *list, struct control_handle *child) {

	struct children_node *new_node = malloc(sizeof(struct children_node));
	new_node->next = NULL;
	new_node->handle = child;

	napi_status status = napi_create_reference(env, child->external, 1, &(new_node->ctrl_ref));
	CHECK_STATUS_THROW(status, napi_create_reference);

	if (list->head == NULL) {
		// First child for this control
		list->head = new_node;
		list->tail = new_node;
		return NULL;
	}

	// Control already has other children. Append to tail
	list->tail->next = new_node;

	// set this node as the new tail
	list->tail = new_node;

	return NULL;
}


napi_value clear_children(napi_env env, struct children_list *list) {
	if (list->head == NULL) {
		// This control has no events
		return NULL;
	}

	struct children_node *node = list->head;
	struct children_node *node_to_free;

	while (node != NULL) {
		uint32_t new_ref_count;
		napi_status status = napi_reference_unref(
			env,
			node->ctrl_ref,
			&new_ref_count
		);
		CHECK_STATUS_THROW(status, napi_reference_unref);
		DEBUG_F("new reference count for %p: %d", node->handle, new_ref_count);

		node_to_free = node;
		node = node->next;
		free(node_to_free);
	}

	list->head = NULL;
	list->tail = NULL;

	return NULL;
}
