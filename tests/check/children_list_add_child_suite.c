#include <assert.h>
#include <stdlib.h>
#include <ui.h>
#include "control.h"
#include "tests.h"

static struct control_handle *get_child(napi_env env) {
	uiControl *ctrl = malloc(sizeof(uiControl));
	napi_value child_value = control_handle_new(env, ctrl, "name_test");
	struct control_handle *child;
	napi_get_value_external(env, child_value, (void **)&child);
	return child;
}

static void test_add_child_return_null_on_success(napi_env env) {

	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);
	napi_value ret = add_child(env, list, child);

	assert(ret == NULL);

	free(child);
	free(list);
}

static void test_add_child_set_head_tail_on_success(napi_env env) {

	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);
	add_child(env, list, child);

	assert(list->head != NULL);
	assert(list->head == list->tail);

	free(child);
	free(list);
}

static void test_add_child_next_null_on_success(napi_env env) {

	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);
	add_child(env, list, child);

	assert(list->head->next == NULL);

	free(child);
	free(list);
}

static void test_add_child_handle_set_on_success(napi_env env) {

	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);
	add_child(env, list, child);

	assert(list->head->handle == child);

	free(child);
	free(list);
}

static void test_add_two_child_set_head_tail(napi_env env) {
	struct children_list *list = create_children_list();
	struct control_handle *child1 = get_child(env);
	struct control_handle *child2 = get_child(env);
	add_child(env, list, child1);
	add_child(env, list, child2);

	assert(list->head->handle == child1);
	assert(list->tail->handle == child2);
	assert(list->head->next == list->tail);
	assert(list->tail->next == NULL);

	free(child1);
	free(child2);
	free(list);
}

static void test_add_child_has_refcount_1(napi_env env) {
	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);

	uint32_t ref_count;
	napi_reference_ref(env, child->ctrl_ref, &ref_count);
	assert(ref_count == 1);
	napi_reference_unref(env, child->ctrl_ref, &ref_count);
	assert(ref_count == 0);

	add_child(env, list, child);

	napi_reference_unref(env, child->ctrl_ref, &ref_count);
	assert(ref_count == 0);

	free(child);
	free(list);
}

void children_list_add_child_suite(napi_env env) {
	RUN_TEST(test_add_child_return_null_on_success);
	RUN_TEST(test_add_child_set_head_tail_on_success);
	RUN_TEST(test_add_child_next_null_on_success);
	RUN_TEST(test_add_child_handle_set_on_success);
	RUN_TEST(test_add_two_child_set_head_tail);
	RUN_TEST(test_add_child_has_refcount_1);
}
