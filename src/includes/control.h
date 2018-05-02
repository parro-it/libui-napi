#ifndef __LIBUI_NODE_CONTROL_H__
#define __LIBUI_NODE_CONTROL_H__

#include <ui.h>
#include <map_template.h>
#include "napi_utils.h"
#include "events.h"

extern struct ctrl_map controls_map;

typedef void (*destroy_cb)(uiControl *);


struct control_handle {
	bool is_destroyed;
	bool is_garbage_collected;
	destroy_cb original_destroy;
	uiControl *control;
	struct events_list *events;
};

napi_value control_handle_new(napi_env env, uiControl *control);

_DECLARE_MAP(struct control_handle *, uiControl *, struct ctrl_map, ctrl_map)



#endif
