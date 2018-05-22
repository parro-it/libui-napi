#include <ui.h>
#include "napi_utils.h"
#include "values.h"

static const char *MODULE = "FontAttribute";

// font-opentype.c
typedef struct {
	uiOpenTypeFeatures *otf;
	bool shouldFree;
} FeaturesHandle;
napi_value create_otf_external(napi_env env, FeaturesHandle *h);

typedef struct {
	uiAttribute *attr;
	bool appended;
} AttributeHandle;

static void free_font_attribute(napi_env env, void *finalize_data, void *finalize_hint) {
	AttributeHandle *h = (AttributeHandle *)finalize_data;
	if (!h->appended) {
		uiFreeAttribute(h->attr);
	}
	free(h);
}

napi_value create_attribute_external(napi_env env, AttributeHandle *attr) {
	napi_value attr_external;
	napi_status status = napi_create_external(env, attr, free_font_attribute, NULL, &attr_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return attr_external;
}

LIBUI_FUNCTION(setAppended) {
	INIT_ARGS(1);
	ARG_POINTER(AttributeHandle, h, 0);

	h->appended = true;

	return NULL;
}

#define GET(NAME, TYPE, FUNC)                                                                      \
	LIBUI_FUNCTION(NAME) {                                                                         \
		INIT_ARGS(1);                                                                              \
		ARG_POINTER(AttributeHandle, h, 0);                                                        \
		return TYPE(env, FUNC(h->attr));                                                           \
	}

GET(getType, make_int32, uiAttributeGetType);
GET(getFamily, make_utf8_string, uiAttributeFamily);
GET(getSize, make_double, uiAttributeSize);
GET(getWeight, make_int32, uiAttributeWeight);
GET(getItalic, make_int32, uiAttributeItalic);
GET(getStretch, make_int32, uiAttributeStretch);
GET(getUnderline, make_int32, uiAttributeUnderline);

LIBUI_FUNCTION(getOTFeatures) {
	INIT_ARGS(1);
	ARG_POINTER(AttributeHandle, h, 0);

	FeaturesHandle *otf_h = malloc(sizeof(FeaturesHandle));
	otf_h->otf = (uiOpenTypeFeatures *)uiAttributeFeatures(h->attr);
	otf_h->shouldFree = false;

	return create_otf_external(env, otf_h);
}

LIBUI_FUNCTION(getColor) {
	INIT_ARGS(1);
	ARG_POINTER(AttributeHandle, h, 0);

	double r;
	double g;
	double b;
	double a;

	uiAttributeColor(h->attr, &r, &g, &b, &a);

	return make_color(env, r, g, b, a);
}

LIBUI_FUNCTION(getUnderlineColor) {
	INIT_ARGS(1);
	ARG_POINTER(AttributeHandle, h, 0);

	double r;
	double g;
	double b;
	double a;

	uiUnderlineColor type;
	uiAttributeUnderlineColor(h->attr, &type, &r, &g, &b, &a);

	napi_value obj;

	napi_handle_scope scope;
	napi_status status = napi_open_handle_scope(env, &scope);
	CHECK_STATUS_THROW(status, napi_open_handle_scope);

	status = napi_create_object(env, &obj);
	CHECK_STATUS_THROW(status, napi_create_object);

	status = napi_set_named_property(env, obj, "color", make_color(env, r, g, b, a));
	CHECK_STATUS_THROW(status, napi_set_named_property);

	status = napi_set_named_property(env, obj, "type", make_int32(env, type));
	CHECK_STATUS_THROW(status, napi_set_named_property);

	status = napi_close_handle_scope(env, scope);
	CHECK_STATUS_THROW(status, napi_close_handle_scope);

	return obj;
}

#define CREATE(NAME, TYPE, FUNC)                                                                   \
	LIBUI_FUNCTION(NAME) {                                                                         \
		INIT_ARGS(1);                                                                              \
		TYPE(v, 0);                                                                                \
                                                                                                   \
		AttributeHandle *h = malloc(sizeof(AttributeHandle));                                      \
		h->attr = FUNC(v);                                                                         \
		h->appended = false;                                                                       \
                                                                                                   \
		return create_attribute_external(env, h);                                                  \
	}

CREATE(createSize, ARG_DOUBLE, uiNewSizeAttribute);
CREATE(createWeight, ARG_INT32, uiNewWeightAttribute);
CREATE(createItalic, ARG_INT32, uiNewItalicAttribute);
CREATE(createStretch, ARG_INT32, uiNewStretchAttribute);
CREATE(createUnderline, ARG_INT32, uiNewUnderlineAttribute);

LIBUI_FUNCTION(createFamily) {
	INIT_ARGS(1);
	ARG_STRING(v, 0);

	AttributeHandle *h = malloc(sizeof(AttributeHandle));
	h->attr = uiNewFamilyAttribute(v);
	h->appended = false;

	free(v);
	return create_attribute_external(env, h);
}

LIBUI_FUNCTION(createOTFeatures) {
	INIT_ARGS(1);
	ARG_POINTER(FeaturesHandle, otf_h, 0);

	AttributeHandle *h = malloc(sizeof(AttributeHandle));
	h->attr = uiNewFeaturesAttribute(otf_h->otf);
	h->appended = false;

	return create_attribute_external(env, h);
}

LIBUI_FUNCTION(createColor) {
	INIT_ARGS(4);
	ARG_DOUBLE(r, 0);
	ARG_DOUBLE(g, 1);
	ARG_DOUBLE(b, 2);
	ARG_DOUBLE(a, 3);

	AttributeHandle *h = malloc(sizeof(AttributeHandle));
	h->attr = uiNewColorAttribute(r, g, b, a);
	h->appended = false;

	return create_attribute_external(env, h);
}

LIBUI_FUNCTION(createBackgroundColor) {
	INIT_ARGS(4);
	ARG_DOUBLE(r, 0);
	ARG_DOUBLE(g, 1);
	ARG_DOUBLE(b, 2);
	ARG_DOUBLE(a, 3);

	AttributeHandle *h = malloc(sizeof(AttributeHandle));
	h->attr = uiNewBackgroundAttribute(r, g, b, a);
	h->appended = false;

	return create_attribute_external(env, h);
}

LIBUI_FUNCTION(createUnderlineColor) {
	INIT_ARGS(5);
	ARG_INT32(underline, 0);
	ARG_DOUBLE(r, 1);
	ARG_DOUBLE(g, 2);
	ARG_DOUBLE(b, 3);
	ARG_DOUBLE(a, 4);

	AttributeHandle *h = malloc(sizeof(AttributeHandle));
	h->attr = uiNewUnderlineColorAttribute(underline, r, g, b, a);
	h->appended = false;

	return create_attribute_external(env, h);
}

napi_value _libui_init_font_attribute(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(setAppended);

	LIBUI_EXPORT(getType);
	LIBUI_EXPORT(getFamily);
	LIBUI_EXPORT(getSize);
	LIBUI_EXPORT(getWeight);
	LIBUI_EXPORT(getItalic);
	LIBUI_EXPORT(getStretch);
	LIBUI_EXPORT(getUnderline);
	LIBUI_EXPORT(getColor);
	LIBUI_EXPORT(getUnderlineColor);
	LIBUI_EXPORT(getOTFeatures);

	LIBUI_EXPORT(createFamily);
	LIBUI_EXPORT(createSize);
	LIBUI_EXPORT(createWeight);
	LIBUI_EXPORT(createItalic);
	LIBUI_EXPORT(createStretch);
	LIBUI_EXPORT(createColor);
	LIBUI_EXPORT(createBackgroundColor);
	LIBUI_EXPORT(createUnderline);
	LIBUI_EXPORT(createUnderlineColor);
	LIBUI_EXPORT(createOTFeatures);
	return module;
}
