#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "EditableCombobox";

LIBUI_FUNCTION(create) {
	uiControl *ctrl = uiControl(uiNewEditableCombobox());
	return control_handle_new(env, ctrl, "editableCombobox");
}

LIBUI_FUNCTION(setText) {
	INIT_ARGS(2);
	ARG_CTRL_HANDLE("editableCombobox", handle, 0);
	ARG_STRING(value, 1);
	uiEditableComboboxSetText(uiEditableCombobox(handle->control), value);
	free(value);
	return NULL;
}

LIBUI_FUNCTION(getText) {
	INIT_ARGS(1);
	ARG_CTRL_HANDLE("editableCombobox", handle, 0);
	char *char_ptr = uiEditableComboboxText(uiEditableCombobox(handle->control));
	napi_value result = make_utf8_string(env, char_ptr);
	uiFreeText(char_ptr);
	return result;
}

LIBUI_FUNCTION(append) {
	INIT_ARGS(2);
	ARG_CTRL_HANDLE("editableCombobox", handle, 0);
	ARG_STRING(value, 1);
	uiEditableComboboxAppend(uiEditableCombobox(handle->control), value);
	free(value);
	return NULL;
}

LIBUI_FUNCTION(onChanged) {
	INIT_ARGS(2);

	ARG_CTRL_HANDLE("editableCombobox", handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onChanged");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiEditableComboboxOnChanged(uiEditableCombobox(handle->control),
								CALLBACK_OF(uiEditableCombobox, control_event_cb), event);

	return NULL;
}

napi_value _libui_init_editablecombobox(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getText);
	LIBUI_EXPORT(setText);
	LIBUI_EXPORT(append);
	LIBUI_EXPORT(onChanged);
	return module;
}
