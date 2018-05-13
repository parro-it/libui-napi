#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "AreaPath";

static void free_path(napi_env env, void *finalize_data, void *finalize_hint) {
	uiDrawPath *font = (uiDrawPath *)finalize_data;
	free(font);
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
	LIBUI_EXPORT(end);
	return module;
}
