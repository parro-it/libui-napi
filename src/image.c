#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Image";

static void on_img_gc(napi_env env, void *finalize_data, void *finalize_hint) {
	uiImage *img = (uiImage *) finalize_data;
	/* TODO: uiFreeImage when? */
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(2);

	ARG_DOUBLE(width, 0);
	ARG_DOUBLE(height, 1);
	
	uiImage *img = uiNewImage(width, height);
	napi_value img_external;

	napi_status status = napi_create_external(env, img, on_img_gc, NULL, &img_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return img_external;
}

LIBUI_FUNCTION(append) {
	INIT_ARGS(5);

	ARG_POINTER(uiImage, image, 0);
	ARG_BUFFER(pixels, 1);
	ARG_INT32(pixelWidth, 2);
	ARG_INT32(pixelHeight, 3);
	ARG_INT32(byteStride, 4);
	printf("%d x %d : %d (len = %d)\n", pixelWidth, pixelHeight, byteStride, pixels__len);
	uiImageAppend(image, pixels__ptr, pixelWidth, pixelHeight, byteStride);
	return NULL;
}


napi_value _libui_init_image(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(append);

	return module;
}
