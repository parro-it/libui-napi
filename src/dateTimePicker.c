#include <stdbool.h>
#include <time.h>
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

LIBUI_FUNCTION(onChanged) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onChanged");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiDateTimePickerOnChanged(uiDateTimePicker(handle->control),
							  CALLBACK_OF(uiDateTimePicker, control_event_cb), event);

	return NULL;
}

LIBUI_FUNCTION(setTime) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_INT64(value, 1);
	struct tm *tm_value = localtime((const long *)&value);
	uiDateTimePickerSetTime(uiDateTimePicker(handle->control), tm_value);
	return NULL;
}

LIBUI_FUNCTION(getTime) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	struct tm time;
	uiDateTimePickerTime(uiDateTimePicker(handle->control), &time);
	// char s[1024];
	// strftime(s, 1024, "%d/%m/%Y %H:%M", &time);

	// printf("%s\n", s);
	return make_int64(env, mktime(&time));
}

napi_value _libui_init_datetimepicker(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(createDatePicker);
	LIBUI_EXPORT(createTimePicker);
	LIBUI_EXPORT(createDateTimePicker);
	LIBUI_EXPORT(getTime);
	LIBUI_EXPORT(setTime);
	LIBUI_EXPORT(onChanged);
	return module;
}
