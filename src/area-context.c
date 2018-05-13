#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "AreaContext";

LIBUI_FUNCTION(fill) {
	INIT_ARGS(3);

	ARG_POINTER(uiDrawContext, ctx, 0);
	ARG_POINTER(uiDrawPath, p, 1);
	ARG_POINTER(uiDrawBrush, b, 2);

	uiDrawFill(ctx, p, b);

	return NULL;
}

LIBUI_FUNCTION(stroke) {
	INIT_ARGS(4);

	ARG_POINTER(uiDrawContext, ctx, 0);
	ARG_POINTER(uiDrawPath, p, 1);
	ARG_POINTER(uiDrawBrush, b, 2);
	ARG_POINTER(uiDrawStrokeParams, sp, 3);

	uiDrawStroke(ctx, p, b, sp);

	return NULL;
}

LIBUI_FUNCTION(save) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawContext, ctx, 0);

	uiDrawSave(ctx);

	return NULL;
}

LIBUI_FUNCTION(restore) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawContext, ctx, 0);

	uiDrawRestore(ctx);

	return NULL;
}

napi_value _libui_init_area_context(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(fill);
	LIBUI_EXPORT(stroke);
	LIBUI_EXPORT(save);
	LIBUI_EXPORT(restore);
	return module;
}
