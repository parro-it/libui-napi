#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "AreaContext";

// area-textlayout.c
typedef struct {
	uiDrawTextLayout *layout;
	napi_ref str_ref;
	napi_ref font_ref;
} LayoutHandle;

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

LIBUI_FUNCTION(transform) {
	INIT_ARGS(2);

	ARG_POINTER(uiDrawContext, ctx, 0);
	ARG_POINTER(uiDrawMatrix, m, 1);

	uiDrawTransform(ctx, m);

	return NULL;
}

LIBUI_FUNCTION(clip) {
	INIT_ARGS(2);

	ARG_POINTER(uiDrawContext, ctx, 0);
	ARG_POINTER(uiDrawPath, p, 1);

	uiDrawClip(ctx, p);

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

LIBUI_FUNCTION(text) {
	INIT_ARGS(4);

	ARG_POINTER(uiDrawContext, ctx, 0);
	ARG_DOUBLE(x, 1);
	ARG_DOUBLE(y, 2);
	ARG_POINTER(LayoutHandle, h, 3);

	uiDrawText(ctx, h->layout, x, y);

	return NULL;
}

napi_value _libui_init_area_context(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(fill);
	LIBUI_EXPORT(stroke);
	LIBUI_EXPORT(transform);
	LIBUI_EXPORT(clip);
	LIBUI_EXPORT(save);
	LIBUI_EXPORT(restore);
	LIBUI_EXPORT(text);
	return module;
}
