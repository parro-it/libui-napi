#ifndef __LIBUI_NODE_CONTROL_H__
#define __LIBUI_NODE_CONTROL_H__

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
	struct children_node *children_head;
	struct children_node *children_tail;
};

struct control_handle {
	bool is_destroyed;
	bool is_garbage_collected;
	destroy_cb original_destroy;
	uiControl *control;
	struct events_list *events;
	struct children_list *children;
};


/*
	add a new child into a control handle.
*/
void add_child(struct control_handle *control, struct control_handle *child);

/*
	remove and decrement references for all children of a control.
*/
void clear_children(struct control_handle *control);

/*
	create a new handle structure representing a control.
*/
napi_value control_handle_new(napi_env env, uiControl *control);

_DECLARE_MAP(struct control_handle *, uiControl *, struct ctrl_map, ctrl_map)



#endif
