#include "ui.h"
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Box";

LIBUI_FUNCTION(append) {
	INIT_ARGS(3);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_POINTER(struct control_handle, child, 1);
	ARG_BOOL(stretchy, 2);

	if (add_child(env, handle->children, child) != napi_ok) {
		return NULL;
	}
	uiBoxAppend(uiBox(handle->control), child->control, stretchy);
	return NULL;
}

LIBUI_FUNCTION(deleteAt) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_INT32(index, 1);

	uiBoxDelete(uiBox(handle->control), index);
	remove_child_at(env, handle->children, index);
	return NULL;
}

LIBUI_FUNCTION(setPadded) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_BOOL(value, 1);

	uiBoxSetPadded(uiBox(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getPadded) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	bool value = uiBoxPadded(uiBox(handle->control));
	return make_bool(env, value);
}

LIBUI_FUNCTION(createVertical) {
	uiControl *ctrl = uiControl(uiNewVerticalBox());
	return control_handle_new(env, ctrl, "verticalBox");
}

LIBUI_FUNCTION(createHorizontal) {
	uiControl *ctrl = uiControl(uiNewHorizontalBox());
	return control_handle_new(env, ctrl, "horizontalBox");
}

napi_value _libui_init_box(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(createVertical);
	LIBUI_EXPORT(createHorizontal);
	LIBUI_EXPORT(getPadded);
	LIBUI_EXPORT(setPadded);
	LIBUI_EXPORT(append);
	LIBUI_EXPORT(deleteAt);
	return module;
}
