#include "control.h"
#include "tests.h"

void control_on_destroy(uiControl *control);
static const char *ctrl_type_name = "name_test";
static bool destroy_cb_called = false;

void original_destroy_cb(uiControl *control) {
	destroy_cb_called = true;
}

static struct control_handle *get_control(napi_env env) {
	uiControl *ctrl = malloc(sizeof(uiControl));
	ctrl->Destroy = original_destroy_cb;
	napi_value control_value = control_handle_new(env, ctrl, ctrl_type_name);
	struct control_handle *control;
	napi_get_value_external(env, control_value, (void **)&control);
	control->original_destroy = original_destroy_cb;
	return control;
}

static void control_on_destroy_remove_ctrl_from_map(napi_env env) {
	struct control_handle *handle = get_control(env);
	struct control_handle *check_handle = NULL;

	ctrl_map_insert(&controls_map, handle, handle->control);
	ctrl_map_get(&controls_map, handle->control, &check_handle);
	assert(handle != NULL);

	control_on_destroy(handle->control);

	check_handle = NULL;
	ctrl_map_get(&controls_map, handle->control, &check_handle);
	assert(check_handle == NULL);
}

static void control_on_destroy_calls_original_destroy(napi_env env) {
	struct control_handle *handle = get_control(env);
	ctrl_map_insert(&controls_map, handle, handle->control);
	destroy_cb_called = false;
	control_on_destroy(handle->control);
	assert(destroy_cb_called);
}

void control_on_destroy_suite(napi_env env) {
	SUITE();
	RUN_TEST(control_on_destroy_remove_ctrl_from_map);
	RUN_TEST(control_on_destroy_calls_original_destroy);
}
