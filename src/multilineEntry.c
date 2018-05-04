#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char* MODULE = "MultilineEntry";

LIBUI_FUNCTION(create) {
	uiControl *ctrl = uiControl(uiNewNonWrappingMultilineEntry());
	return control_handle_new(env, ctrl, "multilineEntry");
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

	uiMultilineEntryOnChanged(
		uiMultilineEntry(handle->control),
		CALLBACK_OF(uiMultilineEntry, control_event_cb),
		event
	);

	return NULL;
}

LIBUI_FUNCTION(setText) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(value, 1);
	uiMultilineEntrySetText(uiMultilineEntry(handle->control), value);
	free(value);
	return NULL;
}

LIBUI_FUNCTION(getText) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	char *char_ptr = uiMultilineEntryText(uiMultilineEntry(handle->control));
	napi_value result = make_utf8_string(env, char_ptr);
	uiFreeText(char_ptr);
	return result;
}

LIBUI_FUNCTION(setReadOnly) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_BOOL(value, 1);

	uiMultilineEntrySetReadOnly(uiMultilineEntry(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getReadOnly) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);

	bool value = uiMultilineEntryReadOnly(uiMultilineEntry(handle->control));
	return make_bool(env, value);
}

LIBUI_FUNCTION(append) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(value, 1);
	uiMultilineEntryAppend(uiMultilineEntry(handle->control), value);
	free(value);
	return NULL;
}

napi_value _libui_init_multilineEntry (napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getText);
	LIBUI_EXPORT(setText);
	LIBUI_EXPORT(getReadOnly);
	LIBUI_EXPORT(setReadOnly);
	LIBUI_EXPORT(append);
	LIBUI_EXPORT(onChanged);
	return module;
}
