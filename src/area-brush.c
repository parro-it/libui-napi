#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "AreaBrush";

static void free_brush(napi_env env, void *finalize_data, void *finalize_hint) {
	uiDrawBrush *font = (uiDrawBrush *)finalize_data;
	free(font);
}

LIBUI_FUNCTION(createSolid) {
	INIT_ARGS(4);

	ARG_DOUBLE(r, 0);
	ARG_DOUBLE(g, 1);
	ARG_DOUBLE(b, 2);
	ARG_DOUBLE(a, 3);

	uiDrawBrush *brush = malloc(sizeof(uiDrawBrush));

	brush->R = r;
	brush->G = g;
	brush->B = b;
	brush->A = a;

	brush->Type = uiDrawBrushTypeSolid;

	napi_value external;
	napi_status status = napi_create_external(env, brush, free_brush, NULL, &external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return external;
}

napi_value _libui_init_area_brush(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(createSolid);
	return module;
}
