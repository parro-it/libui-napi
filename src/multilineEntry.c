#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char* MODULE = "MultilineEntry";

static napi_value create (napi_env env, napi_callback_info info) {
	uiControl *ctrl = uiControl(uiNewNonWrappingMultilineEntry());
	return control_handle_new(env, ctrl, "multilineEntry");
}

napi_value _libui_init_multilineEntry (napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	return module;
}
