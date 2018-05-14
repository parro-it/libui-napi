#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "AreaMatrix";

static void free_brush_solid(napi_env env, void *finalize_data, void *finalize_hint) {
	uiDrawMatrix *matrix = (uiDrawMatrix *)finalize_data;
	free(matrix);
}

LIBUI_FUNCTION(create) {
	uiDrawMatrix *matrix = malloc(sizeof(uiDrawMatrix));

	napi_value external;
	napi_status status = napi_create_external(env, matrix, free_brush_solid, NULL, &external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return external;
}

LIBUI_FUNCTION(setIdentity) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawMatrix, m, 0);

	uiDrawMatrixSetIdentity(m);

	return NULL;
}

LIBUI_FUNCTION(scale) {
	INIT_ARGS(5);

	ARG_POINTER(uiDrawMatrix, m, 0);
	ARG_DOUBLE(xCenter, 1);
	ARG_DOUBLE(yCenter, 2);
	ARG_DOUBLE(x, 3);
	ARG_DOUBLE(y, 4);

	uiDrawMatrixScale(m, xCenter, yCenter, x, y);

	return NULL;
}

LIBUI_FUNCTION(translate) {
	INIT_ARGS(3);

	ARG_POINTER(uiDrawMatrix, m, 0);
	ARG_DOUBLE(x, 1);
	ARG_DOUBLE(y, 2);

	uiDrawMatrixTranslate(m, x, y);

	return NULL;
}

LIBUI_FUNCTION(rotate) {
	INIT_ARGS(4);

	ARG_POINTER(uiDrawMatrix, m, 0);
	ARG_DOUBLE(x, 1);
	ARG_DOUBLE(y, 2);
	ARG_DOUBLE(amount, 3);

	uiDrawMatrixRotate(m, x, y, amount);

	return NULL;
}

LIBUI_FUNCTION(skew) {
	INIT_ARGS(5);

	ARG_POINTER(uiDrawMatrix, m, 0);
	ARG_DOUBLE(x, 1);
	ARG_DOUBLE(y, 2);
	ARG_DOUBLE(xAmount, 3);
	ARG_DOUBLE(yAmount, 4);

	uiDrawMatrixSkew(m, x, y, xAmount, yAmount);

	return NULL;
}

LIBUI_FUNCTION(multiply) {
	INIT_ARGS(2);
	ARG_POINTER(uiDrawMatrix, m, 0);
	ARG_POINTER(uiDrawMatrix, m2, 1);

	uiDrawMatrixMultiply(m, m2);

	return NULL;
}

LIBUI_FUNCTION(invertible) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawMatrix, m, 0);

	return make_bool(env, uiDrawMatrixInvertible(m));
}

LIBUI_FUNCTION(invert) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawMatrix, m, 0);

	return make_bool(env, uiDrawMatrixInvert(m));
}

LIBUI_FUNCTION(set) {
	INIT_ARGS(4);

	ARG_POINTER(uiDrawMatrix, m, 0);
	ARG_INT32(i, 1);
	ARG_INT32(j, 2);
	ARG_DOUBLE(v, 3);

	switch (i) {
	case 0:
		switch (j) {
		case 0:
			m->M11 = v;
			break;
		case 1:
			m->M12 = v;
			break;
		}
		break;
	case 1:
		switch (j) {
		case 0:
			m->M21 = v;
			break;
		case 1:
			m->M22 = v;
			break;
		}
		break;
	case 2:
		switch (j) {
		case 0:
			m->M31 = v;
			break;
		case 1:
			m->M32 = v;
			break;
		}
		break;
	}

	return NULL;
}

LIBUI_FUNCTION(get) {
	INIT_ARGS(3);

	ARG_POINTER(uiDrawMatrix, m, 0);
	ARG_INT32(i, 1);
	ARG_INT32(j, 2);

	double v = 0;

	switch (i) {
	case 0:
		switch (j) {
		case 0:
			v = m->M11;
			break;
		case 1:
			v = m->M12;
			break;
		}
		break;
	case 1:
		switch (j) {
		case 0:
			v = m->M21;
			break;
		case 1:
			v = m->M22;
			break;
		}
		break;
	case 2:
		switch (j) {
		case 0:
			v = m->M31;
			break;
		case 1:
			v = m->M32;
			break;
		}
		break;
	}

	return make_double(env, v);
}

napi_value _libui_init_area_matrix(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(setIdentity);
	LIBUI_EXPORT(scale);
	LIBUI_EXPORT(translate);
	LIBUI_EXPORT(rotate);
	LIBUI_EXPORT(skew);
	LIBUI_EXPORT(multiply);
	LIBUI_EXPORT(invertible);
	LIBUI_EXPORT(invert);
	LIBUI_EXPORT(get);
	LIBUI_EXPORT(set);
	return module;
}
