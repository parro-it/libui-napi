#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Button";

LIBUI_FUNCTION(create) {
	INIT_ARGS(1);
	ARG_STRING(label, 0);

	uiControl *ctrl = uiControl(uiNewButton(label));
	free(label);
	return control_handle_new(env, ctrl, "button");
}

LIBUI_FUNCTION(onClicked) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onClicked");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiButtonOnClicked(uiButton(handle->control), CALLBACK_OF(uiButton, control_event_cb), event);

	return NULL;
}

LIBUI_FUNCTION(setText) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_STRING(value, 1);
	uiButtonSetText(uiButton(handle->control), value);
	free(value);
	return NULL;
}

LIBUI_FUNCTION(getText) {
	INIT_ARGS(1);

	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	char *char_ptr = uiButtonText(uiButton(handle->control));
	napi_value result = make_utf8_string(env, char_ptr);
	uiFreeText(char_ptr);
	return result;
}

napi_value _libui_init_button(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getText);
	LIBUI_EXPORT(setText);
	LIBUI_EXPORT(onClicked);
	return module;
}
