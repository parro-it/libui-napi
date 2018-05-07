#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Separator";

LIBUI_FUNCTION(createVertical) {
	uiControl *ctrl = uiControl(uiNewVerticalSeparator());
	return control_handle_new(env, ctrl, "verticalSeparator");
}

LIBUI_FUNCTION(createHorizontal) {
	uiControl *ctrl = uiControl(uiNewHorizontalSeparator());
	return control_handle_new(env, ctrl, "horizontalSeparator");
}

napi_value _libui_init_separator(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(createVertical);
	LIBUI_EXPORT(createHorizontal);
	return module;
}
