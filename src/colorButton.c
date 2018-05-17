#include "ui.h"
#include "napi_utils.h"
#include "control.h"
#include "events.h"
#include "values.h"

static const char *MODULE = "ColorButton";

LIBUI_FUNCTION(create) {
	uiControl *ctrl = uiControl(uiNewColorButton());
	return control_handle_new(env, ctrl, "colorButton");
}

LIBUI_FUNCTION(onChanged) {
	INIT_ARGS(2);

	ARG_CTRL_HANDLE("colorButton", handle, 0);

	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onChanged");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiColorButtonOnChanged(uiColorButton(handle->control),
						   CALLBACK_OF(uiColorButton, control_event_cb), event);

	return NULL;
}

LIBUI_FUNCTION(setColor) {
	INIT_ARGS(5);
	ARG_CTRL_HANDLE("colorButton", handle, 0);

	ARG_DOUBLE(r, 1);
	ARG_DOUBLE(g, 2);
	ARG_DOUBLE(b, 3);
	ARG_DOUBLE(a, 4);

	uiColorButtonSetColor(uiColorButton(handle->control), r, g, b, a);
	return NULL;
}

LIBUI_FUNCTION(getColor) {
	INIT_ARGS(1);
	ARG_CTRL_HANDLE("colorButton", handle, 0);

	double r, g, b, a;

	uiColorButtonColor(uiColorButton(handle->control), &r, &g, &b, &a);
	return make_color(env, r, g, b, a);
}

napi_value _libui_init_colorbutton(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getColor);
	LIBUI_EXPORT(setColor);
	LIBUI_EXPORT(onChanged);
	return module;
}
