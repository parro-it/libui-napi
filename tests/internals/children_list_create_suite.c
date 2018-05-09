#include <assert.h>
#include <stdlib.h>
#include "control.h"
#include "tests.h"

static const char *ctrl_type_name = "name_test";
static destroy_cb fake_destroy;

static void test_create_node(napi_env env) {
	struct control_handle *child = malloc(sizeof(struct control_handle));
	struct children_node *node = create_node(child);
	assert(node != NULL);
	assert(node->handle == child);
	assert(node->next == NULL);
	free(node);
	free(child);
}

static void test_create_children_list(napi_env env) {
	struct children_list *list = create_children_list();
	assert(list != NULL);
	assert(list->head == NULL);
	assert(list->tail == NULL);
	free(list);
}

static struct control_handle *get_control(napi_env env) {
	uiControl *ctrl = malloc(sizeof(uiControl));
	ctrl->Destroy = fake_destroy;
	napi_value control_value = control_handle_new(env, ctrl, ctrl_type_name);
	struct control_handle *control;
	napi_get_value_external(env, control_value, (void **)&control);
	return control;
}

static void control_handle_new_has_refcount_0(napi_env env) {
	struct control_handle *control = get_control(env);
	uint32_t ref_count;
	napi_reference_ref(env, control->ctrl_ref, &ref_count);
	assert(ref_count == 1);

	free(control);
}

static void control_handle_new_insert_in_map(napi_env env) {
	struct control_handle *handle = get_control(env);
	struct control_handle *saved_handle;
	ctrl_map_get(&controls_map, handle->control, &saved_handle);
	assert(saved_handle == handle);

	free(handle);
}

static void control_handle_new_set_members(napi_env env) {
	struct control_handle *handle = get_control(env);
	assert(handle->env == env);
	assert(handle->children != NULL);
	assert(handle->events != NULL);
	assert(handle->control != NULL);
	assert(handle->ctrl_type_name == ctrl_type_name);
	assert(handle->original_destroy == fake_destroy);
	assert(handle->control->Destroy != NULL);
	free(handle);
}

static void control_handle_new_return_non_null_on_success(napi_env env) {
	uiControl *ctrl = malloc(sizeof(uiControl));
	napi_value result = control_handle_new(env, ctrl, "name_test");
	assert(result != NULL);
}

void children_list_create_suite(napi_env env) {
	fake_destroy = malloc(1);

	RUN_TEST(test_create_node);
	RUN_TEST(control_handle_new_return_non_null_on_success);
	RUN_TEST(control_handle_new_insert_in_map);
	RUN_TEST(control_handle_new_has_refcount_0);
	RUN_TEST(control_handle_new_set_members);
	RUN_TEST(test_create_children_list);
}
