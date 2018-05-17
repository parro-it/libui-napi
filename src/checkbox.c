#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Checkbox";

LIBUI_FUNCTION(create) {
	INIT_ARGS(1);
	ARG_STRING(value, 0);
	uiControl *ctrl = uiControl(uiNewCheckbox(value));
	free(value);
	return control_handle_new(env, ctrl, "checkbox");
}

LIBUI_FUNCTION(setText) {
	INIT_ARGS(2);
	ARG_CTRL_HANDLE("checkbox", handle, 0);
	ARG_STRING(value, 1);
	uiCheckboxSetText(uiCheckbox(handle->control), value);
	free(value);
	return NULL;
}

LIBUI_FUNCTION(getText) {
	INIT_ARGS(1);
	ARG_CTRL_HANDLE("checkbox", handle, 0);

	char *char_ptr = uiCheckboxText(uiCheckbox(handle->control));
	napi_value result = make_utf8_string(env, char_ptr);
	uiFreeText(char_ptr);
	return result;
}

LIBUI_FUNCTION(setChecked) {
	INIT_ARGS(2);
	ARG_CTRL_HANDLE("checkbox", handle, 0);

	ARG_BOOL(value, 1);

	uiCheckboxSetChecked(uiCheckbox(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getChecked) {
	INIT_ARGS(1);
	ARG_CTRL_HANDLE("checkbox", handle, 0);

	bool value = uiCheckboxChecked(uiCheckbox(handle->control));
	return make_bool(env, value);
}

LIBUI_FUNCTION(onToggled) {
	INIT_ARGS(2);

	ARG_CTRL_HANDLE("checkbox", handle, 0);

	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onToggled");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiCheckboxOnToggled(uiCheckbox(handle->control), CALLBACK_OF(uiCheckbox, control_event_cb),
						event);

	return NULL;
}

napi_value _libui_init_checkbox(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getText);
	LIBUI_EXPORT(setText);
	LIBUI_EXPORT(onToggled);
	LIBUI_EXPORT(getChecked);
	LIBUI_EXPORT(setChecked);
	return module;
}
