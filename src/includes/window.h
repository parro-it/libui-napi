#ifndef __LIBUI_NODE_WINDOW_H__
#define __LIBUI_NODE_WINDOW_H__

#include <ui.h>
#include <map_template.h>
#include "uinode.h"

extern struct WindowMap controls_map;

typedef void (*destroy_cb)(uiControl *);

struct windowHandle {
	bool is_destroyed;
	bool is_garbage_collected;
	destroy_cb original_destroy;
	uiWindow *win;
	struct callback_args *onClosing_args;
	struct callback_args *onContentSizeChanged_args;
};


_DECLARE_MAP(struct windowHandle *, uiControl *, struct WindowMap, win_map)



#endif
