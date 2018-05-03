#ifndef LIBUI_NODE_CONTROL_H__
#define LIBUI_NODE_CONTROL_H__

#include <ui.h>
#include <map_template.h>
#include "napi_utils.h"
#include "events.h"

extern struct ctrl_map controls_map;

typedef void (*destroy_cb)(uiControl *);

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

struct control_handle {
	napi_env env;
	/*
		A reference to the JavaScript object that wrap the handle pointer,
		It prevent the JavaScript object to be garbage collected, and is
		released when the control is destroyed.
	 */
	napi_ref ctrl_ref;
	const char* ctrl_type_name;
	bool is_destroyed;
	bool is_garbage_collected;
	destroy_cb original_destroy;
	uiControl *control;
	struct events_list *events;
	struct children_list *children;
};


/*
	add a new child into a control handle children_list.
*/
napi_value add_child(napi_env env, struct children_list *list, struct control_handle *child);

/*
	remove and decrement references for all children of a control children_list.
*/
napi_value clear_children(napi_env env, struct children_list *list);

/*
	create a new handle structure representing a control.
*/
napi_value control_handle_new(napi_env env, uiControl *control, const char* ctrl_type_name);

/*
	create a new list of children controls
*/
struct children_list *create_children_list();

/*
	remove and decrement a child of a control children_list.
*/
napi_value remove_child(napi_env env, struct children_list *list, struct control_handle *child);

/*
	loop over each control in the list destroying them.
*/
napi_value destroy_all_children(napi_env env, struct children_list *list);


_DECLARE_MAP(struct control_handle *, uiControl *, struct ctrl_map, ctrl_map)



#endif
