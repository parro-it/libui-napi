#ifndef __LIBUI_NODE_EVENTS_H__
#define __LIBUI_NODE_EVENTS_H__

#include <ui.h>
#include "uinode.h"

struct callback_args {
	napi_ref cb_ref;
	napi_env env;
	napi_async_context context;
};

struct callback_args *create_event(napi_env env, napi_ref cb_ref, const char *name);
napi_value raise_event(struct callback_args *event);

#endif
