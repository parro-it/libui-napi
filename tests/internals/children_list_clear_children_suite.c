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

static void test_clear_children_reset_head_tail(napi_env env) {

	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);
	add_child(env, list, child);
	assert(list->head != NULL);
	assert(list->tail != NULL);
	clear_children(env, list);
	assert(list->head == NULL);
	assert(list->tail == NULL);
}

static void test_clear_list_with_two_controls(napi_env env) {

	struct children_list *list = create_children_list();
	struct control_handle *child1 = get_child(env);
	struct control_handle *child2 = get_child(env);
	add_child(env, list, child1);
	add_child(env, list, child2);
	assert(list->head->handle == child1);
	assert(list->tail->handle == child2);

	clear_children(env, list);

	assert(list->head == NULL);
	assert(list->tail == NULL);
	uint32_t ref_count;
	napi_reference_ref(env, child1->ctrl_ref, &ref_count);
	assert(ref_count == 1);
	napi_reference_ref(env, child2->ctrl_ref, &ref_count);
	assert(ref_count == 1);
}

static void test_clear_empty_list_is_noop(napi_env env) {

	struct children_list *list = create_children_list();
	clear_children(env, list);
	assert(list->head == NULL);
	assert(list->tail == NULL);
}

static void test_clear_children_decrease_control_ref(napi_env env) {

	struct children_list *list = create_children_list();
	struct control_handle *child = get_child(env);
	add_child(env, list, child);
	uint32_t ref_count;
	napi_reference_unref(env, child->ctrl_ref, &ref_count);
	assert(ref_count == 0);
	napi_reference_ref(env, child->ctrl_ref, &ref_count);
	assert(ref_count == 1);

	clear_children(env, list);

	napi_reference_ref(env, child->ctrl_ref, &ref_count);
	assert(ref_count == 1);
}

void children_list_clear_children_suite(napi_env env) {
	RUN_TEST(test_clear_children_reset_head_tail);
	RUN_TEST(test_clear_children_decrease_control_ref);
	RUN_TEST(test_clear_empty_list_is_noop);
	RUN_TEST(test_clear_list_with_two_controls);
}
