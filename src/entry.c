#include "ui.h"
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Entries";

LIBUI_FUNCTION(createEntry) {
	uiControl *ctrl = uiControl(uiNewEntry());
	return control_handle_new(env, ctrl, "entry");
}

LIBUI_FUNCTION(createPassword) {
	uiControl *ctrl = uiControl(uiNewPasswordEntry());
	return control_handle_new(env, ctrl, "passwordEntry");
}

LIBUI_FUNCTION(createSearch) {
	uiControl *ctrl = uiControl(uiNewSearchEntry());
	return control_handle_new(env, ctrl, "searchEntry");
}

LIBUI_FUNCTION(onChanged) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onChanged");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiEntryOnChanged(uiEntry(handle->control), CALLBACK_OF(uiEntry, control_event_cb), event);

	return NULL;
}

LIBUI_FUNCTION(setText) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(value, 1);
	uiEntrySetText(uiEntry(handle->control), value);
	free(value);
	return NULL;
}

LIBUI_FUNCTION(getText) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	char *char_ptr = uiEntryText(uiEntry(handle->control));
	napi_value result = make_utf8_string(env, char_ptr);
	uiFreeText(char_ptr);
	return result;
}

LIBUI_FUNCTION(setReadOnly) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_BOOL(value, 1);

	uiEntrySetReadOnly(uiEntry(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getReadOnly) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);

	bool value = uiEntryReadOnly(uiEntry(handle->control));
	return make_bool(env, value);
}

napi_value _libui_init_entry(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(createEntry);
	LIBUI_EXPORT(createSearch);
	LIBUI_EXPORT(createPassword);
	LIBUI_EXPORT(getText);
	LIBUI_EXPORT(setText);
	LIBUI_EXPORT(getReadOnly);
	LIBUI_EXPORT(setReadOnly);
	LIBUI_EXPORT(onChanged);
	return module;
}
