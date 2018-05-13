#include <ui.h>
#include "napi_utils.h"

static const char *MODULE = "FontDescriptor";

static void free_font_descriptor(napi_env env, void *finalize_data, void *finalize_hint) {
	uiFontDescriptor *font = (uiFontDescriptor *)finalize_data;
	free(font);
}

napi_value create_with_descriptor(napi_env env, uiFontDescriptor *font) {
	napi_value font_external;
	napi_status status =
		napi_create_external(env, font, free_font_descriptor, NULL, &font_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return font_external;
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(5);
	ARG_STRING(family, 0);
	ARG_DOUBLE(size, 1);
	ARG_INT32(weight, 2);
	ARG_INT32(italic, 3);
	ARG_INT32(stretch, 4);

	uiFontDescriptor *font = malloc(sizeof(uiFontDescriptor));
	font->Family = family;
	font->Size = size;
	font->Weight = weight;
	font->Italic = italic;
	font->Stretch = stretch;
	return create_with_descriptor(env, font);
}

LIBUI_FUNCTION(getFamily) {
	INIT_ARGS(1);
	ARG_POINTER(uiFontDescriptor, font, 0);
	return make_utf8_string(env, font->Family);
}

LIBUI_FUNCTION(getSize) {
	INIT_ARGS(1);
	ARG_POINTER(uiFontDescriptor, font, 0);
	return make_double(env, font->Size);
}

LIBUI_FUNCTION(getWeight) {
	INIT_ARGS(1);
	ARG_POINTER(uiFontDescriptor, font, 0);
	return make_int32(env, font->Weight);
}

LIBUI_FUNCTION(getItalic) {
	INIT_ARGS(1);
	ARG_POINTER(uiFontDescriptor, font, 0);
	return make_int32(env, font->Italic);
}

LIBUI_FUNCTION(getStretch) {
	INIT_ARGS(1);
	ARG_POINTER(uiFontDescriptor, font, 0);
	return make_int32(env, font->Stretch);
}

napi_value _libui_init_font_descriptor(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getFamily);
	LIBUI_EXPORT(getSize);
	LIBUI_EXPORT(getWeight);
	LIBUI_EXPORT(getItalic);
	LIBUI_EXPORT(getStretch);
	return module;
}
