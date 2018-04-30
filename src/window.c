#include <ui.h>
#include "core.h"

static napi_value newWindow (napi_env env, napi_callback_info info) {
	INIT_ARGS(4);

	ARG_STRING(title, 0);
	ARG_INT32(width, 1);
	ARG_INT32(height, 2);
	ARG_BOOL(has_menubar, 3);

	uiWindow *win = uiNewWindow(title, width, height, has_menubar);
	free(title);

	napi_value napi_win;
	napi_status status = napi_create_external(env, win, NULL, NULL, &napi_win);
	CHECK_STATUS_THROW(status, napi_create_external);

	return napi_win;
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
	LIBUI_EXPORT(newWindow);
	LIBUI_EXPORT(windowShow);
	LIBUI_EXPORT(windowClose);
}
