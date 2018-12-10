#include "control.h"
#include <assert.h>
#include "napi_utils.h"
#include "events.h"

struct ctrl_map controls_map;

#if UI_NODE_DEBUG
static const char *MODULE = "ControlInternal";
#endif

int control_event_cb(void *ctrl, void *data) {
	struct event_t *event = (struct event_t *)data;
	fire_event(event);
	return 0;
}

void control_on_destroy(uiControl *control) {
	LIBUI_NODE_DEBUG("A control is destroying.");

	struct control_handle *handle;
	ctrl_map_get(&controls_map, control, &handle);
	LIBUI_NODE_DEBUG_F("Control %s %p destroying.", handle->ctrl_type_name, handle);

	handle->original_destroy(control);
	ctrl_map_remove(&controls_map, control);
	clear_all_events(handle->events);

	clear_children(handle->env, handle->children);

	LIBUI_NODE_DEBUG_F("Control %s %p destroyed.", handle->ctrl_type_name, handle);
	handle->is_destroyed = true;
}

static void on_control_gc(napi_env env, void *finalize_data, void *finalize_hint) {
	struct control_handle *handle = (struct control_handle *)finalize_data;
	LIBUI_NODE_DEBUG_F("Control %s %p garbage collected.", handle->ctrl_type_name, handle);

	free(handle->children);
	free(handle->events);
	LIBUI_NODE_DEBUG_F("%s %p handle freed.", handle->ctrl_type_name, handle);
	handle->ctrl_type_name = NULL;
	free(handle);
}

napi_value control_handle_new(napi_env env, uiControl *control, const char *ctrl_type_name) {
	// printf("on creation %p\n", control->Parent(control));

	struct control_handle *handle = calloc(1, sizeof(struct control_handle));
	handle->env = env;
	handle->events = calloc(1, sizeof(struct events_list));
	handle->children = create_children_list();
	handle->control = control;
	handle->ctrl_type_name = ctrl_type_name;
	handle->original_destroy = control->Destroy;
	control->Destroy = control_on_destroy;
	ctrl_map_insert(&controls_map, handle, control);
	LIBUI_NODE_DEBUG_F("%s %p created.", handle->ctrl_type_name, handle);

	napi_value handle_external;
	napi_status status = napi_create_external(env, handle, on_control_gc, NULL, &handle_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	napi_ref ctrl_ref = NULL;

	status = napi_create_reference(env, handle_external, 0, &ctrl_ref);
	handle->ctrl_ref = ctrl_ref;
	CHECK_STATUS_THROW(status, napi_create_reference);

	return handle_external;
}
