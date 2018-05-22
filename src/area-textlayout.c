#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"
#include "values.h"

static const char *MODULE = "DrawTextLayout";

// font-descriptor.c
typedef struct {
	uiFontDescriptor *font;
	bool fromButton;
} FontHandle;

typedef struct {
	uiDrawTextLayout *layout;
	napi_ref str_ref;
	napi_ref font_ref;
} LayoutHandle;

static void free_layout(napi_env env, void *finalize_data, void *finalize_hint) {
	LayoutHandle *h = (LayoutHandle *)finalize_data;
	uiDrawFreeTextLayout(h->layout);
	napi_delete_reference(env, h->str_ref);
	napi_delete_reference(env, h->font_ref);
	free(h);
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(4);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_POINTER(FontHandle, font_h, 1);
	ARG_DOUBLE(width, 2);
	ARG_INT32(align, 3);

	napi_value str_value = argv[0];
	napi_value font_value = argv[1];

	LayoutHandle *h = malloc(sizeof(LayoutHandle));

	uiDrawTextLayoutParams params = {str, font_h->font, width, (uiDrawTextAlign)align};

	h->layout = uiDrawNewTextLayout(&params);

	napi_status status = napi_create_reference(env, str_value, 1, &(h->str_ref));
	CHECK_STATUS_THROW(status, napi_create_reference);
	status = napi_create_reference(env, font_value, 1, &(h->font_ref));
	CHECK_STATUS_THROW(status, napi_create_reference);

	napi_value external;
	status = napi_create_external(env, h, free_layout, NULL, &external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return external;
}

LIBUI_FUNCTION(getExtents) {
	INIT_ARGS(1);

	ARG_POINTER(LayoutHandle, h, 0);

	double width;
	double height;

	uiDrawTextLayoutExtents(h->layout, &width, &height);

	return make_size_double(env, width, height);
}

napi_value _libui_init_area_textlayout(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getExtents);

	return module;
}
