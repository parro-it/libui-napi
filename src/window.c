#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"
#include "values.h"

typedef void (*window_event_cb_t)(uiWindow *win, void *data);

static int window_event_cb(uiWindow *win, void *data) {
	struct event_t *event = (struct event_t *) data;
	fire_event(event);
	return 0;
}

static napi_value windowOnContentSizeChanged (napi_env env, napi_callback_info info) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onContentSizeChanged");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiWindowOnContentSizeChanged(uiWindow(handle->control), (window_event_cb_t) window_event_cb, event);

	return NULL;
}

static napi_value windowOnClosing (napi_env env, napi_callback_info info) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onClosing");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiWindowOnClosing(uiWindow(handle->control), window_event_cb, event);

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

	return control_handle_new(env, uiControl(win), "window");
}


static napi_value windowClose (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	uiControlDestroy(handle->control);
	return NULL;
}


static napi_value windowGetTitle (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	char *char_ptr = uiWindowTitle(uiWindow(handle->control));
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
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(title, 1);
	uiWindowSetTitle(uiWindow(handle->control), title);
	free(title);
	return NULL;
}

static napi_value windowShow (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	uiControlShow(handle->control);
	return NULL;
}

static napi_value windowSetChild (napi_env env, napi_callback_info info) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_POINTER(struct control_handle, child, 1);
	uiWindowSetChild(uiWindow(handle->control), child->control);
	add_child(handle, child);
	return NULL;
}

static napi_value windowGetContentSize (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);

	int width = 0;
	int height = 0;
	uiWindowContentSize(uiWindow(handle->control), &width, &height);
	return make_size(env, width, height);
}

void _libui_init_window (napi_env env, napi_value exports) {
	LIBUI_EXPORT(windowSetChild);
	LIBUI_EXPORT(windowNew);
	LIBUI_EXPORT(windowShow);
	LIBUI_EXPORT(windowClose);
	LIBUI_EXPORT(windowOnClosing);
	LIBUI_EXPORT(windowGetContentSize);
	LIBUI_EXPORT(windowOnContentSizeChanged);
	LIBUI_EXPORT(windowGetTitle);
	LIBUI_EXPORT(windowSetTitle);
}
