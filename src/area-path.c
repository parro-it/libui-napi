#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "AreaPath";

static void free_path(napi_env env, void *finalize_data, void *finalize_hint) {
	uiDrawPath *path = (uiDrawPath *)finalize_data;
	uiDrawFreePath(path);
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(1);

	ARG_INT32(mode, 0);

	uiDrawPath *p = uiDrawNewPath(mode);

	napi_value external;
	napi_status status = napi_create_external(env, p, free_path, NULL, &external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return external;
}

LIBUI_FUNCTION(addRectangle) {
	INIT_ARGS(5);

	ARG_POINTER(uiDrawPath, handle, 0);
	ARG_DOUBLE(x, 1);
	ARG_DOUBLE(y, 2);
	ARG_DOUBLE(width, 3);
	ARG_DOUBLE(height, 4);

	uiDrawPathAddRectangle(handle, x, y, width, height);

	return NULL;
}

LIBUI_FUNCTION(newFigure) {
	INIT_ARGS(3);

	ARG_POINTER(uiDrawPath, handle, 0);
	ARG_DOUBLE(x, 1);
	ARG_DOUBLE(y, 2);

	uiDrawPathNewFigure(handle, x, y);

	return NULL;
}

LIBUI_FUNCTION(newFigureWithArc) {
	INIT_ARGS(7);

	ARG_POINTER(uiDrawPath, handle, 0);
	ARG_DOUBLE(xCenter, 1);
	ARG_DOUBLE(yCenter, 2);
	ARG_DOUBLE(radius, 3);
	ARG_DOUBLE(startAngle, 4);
	ARG_DOUBLE(sweep, 5);
	ARG_BOOL(negative, 6);

	uiDrawPathNewFigureWithArc(handle, xCenter, yCenter, radius, startAngle, sweep, negative);

	return NULL;
}

LIBUI_FUNCTION(lineTo) {
	INIT_ARGS(3);

	ARG_POINTER(uiDrawPath, handle, 0);
	ARG_DOUBLE(x, 1);
	ARG_DOUBLE(y, 2);

	uiDrawPathLineTo(handle, x, y);

	return NULL;
}

LIBUI_FUNCTION(arcTo) {
	INIT_ARGS(7);

	ARG_POINTER(uiDrawPath, handle, 0);
	ARG_DOUBLE(xCenter, 1);
	ARG_DOUBLE(yCenter, 2);
	ARG_DOUBLE(radius, 3);
	ARG_DOUBLE(startAngle, 4);
	ARG_DOUBLE(sweep, 5);
	ARG_BOOL(negative, 6);

	uiDrawPathArcTo(handle, xCenter, yCenter, radius, startAngle, sweep, negative);

	return NULL;
}

LIBUI_FUNCTION(bezierTo) {
	INIT_ARGS(7);

	ARG_POINTER(uiDrawPath, handle, 0);
	ARG_DOUBLE(c1x, 1);
	ARG_DOUBLE(c1y, 2);
	ARG_DOUBLE(c2x, 3);
	ARG_DOUBLE(c2y, 4);
	ARG_DOUBLE(endX, 5);
	ARG_DOUBLE(endY, 6);

	uiDrawPathBezierTo(handle, c1x, c1y, c2x, c2y, endX, endY);

	return NULL;
}

LIBUI_FUNCTION(closeFigure) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawPath, handle, 0);

	uiDrawPathCloseFigure(handle);

	return NULL;
}

LIBUI_FUNCTION(end) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawPath, handle, 0);

	uiDrawPathEnd(handle);

	return NULL;
}

napi_value _libui_init_area_path(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(addRectangle);
	LIBUI_EXPORT(newFigure);
	LIBUI_EXPORT(newFigureWithArc);
	LIBUI_EXPORT(lineTo);
	LIBUI_EXPORT(arcTo);
	LIBUI_EXPORT(bezierTo);
	LIBUI_EXPORT(closeFigure);
	LIBUI_EXPORT(end);
	return module;
}
