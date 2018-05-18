#include <ui.h>
#include "napi_utils.h"
#include "values.h"

static const char *MODULE = "FontAttribute";

static void free_font_attribute(napi_env env, void *finalize_data, void *finalize_hint) {
	// uiAttribute *attr = (uiAttribute *)finalize_data;
	// if (!appended) {
	// 	uiFreeAttribute(a);
	// }
}

static napi_value create_attribute_external(napi_env env, uiAttribute *attr) {
	napi_value attr_external;
	napi_status status = napi_create_external(env, attr, free_font_attribute, NULL, &attr_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return attr_external;
}

LIBUI_FUNCTION(getType) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttribute, attr, 0);

	return make_int32(env, uiAttributeGetType(attr));
}

LIBUI_FUNCTION(getFamily) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttribute, attr, 0);

	return make_utf8_string(env, uiAttributeFamily(attr));
}

LIBUI_FUNCTION(getSize) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttribute, attr, 0);

	return make_double(env, uiAttributeSize(attr));
}

LIBUI_FUNCTION(getWeight) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttribute, attr, 0);

	return make_int32(env, uiAttributeWeight(attr));
}

LIBUI_FUNCTION(getItalic) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttribute, attr, 0);

	return make_int32(env, uiAttributeItalic(attr));
}

LIBUI_FUNCTION(getStretch) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttribute, attr, 0);

	return make_int32(env, uiAttributeStretch(attr));
}

LIBUI_FUNCTION(getUnderline) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttribute, attr, 0);

	return make_int32(env, uiAttributeUnderline(attr));
}

LIBUI_FUNCTION(getColor) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttribute, attr, 0);

	double r;
	double g;
	double b;
	double a;

	uiAttributeColor(attr, &r, &g, &b, &a);

	return make_color(env, r, g, b, a);
}

// std::vector<Color> FontAttribute::getUnderlineColorInternal() {
// 	double r;
// 	double g;
// 	double b;
// 	double alpha;

// 	uiUnderlineColor type;
// 	uiAttributeUnderlineColor(a, &type, &r, &g, &b, &alpha);

// 	return std::vector<Color>{Color(r, g, b, alpha), Color(type, 0, 0, 0)};
// }

// OpenTypeFeatures FontAttribute::getOTFeaturesInternal() {
// 	return OpenTypeFeatures((uiOpenTypeFeatures *)uiAttributeFeatures(a));
// }

LIBUI_FUNCTION(createFamily) {
	INIT_ARGS(1);
	ARG_STRING(family, 0);
	return create_attribute_external(env, uiNewFamilyAttribute(family));
}

LIBUI_FUNCTION(createSize) {
	INIT_ARGS(1);
	ARG_DOUBLE(size, 0);
	return create_attribute_external(env, uiNewSizeAttribute(size));
}

LIBUI_FUNCTION(createWeight) {
	INIT_ARGS(1);
	ARG_INT32(weight, 0);
	return create_attribute_external(env, uiNewWeightAttribute(weight));
}

LIBUI_FUNCTION(createItalic) {
	INIT_ARGS(1);
	ARG_INT32(italic, 0);
	return create_attribute_external(env, uiNewItalicAttribute(italic));
}

LIBUI_FUNCTION(createStretch) {
	INIT_ARGS(1);
	ARG_INT32(stretch, 0);
	return create_attribute_external(env, uiNewStretchAttribute(stretch));
}

LIBUI_FUNCTION(createColor) {
	INIT_ARGS(4);
	ARG_DOUBLE(r, 0);
	ARG_DOUBLE(g, 1);
	ARG_DOUBLE(b, 2);
	ARG_DOUBLE(a, 3);

	return create_attribute_external(env, uiNewColorAttribute(r, g, b, a));
}

LIBUI_FUNCTION(createBackgroundColor) {
	INIT_ARGS(4);
	ARG_DOUBLE(r, 0);
	ARG_DOUBLE(g, 1);
	ARG_DOUBLE(b, 2);
	ARG_DOUBLE(a, 3);

	return create_attribute_external(env, uiNewBackgroundAttribute(r, g, b, a));
}

LIBUI_FUNCTION(createUnderline) {
	INIT_ARGS(1);
	ARG_INT32(underline, 0);
	return create_attribute_external(env, uiNewUnderlineAttribute(underline));
}

LIBUI_FUNCTION(createUnderlineColor) {
	INIT_ARGS(5);
	ARG_INT32(underline, 0);
	ARG_DOUBLE(r, 1);
	ARG_DOUBLE(g, 2);
	ARG_DOUBLE(b, 3);
	ARG_DOUBLE(a, 4);
	return create_attribute_external(env, uiNewUnderlineColorAttribute(underline, r, g, b, a));
}

// FontAttribute FontAttribute::newOTFeatures(OpenTypeFeatures *otf) {
// 	return FontAttribute(uiNewFeaturesAttribute(otf->getHandle()));
// }

napi_value _libui_init_font_attribute(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(getType);
	LIBUI_EXPORT(getFamily);
	LIBUI_EXPORT(getSize);
	LIBUI_EXPORT(getWeight);
	LIBUI_EXPORT(getItalic);
	LIBUI_EXPORT(getStretch);
	LIBUI_EXPORT(getUnderline);
	LIBUI_EXPORT(getColor);

	LIBUI_EXPORT(createFamily);
	LIBUI_EXPORT(createSize);
	LIBUI_EXPORT(createWeight);
	LIBUI_EXPORT(createItalic);
	LIBUI_EXPORT(createStretch);
	LIBUI_EXPORT(createColor);
	LIBUI_EXPORT(createBackgroundColor);
	LIBUI_EXPORT(createUnderline);
	LIBUI_EXPORT(createUnderlineColor);
	return module;
}
