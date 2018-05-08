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

void children_list_add_child_suite(napi_env env) {
	RUN_TEST(test_add_child_return_null_on_success);
	RUN_TEST(test_add_child_set_head_tail_on_success);
	RUN_TEST(test_add_child_next_null_on_success);
	RUN_TEST(test_add_child_handle_set_on_success);
}
