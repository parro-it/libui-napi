#include "ui.h"
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Tab";

LIBUI_FUNCTION(append) {
	INIT_ARGS(3);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(label, 1);
	ARG_POINTER(struct control_handle, child, 2);

	uiTabAppend(uiTab(handle->control), label, child->control);
	add_child(env, handle->children, child);
	return NULL;
}

LIBUI_FUNCTION(insertAt) {
	INIT_ARGS(4);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(label, 1);
	ARG_INT32(before, 2);
	ARG_POINTER(struct control_handle, child, 3);

	uiTabInsertAt(uiTab(handle->control), label, before, child->control);
	// TODO: fix this, insert at specific position
	add_child_at(env, handle->children, child, before);
	return NULL;
}

LIBUI_FUNCTION(deleteAt) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_INT32(index, 1);

	uiTabDelete(uiTab(handle->control), index);
	remove_child_at(env, handle->children, index);
	return NULL;
}

LIBUI_FUNCTION(setMargined) {
	INIT_ARGS(3);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_INT32(page, 1);
	ARG_BOOL(value, 2);

	uiTabSetMargined(uiTab(handle->control), page, value);
	return NULL;
}

LIBUI_FUNCTION(getMargined) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_INT32(page, 1);

	bool value = uiTabMargined(uiTab(handle->control), page);
	return make_bool(env, value);
}

LIBUI_FUNCTION(create) {
	uiControl *ctrl = uiControl(uiNewTab());
	return control_handle_new(env, ctrl, "tab");
}

LIBUI_FUNCTION(numPages) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);

	int value = uiTabNumPages(uiTab(handle->control));
	return make_int32(env, value);
}

napi_value _libui_init_tab(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getMargined);
	LIBUI_EXPORT(setMargined);
	LIBUI_EXPORT(append);
	LIBUI_EXPORT(numPages);
	LIBUI_EXPORT(deleteAt);
	LIBUI_EXPORT(insertAt);
	return module;
}
