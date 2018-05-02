#include <ui.h>
#include "uinode.h"
#include "control.h"
#include "events.h"

struct ctrl_map controls_map;

static int windowOnClosing_cb(uiWindow *win, void *data) {
	struct event_t *event = (struct event_t *) data;
	fire_event(event);
	return 0;
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

	uiWindowOnClosing(uiWindow(handle->control), windowOnClosing_cb, event);

	return NULL;
}

static void window_on_destroy(uiControl *control) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, control, &handle);
	handle->original_destroy(control);
	ctrl_map_remove(&controls_map, control);
	clear_all_events(handle->events);
	if (handle->is_garbage_collected) {
		free(handle->events);
		free(handle);
	} else {
		handle->is_destroyed = true;
	}
}

static void on_window_collected(napi_env env, void* finalize_data, void* finalize_hint) {
	struct control_handle *handle = (struct control_handle *) finalize_data;
	if (handle->is_destroyed) {
		free(handle->events);
		free(handle);
	} else {
		handle->is_garbage_collected = true;
	}
}

static napi_value windowNew (napi_env env, napi_callback_info info) {
	INIT_ARGS(4);

	ARG_STRING(title, 0);
	ARG_INT32(width, 1);
	ARG_INT32(height, 2);
	ARG_BOOL(has_menubar, 3);

	uiWindow *win = uiNewWindow(title, width, height, has_menubar);

	struct control_handle *handle = calloc(1, sizeof(struct control_handle));
	handle->events = calloc(1, sizeof(struct events_list));
	handle->control = uiControl(win);
	handle->original_destroy = uiControl(win)->Destroy;
	uiControl(win)->Destroy = window_on_destroy;
	ctrl_map_insert(&controls_map, handle, uiControl(win));

	free(title);

	RETURN_EXTERNAL(handle, on_window_collected);
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


void _libui_init_window (napi_env env, napi_value exports) {
	LIBUI_EXPORT(windowNew);
	LIBUI_EXPORT(windowShow);
	LIBUI_EXPORT(windowClose);
	LIBUI_EXPORT(windowOnClosing);
	LIBUI_EXPORT(windowGetTitle);
	LIBUI_EXPORT(windowSetTitle);

}
