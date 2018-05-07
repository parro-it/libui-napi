#include <stdbool.h>
#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "DateTimePickers";

LIBUI_FUNCTION(createDatePicker) {
	uiControl *ctrl = uiControl(uiNewDatePicker());
	return control_handle_new(env, ctrl, "datePicker");
}

LIBUI_FUNCTION(createTimePicker) {
	uiControl *ctrl = uiControl(uiNewTimePicker());
	return control_handle_new(env, ctrl, "datePicker");
}

LIBUI_FUNCTION(createDateTimePicker) {
	uiControl *ctrl = uiControl(uiNewDateTimePicker());
	return control_handle_new(env, ctrl, "dateTimePicker");
}

napi_value _libui_init_datetimepicker(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(createDatePicker);
	LIBUI_EXPORT(createTimePicker);
	LIBUI_EXPORT(createDateTimePicker);
	return module;
}
