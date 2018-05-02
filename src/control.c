#include "control.h"
#include "events.h"

struct ctrl_map controls_map;

static void window_on_destroy(uiControl *control) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, control, &handle);
	handle->original_destroy(control);
	ctrl_map_remove(&controls_map, control);
	clear_all_events(handle->events);
	if (handle->is_garbage_collected) {
		free(handle->events);
		free(handle);
	} else {
		handle->is_destroyed = true;
	}
}

static void on_window_collected(napi_env env, void* finalize_data, void* finalize_hint) {
	struct control_handle *handle = (struct control_handle *) finalize_data;
	if (handle->is_destroyed) {
		free(handle->events);
		free(handle);
	} else {
		handle->is_garbage_collected = true;
	}
}

napi_value control_handle_new(napi_env env, uiControl *control) {
	struct control_handle *handle = calloc(1, sizeof(struct control_handle));
	handle->events = calloc(1, sizeof(struct events_list));
	handle->control = control;
	handle->original_destroy = control->Destroy;
	control->Destroy = window_on_destroy;
	ctrl_map_insert(&controls_map, handle, control);
	RETURN_EXTERNAL(handle, on_window_collected)
}
