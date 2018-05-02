#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"


static napi_value multilineEntryNew (napi_env env, napi_callback_info info) {
	uiControl *ctrl = uiControl(uiNewNonWrappingMultilineEntry());
	return control_handle_new(env, ctrl);
}

void _libui_init_multilineEntry (napi_env env, napi_value exports) {
	LIBUI_EXPORT(multilineEntryNew);
}
