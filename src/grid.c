#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Grid";

LIBUI_FUNCTION(append) {
	INIT_ARGS(10);
	ARG_CTRL_HANDLE("grid", handle, 0);
	ARG_POINTER(struct control_handle, child, 1);
	ARG_INT32(left, 2);
	ARG_INT32(top, 3);
	ARG_INT32(xspan, 4);
	ARG_INT32(yspan, 5);
	ARG_INT32(hexpand, 6);
	ARG_INT32(halign, 7);
	ARG_INT32(vexpand, 8);
	ARG_INT32(valign, 9);

	uiGridAppend(uiGrid(handle->control), child->control, left, top, xspan, yspan, hexpand, halign,
				 vexpand, valign);
	add_child(env, handle->children, child);

	return NULL;
}

LIBUI_FUNCTION(setPadded) {
	INIT_ARGS(2);
	ARG_CTRL_HANDLE("grid", handle, 0);
	ARG_BOOL(value, 1);

	uiGridSetPadded(uiGrid(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getPadded) {
	INIT_ARGS(1);
	ARG_CTRL_HANDLE("grid", handle, 0);

	bool value = uiGridPadded(uiGrid(handle->control));
	return make_bool(env, value);
}

LIBUI_FUNCTION(create) {
	uiControl *ctrl = uiControl(uiNewGrid());
	return control_handle_new(env, ctrl, "grid");
}

LIBUI_FUNCTION(insertAt) {
	INIT_ARGS(10);
	ARG_CTRL_HANDLE("grid", handle, 0);
	ARG_POINTER(struct control_handle, child, 1);
	ARG_POINTER(struct control_handle, before, 2);
	ARG_INT32(at, 3);
	ARG_INT32(xspan, 4);
	ARG_INT32(yspan, 5);
	ARG_INT32(hexpand, 6);
	ARG_INT32(halign, 7);
	ARG_INT32(vexpand, 8);
	ARG_INT32(valign, 9);

	uiGridInsertAt(uiGrid(handle->control), child->control, before->control, at, xspan, yspan,
				   hexpand, halign, vexpand, valign);
	// TODO: fix this, insert at specific position
	add_child(env, handle->children, child);
	return NULL;
}

napi_value _libui_init_grid(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getPadded);
	LIBUI_EXPORT(setPadded);
	LIBUI_EXPORT(append);
	LIBUI_EXPORT(insertAt);

	return module;
}
