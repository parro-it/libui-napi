#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "ControlBase";

LIBUI_FUNCTION(toplevel) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	return make_bool(env, uiControlToplevel(handle->control));
}

LIBUI_FUNCTION(getVisible) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	return make_bool(env, uiControlVisible(handle->control));
}

LIBUI_FUNCTION(setVisible) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_BOOL(value, 1);
	if (value) {
		uiControlShow(handle->control);
	} else {
		uiControlHide(handle->control);
	}

	return NULL;
}

LIBUI_FUNCTION(getEnabled) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	return make_bool(env, uiControlEnabled(handle->control));
}

LIBUI_FUNCTION(setEnabled) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_BOOL(value, 1);

	if (value) {
		uiControlEnable(handle->control);
	} else {
		uiControlDisable(handle->control);
	}

	return NULL;
}

napi_value _libui_init_ui_control(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(getEnabled);
	LIBUI_EXPORT(setEnabled);
	LIBUI_EXPORT(setVisible);
	LIBUI_EXPORT(getVisible);
	LIBUI_EXPORT(toplevel);
	return module;
}
