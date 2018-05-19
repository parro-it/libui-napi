#include <ui.h>
#include "napi_utils.h"
#include "values.h"

static const char *MODULE = "OpenTypeFeatures";

static void free_otf(napi_env env, void *finalize_data, void *finalize_hint) {
	uiOpenTypeFeatures *otf = (uiOpenTypeFeatures *)finalize_data;
	uiFreeOpenTypeFeatures(otf);
}

static napi_value create_otf_external(napi_env env, uiOpenTypeFeatures *otf) {
	napi_value otf_external;
	napi_status status = napi_create_external(env, otf, free_otf, NULL, &otf_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return otf_external;
}

LIBUI_FUNCTION(create) {
	uiOpenTypeFeatures *otf = uiNewOpenTypeFeatures();

	return create_otf_external(env, otf);
}

LIBUI_FUNCTION(clone) {
	INIT_ARGS(1);

	ARG_POINTER(uiOpenTypeFeatures, otf, 0);

	return create_otf_external(env, uiOpenTypeFeaturesClone(otf));
}

LIBUI_FUNCTION(addTag) {
	INIT_ARGS(3);

	ARG_POINTER(uiOpenTypeFeatures, otf, 0);
	ARG_STRING(tag, 1);
	ARG_UINT32(value, 2);

	uiOpenTypeFeaturesAdd(otf, tag[0], tag[1], tag[2], tag[3], value);

	return NULL;
}

LIBUI_FUNCTION(removeTag) {
	INIT_ARGS(2);

	ARG_POINTER(uiOpenTypeFeatures, otf, 0);
	ARG_STRING(tag, 1);

	uiOpenTypeFeaturesRemove(otf, tag[0], tag[1], tag[2], tag[3]);

	return NULL;
}

LIBUI_FUNCTION(getTag) {
	INIT_ARGS(2);

	ARG_POINTER(uiOpenTypeFeatures, otf, 0);
	ARG_STRING(tag, 1);

	unsigned int value = 0;
	unsigned int exists = uiOpenTypeFeaturesGet(otf, tag[0], tag[1], tag[2], tag[3], &value);

	if (exists) {
		return make_uint32(env, value);
	} else {
		napi_value null;
		napi_status status = napi_get_null(env, &null);
		CHECK_STATUS_THROW(status, napi_get_null);

		return null;
	}
}

// foreach

napi_value _libui_init_font_opentype(napi_env env, napi_value exports) {
	DEFINE_MODULE();

	LIBUI_EXPORT(create);
	LIBUI_EXPORT(clone);
	LIBUI_EXPORT(addTag);
	LIBUI_EXPORT(removeTag);
	LIBUI_EXPORT(getTag);

	return module;
}
