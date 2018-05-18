#include <stdbool.h>
#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Spinbox";

LIBUI_FUNCTION(create) {
	INIT_ARGS(2);
	ARG_INT32(min, 0);
	ARG_INT32(max, 1);
	uiControl *ctrl = uiControl(uiNewSpinbox(min, max));
	return control_handle_new(env, ctrl, "spinbox");
}

LIBUI_FUNCTION(onChanged) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onChanged");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiSpinboxOnChanged(uiSpinbox(handle->control), CALLBACK_OF(uiSpinbox, control_event_cb), event);

	return NULL;
}

LIBUI_FUNCTION(setValue) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_INT32(value, 1);

	uiSpinboxSetValue(uiSpinbox(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getValue) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	int value = uiSpinboxValue(uiSpinbox(handle->control));
	return make_int32(env, value);
}

napi_value _libui_init_spinbox(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getValue);
	LIBUI_EXPORT(setValue);
	LIBUI_EXPORT(onChanged);
	return module;
}
