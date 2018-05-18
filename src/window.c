#include "ui.h"
#include "napi_utils.h"
#include "app.h"
#include "control.h"
#include "events.h"
#include "values.h"

static const char *MODULE = "Window";

LIBUI_FUNCTION(onContentSizeChanged) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onContentSizeChanged");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiWindowOnContentSizeChanged(uiWindow(handle->control), CALLBACK_OF(uiWindow, control_event_cb),
								 event);

	return NULL;
}

LIBUI_FUNCTION(onClosing) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onClosing");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiWindowOnClosing(uiWindow(handle->control), INT_CALLBACK_OF(uiWindow, control_event_cb),
					  event);

	return NULL;
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(4);

	ARG_STRING(title, 0);
	ARG_INT32(width, 1);
	ARG_INT32(height, 2);
	ARG_BOOL(has_menubar, 3);

	uiWindow *win = uiNewWindow(title, width, height, has_menubar);
	free(title);

	return control_handle_new(env, uiControl(win), "window");
}

LIBUI_FUNCTION(close) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	uiControlDestroy(handle->control);
	remove_child(env, visible_windows, handle);
	return NULL;
}

LIBUI_FUNCTION(getTitle) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	char *char_ptr = uiWindowTitle(uiWindow(handle->control));
	napi_value result;

	napi_status status = napi_create_string_utf8(env, char_ptr, NAPI_AUTO_LENGTH, &result);
	CHECK_STATUS_THROW(status, napi_create_string_utf8);

	uiFreeText(char_ptr);
	return result;
}

LIBUI_FUNCTION(setTitle) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(title, 1);
	uiWindowSetTitle(uiWindow(handle->control), title);
	free(title);
	return NULL;
}

LIBUI_FUNCTION(show) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	uiControlShow(handle->control);
	add_child(env, visible_windows, handle);
	return NULL;
}

LIBUI_FUNCTION(setChild) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_POINTER(struct control_handle, child, 1);
	uiWindowSetChild(uiWindow(handle->control), child->control);
	clear_children(env, handle->children);
	add_child(env, handle->children, child);
	return NULL;
}

LIBUI_FUNCTION(getContentSize) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);

	int width = 0;
	int height = 0;
	uiWindowContentSize(uiWindow(handle->control), &width, &height);
	return make_size_int(env, width, height);
}

LIBUI_FUNCTION(setContentSize) {
	INIT_ARGS(3);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_INT32(width, 1);
	ARG_INT32(height, 2);
	uiWindowSetContentSize(uiWindow(handle->control), width, height);
	return NULL;
}

LIBUI_FUNCTION(getFullscreen) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);

	bool value = uiWindowFullscreen(uiWindow(handle->control));
	return make_bool(env, value);
}

LIBUI_FUNCTION(setFullscreen) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_BOOL(value, 1);

	uiWindowSetFullscreen(uiWindow(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getBorderless) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);

	bool value = uiWindowBorderless(uiWindow(handle->control));
	return make_bool(env, value);
}

LIBUI_FUNCTION(setBorderless) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_BOOL(value, 1);

	uiWindowSetBorderless(uiWindow(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getMargined) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);

	bool value = uiWindowMargined(uiWindow(handle->control));
	return make_bool(env, value);
}

LIBUI_FUNCTION(setMargined) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_BOOL(value, 1);

	uiWindowSetMargined(uiWindow(handle->control), value);
	return NULL;
}

napi_value _libui_init_window(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(setChild);
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(show);
	LIBUI_EXPORT(close);
	LIBUI_EXPORT(onClosing);
	LIBUI_EXPORT(getContentSize);
	LIBUI_EXPORT(setContentSize);
	LIBUI_EXPORT(onContentSizeChanged);
	LIBUI_EXPORT(getMargined);
	LIBUI_EXPORT(setMargined);
	LIBUI_EXPORT(getBorderless);
	LIBUI_EXPORT(setBorderless);
	LIBUI_EXPORT(getFullscreen);
	LIBUI_EXPORT(setFullscreen);
	LIBUI_EXPORT(getTitle);
	LIBUI_EXPORT(setTitle);
	return module;
}
