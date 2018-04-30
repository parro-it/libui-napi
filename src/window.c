#include <ui.h>
#include "ui_node.h"


static int windowOnClosing_cb(uiWindow *win, void *data) {
	napi_value result;

	struct callback_args *args = (struct callback_args *) data;
	napi_env env = args->env;

	CALL_CB(args->cb_ref, args->context, result, 0);
	return 0;
}

static napi_value windowOnClosing (napi_env env, napi_callback_info info) {
	napi_status status;

	INIT_ARGS(2);

	ARG_POINTER(uiWindow, win, 0);

	napi_async_context async_context;
	napi_ref cb_ref;
	struct callback_args *args;

	CREATE_ASYNC_CONTEXT(async_context, windowOnClosing);
	CREATE_CB_REF(cb_ref, 1);
	CREATE_CB_ARGS(args, async_context, cb_ref);

	uiWindowOnClosing(win, windowOnClosing_cb, args);

	return NULL;
}

static napi_value windowNew (napi_env env, napi_callback_info info) {
	INIT_ARGS(4);

	ARG_STRING(title, 0);
	ARG_INT32(width, 1);
	ARG_INT32(height, 2);
	ARG_BOOL(has_menubar, 3);

	uiWindow *win = uiNewWindow(title, width, height, has_menubar);
	free(title);
	RETURN_EXTERNAL(win);
}


static napi_value windowClose (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_POINTER(uiControl, win, 0);
	uiControlDestroy(win);
	return NULL;
}

static napi_value windowShow (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_POINTER(uiControl, win, 0);
	uiControlShow(win);
	return NULL;
}


void _libui_init_window (napi_env env, napi_value exports) {
	LIBUI_EXPORT(windowNew);
	LIBUI_EXPORT(windowShow);
	LIBUI_EXPORT(windowClose);
	LIBUI_EXPORT(windowOnClosing);
}
