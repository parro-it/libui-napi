#include <ui.h>
#include "napi_utils.h"

static const char *MODULE = "FontDescriptor";

typedef struct {
	uiFontDescriptor *font;
	bool fromButton;
} FontHandle;

static void free_font_descriptor(napi_env env, void *finalize_data, void *finalize_hint) {
	FontHandle *h = (FontHandle *)finalize_data;
	if (h->fromButton) {
		uiFreeFontButtonFont(h->font);
	} else {
		free(h->font->Family);
	}
	free(h->font);
	free(h);
}

napi_value create_font_descriptor(napi_env env, FontHandle *h) {
	napi_value font_external;
	napi_status status = napi_create_external(env, h, free_font_descriptor, NULL, &font_external);
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

	FontHandle *h = malloc(sizeof(FontHandle));
	h->font = malloc(sizeof(uiFontDescriptor));
	h->font->Family = family;
	h->font->Size = size;
	h->font->Weight = weight;
	h->font->Italic = italic;
	h->font->Stretch = stretch;
	h->fromButton = false;
	return create_font_descriptor(env, h);
}

LIBUI_FUNCTION(getFamily) {
	INIT_ARGS(1);
	ARG_POINTER(FontHandle, h, 0);
	return make_utf8_string(env, h->font->Family);
}

LIBUI_FUNCTION(getSize) {
	INIT_ARGS(1);
	ARG_POINTER(FontHandle, h, 0);
	return make_double(env, h->font->Size);
}

LIBUI_FUNCTION(getWeight) {
	INIT_ARGS(1);
	ARG_POINTER(FontHandle, h, 0);
	return make_int32(env, h->font->Weight);
}

LIBUI_FUNCTION(getItalic) {
	INIT_ARGS(1);
	ARG_POINTER(FontHandle, h, 0);
	return make_int32(env, h->font->Italic);
}

LIBUI_FUNCTION(getStretch) {
	INIT_ARGS(1);
	ARG_POINTER(FontHandle, h, 0);
	return make_int32(env, h->font->Stretch);
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
