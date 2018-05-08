#ifndef LIBUI_NODE_CHILDREN_LIST_H__
#define LIBUI_NODE_CHILDREN_LIST_H__

#include <node_api.h>
#include <stdlib.h>
#include <ui.h>
#include "napi_utils.h"

typedef void (*destroy_cb)(uiControl *);

struct control_handle {
	napi_env env;
	/*
		A reference to the JavaScript object that wrap the handle pointer,
		It prevent the JavaScript object to be garbage collected, and is
		released when the control is destroyed.
	 */
	napi_ref ctrl_ref;
	const char *ctrl_type_name;
	bool is_destroyed;
	bool is_garbage_collected;
	destroy_cb original_destroy;
	uiControl *control;
	struct events_list *events;
	struct children_list *children;
};

/*
	this structure represent a node of the linked list
	of children of a control.
*/
struct children_node {
	struct control_handle *handle;
	struct children_node *next;
};

/*
	this structure represent a linked list
	of children of a control.
*/
struct children_list {
	struct children_node *head;
	struct children_node *tail;
};

/*
	create a new list of children controls
*/
struct children_list *create_children_list();

/*
	create a new node for a children list
*/
struct children_node *create_node(struct control_handle *child);

/*
	add a new child into a control handle children_list.
*/
napi_value add_child(napi_env env, struct children_list *list, struct control_handle *child);

#endif
