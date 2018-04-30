#include <ui.h>
#include "ui_node.h"

struct windowHandle {
	uiWindow *win;
	struct callback_args *onClosingArgs;
	struct callback_args *onContentSizeChangedArgs;
};

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

	ARG_POINTER(struct windowHandle, handle, 0);

	napi_async_context async_context;
	napi_ref cb_ref;
	struct callback_args *args;

	CREATE_ASYNC_CONTEXT(async_context, windowOnClosing);
	ARG_CB_REF(cb_ref, 1);
	CREATE_CB_ARGS(args, async_context, cb_ref);

	handle->onClosingArgs = args;

	uiWindowOnClosing(handle->win, windowOnClosing_cb, args);

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
	struct windowHandle *handle = calloc(1, sizeof(struct windowHandle));
	handle->win = win;

	// TODO: add callback to free handle
	// when external is freed and window is destroyed
	RETURN_EXTERNAL(handle);
}


static napi_value windowClose (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_POINTER(struct windowHandle, handle, 0);
	if (handle->onClosingArgs != NULL) {
		uint32_t new_ref_count;
		napi_status status = napi_reference_unref(
			env,
			handle->onClosingArgs->cb_ref,
			&new_ref_count
		);
		CHECK_STATUS_THROW(status, napi_create_external);
		free(handle->onClosingArgs);
		handle->onClosingArgs = NULL;

	}
	uiControlDestroy(uiControl(handle->win));
	return NULL;
}


static napi_value windowGetTitle (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_POINTER(struct windowHandle, handle, 0);
	char *char_ptr = uiWindowTitle(handle->win);
	napi_value result;

	napi_status status = napi_create_string_utf8(
		env,
		char_ptr,
		NAPI_AUTO_LENGTH,
		&result
	);
	CHECK_STATUS_THROW(status, napi_create_external);

	uiFreeText(char_ptr);
	return result;
}

static napi_value windowSetTitle (napi_env env, napi_callback_info info) {
	INIT_ARGS(2);
	ARG_POINTER(struct windowHandle, handle, 0);
	ARG_STRING(title, 1);
	uiWindowSetTitle(handle->win, title);
	free(title);
	return NULL;
}

static napi_value windowShow (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_POINTER(struct windowHandle, handle, 0);
	uiControlShow(uiControl(handle->win));
	return NULL;
}


void _libui_init_window (napi_env env, napi_value exports) {
	LIBUI_EXPORT(windowNew);
	LIBUI_EXPORT(windowShow);
	LIBUI_EXPORT(windowClose);
	LIBUI_EXPORT(windowOnClosing);
	LIBUI_EXPORT(windowGetTitle);
	LIBUI_EXPORT(windowSetTitle);

}
