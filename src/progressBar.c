#include <stdbool.h>
#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "ProgressBar";

LIBUI_FUNCTION(create) {
	uiControl *ctrl = uiControl(uiNewProgressBar());
	return control_handle_new(env, ctrl, "progressBar");
}

LIBUI_FUNCTION(setValue) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_INT32(value, 1);

	uiProgressBarSetValue(uiProgressBar(handle->control), value);
	return NULL;
}

napi_value _libui_init_progressbar(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(setValue);
	return module;
}
