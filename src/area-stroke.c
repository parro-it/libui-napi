
#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "AreaStrokeParams";

#define SETTER_DOUBLE(FN, VALUE)                                                                   \
	LIBUI_FUNCTION(FN) {                                                                           \
		INIT_ARGS(2);                                                                              \
                                                                                                   \
		ARG_POINTER(uiDrawStrokeParams, handle, 0);                                                \
		ARG_DOUBLE(v, 1);                                                                          \
                                                                                                   \
		handle->VALUE = v;                                                                         \
                                                                                                   \
		return NULL;                                                                               \
	}

#define GETTER_DOUBLE(FN, VALUE)                                                                   \
	LIBUI_FUNCTION(FN) {                                                                           \
		INIT_ARGS(1);                                                                              \
                                                                                                   \
		ARG_POINTER(uiDrawStrokeParams, handle, 0);                                                \
                                                                                                   \
		double v = handle->VALUE;                                                                  \
		return make_double(env, v);                                                                \
	}

#define SETTER_INT(FN, VALUE)                                                                      \
	LIBUI_FUNCTION(FN) {                                                                           \
		INIT_ARGS(2);                                                                              \
                                                                                                   \
		ARG_POINTER(uiDrawStrokeParams, handle, 0);                                                \
		ARG_INT32(v, 1);                                                                           \
                                                                                                   \
		handle->VALUE = v;                                                                         \
                                                                                                   \
		return NULL;                                                                               \
	}

#define GETTER_INT(FN, VALUE)                                                                      \
	LIBUI_FUNCTION(FN) {                                                                           \
		INIT_ARGS(1);                                                                              \
                                                                                                   \
		ARG_POINTER(uiDrawStrokeParams, handle, 0);                                                \
                                                                                                   \
		int v = handle->VALUE;                                                                     \
		return make_int32(env, v);                                                                 \
	}

static void free_sp(napi_env env, void *finalize_data, void *finalize_hint) {
	uiDrawStrokeParams *sp = (uiDrawStrokeParams *)finalize_data;
	if (sp->NumDashes > 0) {
		free(sp->Dashes);
	}
	free(sp);
}

LIBUI_FUNCTION(create) {
	uiDrawStrokeParams *sp = calloc(1, sizeof(uiDrawStrokeParams));

	sp->Thickness = 1;
	sp->MiterLimit = uiDrawDefaultMiterLimit;

	napi_value external;
	napi_status status = napi_create_external(env, sp, free_sp, NULL, &external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return external;
}

SETTER_DOUBLE(setThickness, Thickness);
GETTER_DOUBLE(getThickness, Thickness);

SETTER_DOUBLE(setMiterLimit, MiterLimit);
GETTER_DOUBLE(getMiterLimit, MiterLimit);

SETTER_INT(setLineCap, Cap);
GETTER_INT(getLineCap, Cap);

SETTER_INT(setLineJoin, Join);
GETTER_INT(getLineJoin, Join);

SETTER_DOUBLE(setDashPhase, DashPhase);
GETTER_DOUBLE(getDashPhase, DashPhase);

LIBUI_FUNCTION(setDashes) {
	INIT_ARGS(2);

	ARG_POINTER(uiDrawStrokeParams, handle, 0);
	napi_value array = argv[1];

	if (handle->NumDashes > 0) {
		free(handle->Dashes);
	}

	uint32_t numDashes;
	napi_status status = napi_get_array_length(env, array, &numDashes);
	CHECK_STATUS_THROW(status, napi_get_array_length);

	handle->NumDashes = numDashes;
	handle->Dashes = malloc(numDashes * sizeof(double));

	for (uint32_t i = 0; i < numDashes; i++) {
		napi_value v;
		status = napi_get_element(env, array, i, &v);
		CHECK_STATUS_THROW(status, napi_get_element);

		status = napi_get_value_double(env, v, &(handle->Dashes[i]));
		CHECK_STATUS_THROW(status, napi_get_value_double);
	}

	return NULL;
}

LIBUI_FUNCTION(getDashes) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawStrokeParams, handle, 0);

	napi_value array;
	napi_status status = napi_create_array_with_length(env, handle->NumDashes, &array);
	CHECK_STATUS_THROW(status, napi_create_array_with_length);

	for (uint32_t i = 0; i < handle->NumDashes; i++) {
		napi_value v = make_double(env, handle->Dashes[i]);

		status = napi_set_element(env, array, i, v);
		CHECK_STATUS_THROW(status, napi_set_element);
	}

	return array;
}

napi_value _libui_init_area_stroke(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getThickness);
	LIBUI_EXPORT(setThickness);
	LIBUI_EXPORT(setMiterLimit);
	LIBUI_EXPORT(getMiterLimit);
	LIBUI_EXPORT(setLineCap);
	LIBUI_EXPORT(getLineCap);
	LIBUI_EXPORT(setLineJoin);
	LIBUI_EXPORT(getLineJoin);
	LIBUI_EXPORT(setDashPhase);
	LIBUI_EXPORT(getDashPhase);
	LIBUI_EXPORT(setDashes);
	LIBUI_EXPORT(getDashes);
	return module;
}
