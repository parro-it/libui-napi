#include <stdbool.h>
#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Slider";

LIBUI_FUNCTION(create) {
	INIT_ARGS(2);
	ARG_INT32(min, 0);
	ARG_INT32(max, 1);
	uiControl *ctrl = uiControl(uiNewSlider(min, max));
	return control_handle_new(env, ctrl, "slider");
}

LIBUI_FUNCTION(onChanged) {
	INIT_ARGS(2);

	ARG_CTRL_HANDLE("slider", handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onChanged");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiSliderOnChanged(uiSlider(handle->control), CALLBACK_OF(uiSlider, control_event_cb), event);

	return NULL;
}

LIBUI_FUNCTION(setValue) {
	INIT_ARGS(2);
	ARG_CTRL_HANDLE("slider", handle, 0);
	ARG_INT32(value, 1);

	uiSliderSetValue(uiSlider(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getValue) {
	INIT_ARGS(1);
	ARG_CTRL_HANDLE("slider", handle, 0);

	int value = uiSliderValue(uiSlider(handle->control));
	return make_int32(env, value);
}

napi_value _libui_init_slider(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getValue);
	LIBUI_EXPORT(setValue);
	LIBUI_EXPORT(onChanged);
	return module;
}
