#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char* MODULE = "Label";

LIBUI_FUNCTION(create) {
	INIT_ARGS(1);
	ARG_STRING(value, 0);
	uiControl *ctrl = uiControl(uiNewLabel(value));
	free(value);
	return control_handle_new(env, ctrl, "label");
}

LIBUI_FUNCTION(setText) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(value, 1);
	uiLabelSetText(uiLabel(handle->control), value);
	free(value);
	return NULL;
}

LIBUI_FUNCTION(getText) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	char *char_ptr = uiLabelText(uiLabel(handle->control));
	napi_value result = make_utf8_string(env, char_ptr);
	uiFreeText(char_ptr);
	return result;
}

napi_value _libui_init_label (napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getText);
	LIBUI_EXPORT(setText);
	return module;
}
