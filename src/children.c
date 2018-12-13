#include <assert.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "ControlChildren";

napi_value remove_child(napi_env env, struct children_list *list, struct control_handle *child) {
	if (list->head == NULL) {
		return NULL;
	}

	struct children_node *node = list->head;
	struct children_node *prev_node = NULL;

	while (node != NULL) {
		if (node->handle == child) {
			uint32_t new_ref_count;
			napi_status status = napi_reference_unref(env, node->handle->ctrl_ref, &new_ref_count);
			CHECK_STATUS_THROW(status, napi_reference_unref);
			LIBUI_NODE_DEBUG_F("new reference count for %s %p: %d", node->handle->ctrl_type_name,
							   node->handle, new_ref_count);

			if (node == list->head) {
				// removing first child
				list->head = node->next;
			}

			if (node == list->tail) {
				// removing last child
				list->tail = prev_node;
			}

			if (prev_node != NULL) {
				prev_node->next = node->next;
			}

			free(node);

			return NULL;
		}

		prev_node = node;
		node = node->next;
	}
	return NULL;
}

bool has_child(struct children_list *list, struct control_handle *child) {
	struct children_node *node = list->head;
	while (node != NULL) {
		if (node->handle == child) {
			return true;
		}
		node = node->next;
	}
	return false;
}

napi_status add_child_at(napi_env env, struct children_list *list, struct control_handle *child,
						 int index) {
	assert(env != NULL);
	assert(list != NULL);
	assert(child != NULL);
	if (child->control->Parent != NULL && child->control->Parent(child->control) != NULL) {
		napi_throw_error(env, NULL, "Child control already has parent.");
		return napi_pending_exception;
	}

	struct children_node *new_node = malloc(sizeof(struct children_node));
	new_node->next = NULL;
	new_node->handle = child;

	uint32_t new_ref_count;
	napi_status status = napi_reference_ref(env, child->ctrl_ref, &new_ref_count);
	CHECK_STATUS_PENDING(status, napi_reference_unref);

	if (index == 0) {
		new_node->next = list->head;
		list->head = new_node;

		if (list->tail == NULL) {
			// first child
			list->tail = new_node;
		}
		return napi_ok;
	}

	int i = 0;
	struct children_node *node = list->head;
	struct children_node *prev_node = NULL;
	while (i < index && node != NULL) {
		prev_node = node;
		node = node->next;
		i++;
	}

	prev_node->next = new_node;
	new_node->next = node;

	if (i < index) {
		// we are past end. insert at tail
		list->tail->next = new_node;
		list->tail = new_node;
	}

	return napi_ok;
}

napi_value destroy_all_children(napi_env env, struct children_list *list) {
	if (list->head == NULL) {
		// This control has no children
		return NULL;
	}

	struct children_node *node = list->head;

	while (node != NULL) {
		uiControlDestroy(node->handle->control);
		node = node->next;
	}

	return NULL;
}

napi_value clear_children(napi_env env, struct children_list *list) {
	if (list->head == NULL) {
		// This control has no children
		return NULL;
	}

	struct children_node *node = list->head;
	struct children_node *node_to_free;

	while (node != NULL) {
		uint32_t new_ref_count;
		napi_status status = napi_reference_unref(env, node->handle->ctrl_ref, &new_ref_count);
		CHECK_STATUS_THROW(status, napi_reference_unref);
		LIBUI_NODE_DEBUG_F("new reference count for %s %p: %d", node->handle->ctrl_type_name,
						   node->handle, new_ref_count);

		node_to_free = node;
		node = node->next;
		free(node_to_free);
	}

	list->head = NULL;
	list->tail = NULL;

	return NULL;
}

napi_value remove_child_at(napi_env env, struct children_list *list, int index_to_remove) {
	if (list->head == NULL) {
		return NULL;
	}

	struct children_node *node = list->head;
	struct children_node *prev_node = NULL;
	int i = 0;
	while (node != NULL) {
		if (i == index_to_remove) {
			uint32_t new_ref_count;
			napi_status status = napi_reference_unref(env, node->handle->ctrl_ref, &new_ref_count);
			CHECK_STATUS_THROW(status, napi_reference_unref);
			LIBUI_NODE_DEBUG_F("new reference count for %s %p: %d", node->handle->ctrl_type_name,
							   node->handle, new_ref_count);

			if (node == list->head) {
				// removing first child
				list->head = node->next;
			}

			if (node == list->tail) {
				// removing last child
				list->tail = prev_node;
			}

			if (prev_node != NULL) {
				prev_node->next = node->next;
			}

			free(node);

			return NULL;
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return NULL;
}

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

napi_status add_child(napi_env env, struct children_list *list, struct control_handle *child) {
	assert(env != NULL);
	assert(list != NULL);
	assert(child != NULL);
	if (child->control->Parent != NULL && child->control->Parent(child->control) != NULL) {
		napi_throw_error(env, NULL, "Child control already has parent.");
		return napi_pending_exception;
	}
	struct children_node *new_node = malloc(sizeof(struct children_node));
	new_node->next = NULL;
	new_node->handle = child;
	uint32_t new_ref_count;
	napi_status status = napi_reference_ref(env, child->ctrl_ref, &new_ref_count);
	CHECK_STATUS_PENDING(status, napi_reference_unref);
	if (list->head == NULL) {
		// First child for this control
		list->head = new_node;
		list->tail = new_node;
		return napi_ok;
	}

	// Control already has other children. Append to tail
	list->tail->next = new_node;

	// set this node as the new tail
	list->tail = new_node;

	return napi_ok;
}

static void on_node_gc(napi_env env, void *finalize_data, void *finalize_hint) {
	// TODO: children_node should be unmarked as
	// used by js side, so that it can be freed
	// by C side when needed.
	// Also, if the C side has already tryied to free it,
	// it should have marked it as 'disposable'
	// in that case, it should be fred here.
}

LIBUI_FUNCTION(getChildNodeAt) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_INT32(index, 1);

	if (index < 0) {
		napi_throw_error(env, NULL, "Index should be great than 0.");
		return NULL;
	}

	const char *not_found = "Index should be less than number of children.";
	struct children_node *node = handle->children->head;
	int current_idx = 0;

	while (current_idx < index) {
		if (node == NULL) {
			napi_throw_error(env, NULL, not_found);
			return NULL;
		}
		node = node->next;
		current_idx++;
	}

	if (node == NULL) {
		napi_throw_error(env, NULL, not_found);
		return NULL;
	}

	// TODO: children_node should be marked as
	// used by js side, because it should not be freed
	// by C side until its external is garbage collected by
	// js side

	napi_value node_external;
	napi_status status = napi_create_external(env, node, on_node_gc, NULL, &node_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return node_external;
}

LIBUI_FUNCTION(controlFromChildNode) {
	INIT_ARGS(1);
	ARG_POINTER(struct children_node, node, 0);

	napi_ref ctrl_ref = node->handle->ctrl_ref;
	napi_value handle_external;

	napi_status status = napi_get_reference_value(env, ctrl_ref, &handle_external);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	return handle_external;
}

LIBUI_FUNCTION(nextChildNode) {
	INIT_ARGS(1);
	ARG_POINTER(struct children_node, handle, 0);

	struct children_node *node = children_node->next;

	if (node == NULL) {
		return NULL;
	}

	napi_value node_external;
	napi_status status = napi_create_external(env, node, on_node_gc, NULL, &node_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return NULL;
}

napi_value _libui_init_ui_control_children(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(getChildNodeAt);
	LIBUI_EXPORT(nextChildNode);
	LIBUI_EXPORT(controlFromChildNode);
	return module;
}