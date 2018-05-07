#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Combobox";

LIBUI_FUNCTION(create) {
	uiControl *ctrl = uiControl(uiNewCombobox());
	return control_handle_new(env, ctrl, "combobox");
}

LIBUI_FUNCTION(setSelected) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_INT32(idx, 1);
	uiComboboxSetSelected(uiCombobox(handle->control), idx);
	return NULL;
}

LIBUI_FUNCTION(getSelected) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	int idx = uiComboboxSelected(uiCombobox(handle->control));
	return make_int32(env, idx);
}

LIBUI_FUNCTION(append) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(value, 1);
	uiComboboxAppend(uiCombobox(handle->control), value);
	free(value);
	return NULL;
}

LIBUI_FUNCTION(onSelected) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onSelected");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiComboboxOnSelected(uiCombobox(handle->control), CALLBACK_OF(uiCombobox, control_event_cb),
						 event);

	return NULL;
}

napi_value _libui_init_combobox(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getSelected);
	LIBUI_EXPORT(setSelected);
	LIBUI_EXPORT(append);
	LIBUI_EXPORT(onSelected);
	return module;
}
