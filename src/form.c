#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char* MODULE = "Form";

LIBUI_FUNCTION(append) {
	INIT_ARGS(4);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(label, 1);
	ARG_POINTER(struct control_handle, child, 2);
	ARG_BOOL(stretchy, 3);

	uiFormAppend(uiForm(handle->control), label, child->control, stretchy);
	add_child(env, handle->children, child);
	free(label);

	return NULL;
}

LIBUI_FUNCTION(deleteAt) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_INT32(index, 1);

	uiFormDelete(uiForm(handle->control), index);
	remove_child_at(env, handle->children, index);
	return NULL;
}

LIBUI_FUNCTION(setPadded) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_BOOL(value, 1);

	uiFormSetPadded(uiForm(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getPadded) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);

	bool value = uiFormPadded(uiForm(handle->control));
	return make_bool(env, value);
}

LIBUI_FUNCTION(create) {
	uiControl *ctrl = uiControl(uiNewForm());
	return control_handle_new(env, ctrl, "form");
}

napi_value _libui_init_form (napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getPadded);
	LIBUI_EXPORT(setPadded);
	LIBUI_EXPORT(append);
	LIBUI_EXPORT(deleteAt);
	return module;
}

