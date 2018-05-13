#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "AreaBrush";

static void free_brush_solid(napi_env env, void *finalize_data, void *finalize_hint) {
	uiDrawBrush *brush = (uiDrawBrush *)finalize_data;
	free(brush);
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
	napi_status status = napi_create_external(env, brush, free_brush_solid, NULL, &external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return external;
}

// static void free_brush_gradient(napi_env env, void *finalize_data, void *finalize_hint) {
// 	uiDrawBrush *brush = (uiDrawBrush *)finalize_data;
// 	if (brush->NumStops > 0) {
// 		free(brush->Stops);
// 	}
// 	free(brush);
// }

// LIBUI_FUNCTION(createGradientLinear) {
// 	INIT_ARGS(2);

// 	ARG_DOUBLE(x0, 0);
// 	ARG_DOUBLE(y0, 1);
// 	ARG_DOUBLE(x1, 2);
// 	ARG_DOUBLE(y1, 3);
// 	napi_value stops = args[4];

// 	int numStops;
// 	napi_status status = napi_array_elgnth(env, stops, &numStops);
// 	CHECK_STATUS_THROW(status, napi_array_elgnth);

// 	uiDrawBrush *brush = malloc(sizeof(uiDrawBrush));

// 	brush->Type = uiDrawBrushTypeLinearGradient;
// 	brush->NumStops = numStops;

// 	// napi_get_element
// 	napi_status napi_get_element(napi_env env,
//                              napi_value object,
//                              uint32_t index,
//                              napi_value* result);

// 	napi_value external;
// 	napi_status status = napi_create_external(env, brush, free_brush, NULL, &external);
// 	CHECK_STATUS_THROW(status, napi_create_external);

// 	return external;
// }

napi_value _libui_init_area_brush(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(createSolid);
	// LIBUI_EXPORT(createGradientLinear);
	// LIBUI_EXPORT(createGradientRadial);
	return module;
}
