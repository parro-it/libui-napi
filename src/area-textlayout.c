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

static void free_layout(napi_env env, void *finalize_data, void *finalize_hint) {
	uiDrawTextLayout *layout = (uiDrawTextLayout *)finalize_data;
	uiDrawFreeTextLayout(layout);
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(4);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_POINTER(FontHandle, h, 1);
	ARG_DOUBLE(width, 2);
	ARG_INT32(align, 3);

	// ok with memory?
	uiDrawTextLayoutParams params = {str, h->font, width, (uiDrawTextAlign)align};

	uiDrawTextLayout *layout = uiDrawNewTextLayout(&params);

	napi_value external;
	napi_status status = napi_create_external(env, layout, free_layout, NULL, &external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return external;
}

LIBUI_FUNCTION(getExtents) {
	INIT_ARGS(1);

	ARG_POINTER(uiDrawTextLayout, layout, 0);

	double width;
	double height;

	uiDrawTextLayoutExtents(layout, &width, &height);

	return make_size_double(env, width, height);
}

napi_value _libui_init_area_textlayout(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getExtents);

	return module;
}
