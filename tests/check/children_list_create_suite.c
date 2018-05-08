#include <assert.h>
#include <stdlib.h>
#include "children_list.h"
#include "tests.h"

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

void children_list_create_suite(napi_env env) {
	RUN_TEST(test_create_node);
	RUN_TEST(test_create_children_list);
}
