#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "AreaStrokeParams";

static void free_sp(napi_env env, void *finalize_data, void *finalize_hint) {
	uiDrawStrokeParams *sp = (uiDrawStrokeParams *)finalize_data;
	if (sp->NumDashes > 0) {
		free(sp->Dashes);
	}
	free(sp);
}

LIBUI_FUNCTION(create) {
	uiDrawStrokeParams *sp = malloc(sizeof(uiDrawStrokeParams));

	sp->Cap = 0;
	sp->Join = 0;
	sp->Thickness = 1;
	sp->MiterLimit = uiDrawDefaultMiterLimit;
	sp->Dashes = NULL;
	sp->NumDashes = 0;
	sp->DashPhase = 0;

	napi_value external;
	napi_status status = napi_create_external(env, sp, free_sp, NULL, &external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return external;
}

LIBUI_FUNCTION(setThickness) {
	INIT_ARGS(2);

	ARG_POINTER(uiDrawStrokeParams, handle, 0);
	ARG_DOUBLE(v, 1);

	handle->Thickness = v;

	return NULL;
}

LIBUI_FUNCTION(getThickness) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawStrokeParams, handle, 0);

	double v = handle->Thickness;
	return make_double(env, v);
}

napi_value _libui_init_area_stroke(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getThickness);
	LIBUI_EXPORT(setThickness);
	return module;
}
