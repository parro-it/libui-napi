#include <assert.h>
#include "children_list.h"

struct children_list *create_children_list() {
	return calloc(1, sizeof(struct children_list));
}

struct children_node *create_node(struct control_handle *child) {
	assert(child != NULL);
	struct children_node *new_node = malloc(sizeof(struct children_node));
	new_node->next = NULL;
	new_node->handle = child;
	return new_node;
}

napi_value add_child(napi_env env, struct children_list *list, struct control_handle *child) {
	assert(env != NULL);
	assert(list != NULL);
	assert(child != NULL);

	struct children_node *new_node = malloc(sizeof(struct children_node));
	new_node->next = NULL;
	new_node->handle = child;

	uint32_t new_ref_count;
	napi_status status = napi_reference_ref(env, child->ctrl_ref, &new_ref_count);
	CHECK_STATUS_THROW(status, napi_reference_unref);
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
