#include <assert.h>
#include <stdlib.h>
#include <ui.h>
#include "control.h"
#include "tests.h"

static struct control_handle *get_child(napi_env env) {
	uiControl *ctrl = calloc(1, sizeof(uiControl));
	napi_value child_value = control_handle_new(env, ctrl, "name_test");
	struct control_handle *child;
	napi_get_value_external(env, child_value, (void **)&child);
	return child;
}

static void test_add_child_return_napi_ok_on_success(napi_env env) {
	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);
	napi_status ret = add_child(env, list, child);
	assert(ret == napi_ok);
}

static void test_add_child_set_head_tail_on_success(napi_env env) {

	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);
	napi_status ret = add_child(env, list, child);

	assert(ret == napi_ok);

	assert(list->head != NULL);
	assert(list->head == list->tail);
}

static void test_add_child_next_null_on_success(napi_env env) {

	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);
	napi_status ret = add_child(env, list, child);

	assert(ret == napi_ok);

	assert(list->head->next == NULL);
}

static void test_add_child_handle_set_on_success(napi_env env) {

	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);
	napi_status ret = add_child(env, list, child);

	assert(ret == napi_ok);

	assert(list->head->handle == child);
}

static void test_add_two_child_set_head_tail(napi_env env) {
	struct children_list *list = create_children_list();
	struct control_handle *child1 = get_child(env);
	struct control_handle *child2 = get_child(env);
	napi_status ret = add_child(env, list, child1);
	assert(ret == napi_ok);

	ret = add_child(env, list, child2);
	assert(ret == napi_ok);

	assert(list->head->handle == child1);
	assert(list->tail->handle == child2);
	assert(list->head->next == list->tail);
	assert(list->tail->next == NULL);
}

static void test_add_child_has_refcount_1(napi_env env) {
	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);

	uint32_t ref_count;
	napi_reference_ref(env, child->ctrl_ref, &ref_count);
	assert(ref_count == 1);
	napi_reference_unref(env, child->ctrl_ref, &ref_count);
	assert(ref_count == 0);

	napi_status ret = add_child(env, list, child);

	assert(ret == napi_ok);

	napi_reference_unref(env, child->ctrl_ref, &ref_count);
	assert(ref_count == 0);
}

void children_list_add_child_suite(napi_env env) {
	RUN_TEST(test_add_child_return_napi_ok_on_success);
	RUN_TEST(test_add_child_set_head_tail_on_success);
	RUN_TEST(test_add_child_next_null_on_success);
	RUN_TEST(test_add_child_handle_set_on_success);
	RUN_TEST(test_add_two_child_set_head_tail);
	RUN_TEST(test_add_child_has_refcount_1);
}
