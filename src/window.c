#include <ui.h>
#include "core.h"

static napi_value newWindow (napi_env env, napi_callback_info info) {
	napi_value argv[4];
	size_t argc = 4;

	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	if (argc < 4) {
		napi_throw_error(env, "EINVAL", "Too few arguments");
		return NULL;
	}

	napi_status status;

	ARG_STRING(title, 0);
	ARG_INT32(width, 1);
	ARG_INT32(height, 2);
	ARG_BOOL(has_menubar, 3);

	uiWindow *win = uiNewWindow(title, width, height, has_menubar);
	free(title);

	napi_value napi_win;
	status = napi_create_external(env, win, NULL, NULL, &napi_win);
	CHECK_STATUS_THROW(status, napi_create_external);

	return napi_win;
}

static napi_value windowShow (napi_env env, napi_callback_info info) {
	napi_value argv[1];
	size_t argc = 1;

	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	if (argc < 1) {
		napi_throw_error(env, "EINVAL", "Too few arguments");
		return NULL;
	}

	uiWindow *win;
	napi_status status = napi_get_value_external(env, argv[0], (void **) &win);
	CHECK_STATUS_THROW(status, napi_get_value_external);

	uiControlShow(uiControl(win));
	return NULL;
}


void _libui_init_window (napi_env env, napi_value exports) {
	LIBUI_EXPORT(newWindow);
	LIBUI_EXPORT(windowShow);
}
