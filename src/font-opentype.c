#include <ui.h>
#include "napi_utils.h"
#include "values.h"

static const char *MODULE = "OpenTypeFeatures";

typedef struct {
	uiOpenTypeFeatures *otf;
	bool shouldFree;
} FeaturesHandle;

static void free_otf(napi_env env, void *finalize_data, void *finalize_hint) {
	FeaturesHandle *h = (FeaturesHandle *)finalize_data;
	if (h->shouldFree) {
		uiFreeOpenTypeFeatures(h->otf);
	}
	free(h);
}

napi_value create_otf_external(napi_env env, FeaturesHandle *h) {
	napi_value otf_external;
	napi_status status = napi_create_external(env, h, free_otf, NULL, &otf_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	return otf_external;
}

LIBUI_FUNCTION(create) {
	FeaturesHandle *h = malloc(sizeof(FeaturesHandle));
	h->otf = uiNewOpenTypeFeatures();
	h->shouldFree = true;

	return create_otf_external(env, h);
}

LIBUI_FUNCTION(clone) {
	INIT_ARGS(1);

	ARG_POINTER(FeaturesHandle, h2, 0);

	FeaturesHandle *h = malloc(sizeof(FeaturesHandle));
	h->otf = uiOpenTypeFeaturesClone(h2->otf);
	h->shouldFree = true;

	return create_otf_external(env, h);
}

LIBUI_FUNCTION(addTag) {
	INIT_ARGS(3);

	ARG_POINTER(FeaturesHandle, h, 0);
	ARG_STRING(tag, 1);
	ARG_UINT32(value, 2);

	uiOpenTypeFeaturesAdd(h->otf, tag[0], tag[1], tag[2], tag[3], value);

	free(tag);
	return NULL;
}

LIBUI_FUNCTION(removeTag) {
	INIT_ARGS(2);

	ARG_POINTER(FeaturesHandle, h, 0);
	ARG_STRING(tag, 1);

	uiOpenTypeFeaturesRemove(h->otf, tag[0], tag[1], tag[2], tag[3]);

	free(tag);
	return NULL;
}

LIBUI_FUNCTION(getTag) {
	INIT_ARGS(2);

	ARG_POINTER(FeaturesHandle, h, 0);
	ARG_STRING(tag, 1);

	unsigned int value = 0;
	unsigned int exists = uiOpenTypeFeaturesGet(h->otf, tag[0], tag[1], tag[2], tag[3], &value);

	free(tag);

	if (exists) {
		return make_uint32(env, value);
	} else {
		napi_value null;
		napi_status status = napi_get_null(env, &null);
		CHECK_STATUS_THROW(status, napi_get_null);

		return null;
	}
}

typedef struct {
	napi_env *env;
	napi_value *cb;
	napi_value *null;
} ForEachData;

static uiForEach forEach_cb(const uiOpenTypeFeatures *otf, char a, char b, char c, char d,
							uint32_t value, void *data) {
	ForEachData *dat = (ForEachData *)data;
	napi_env env = *(dat->env);

	const char tag[5] = {a, b, c, d, '\0'};

	napi_value args[2] = {make_utf8_string(env, tag), make_uint32(env, value)};

	napi_value result_v;

	napi_status status = napi_call_function(env, *(dat->null), *(dat->cb), 2, args, &result_v);
	if (status != napi_ok) {
		const napi_extended_error_info *result;
		napi_get_last_error_info(env, &result);
		char err[1024];
		snprintf(err, 1024, "napi_call_function failed with code %d: %s\n",
				 result->engine_error_code, result->error_message);
		napi_throw_error(env, NULL, err);
		return uiForEachStop;
	}

	bool result;
	status = napi_get_value_bool(env, result_v, &result);
	if (status != napi_ok) {
		const napi_extended_error_info *result;
		napi_get_last_error_info(env, &result);
		char err[1024];
		snprintf(err, 1024, "napi_get_value_bool failed with code %d: %s\n",
				 result->engine_error_code, result->error_message);
		napi_throw_error(env, NULL, err);
		return uiForEachStop;
	}

	return result ? uiForEachStop : uiForEachContinue;
}

LIBUI_FUNCTION(forEach) {
	INIT_ARGS(2);

	ARG_POINTER(FeaturesHandle, h, 0);
	napi_value cb = argv[1];

	napi_value null;
	napi_status status = napi_get_null(env, &null);
	CHECK_STATUS_THROW(status, napi_get_null);

	ForEachData d = {&env, &cb, &null};

	uiOpenTypeFeaturesForEach(h->otf, forEach_cb, &d);

	return NULL;
}

napi_value _libui_init_font_opentype(napi_env env, napi_value exports) {
	DEFINE_MODULE();

	LIBUI_EXPORT(create);
	LIBUI_EXPORT(clone);
	LIBUI_EXPORT(addTag);
	LIBUI_EXPORT(removeTag);
	LIBUI_EXPORT(getTag);
	LIBUI_EXPORT(forEach);

	return module;
}
