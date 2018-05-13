#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "AreaUtil";

LIBUI_FUNCTION(context_save) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawContext, ctx, 0);

	uiDrawSave(ctx);

	return NULL;
}

LIBUI_FUNCTION(context_restore) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawContext, ctx, 0);

	uiDrawRestore(ctx);

	return NULL;
}

napi_value _libui_init_area_util(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(context_save);
	LIBUI_EXPORT(context_restore);
	return module;
}
