#include <ui.h>
#include "napi_utils.h"
#include "values.h"

static const char *MODULE = "AttributedString";

// font-attribute.c
typedef struct {
	uiAttribute *attr;
	bool appended;
} AttributeHandle;
napi_value create_attribute_external(napi_env env, AttributeHandle *h);

static void free_string(napi_env env, void *finalize_data, void *finalize_hint) {
	uiAttributedString *str = (uiAttributedString *)finalize_data;
	uiFreeAttributedString(str);
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(1);
	ARG_STRING(s, 0);

	napi_value str_external;
	napi_status status =
		napi_create_external(env, uiNewAttributedString(s), free_string, NULL, &str_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	free(s);
	return str_external;
}

LIBUI_FUNCTION(toString) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttributedString, str, 0);

	return make_utf8_string(env, uiAttributedStringString(str));
}

LIBUI_FUNCTION(toStringLen) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttributedString, str, 0);

	return make_uint32(env, uiAttributedStringLen(str));
}

LIBUI_FUNCTION(appendUnattributed) {
	INIT_ARGS(2);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_STRING(s, 1);

	uiAttributedStringAppendUnattributed(str, s);

	free(s);
	return NULL;
}

LIBUI_FUNCTION(insertUnattributed) {
	INIT_ARGS(3);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_STRING(s, 1);
	ARG_UINT32(pos, 2);

	uiAttributedStringInsertAtUnattributed(str, s, pos);

	free(s);
	return NULL;
}

LIBUI_FUNCTION(deleteString) {
	INIT_ARGS(3);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_UINT32(start, 1);
	ARG_UINT32(end, 2);

	uiAttributedStringDelete(str, start, end);

	return NULL;
}

LIBUI_FUNCTION(setAttribute) {
	INIT_ARGS(4);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_POINTER(AttributeHandle, h, 1);
	ARG_UINT32(start, 2);
	ARG_UINT32(end, 3);

	uiAttributedStringSetAttribute(str, h->attr, start, end);
	h->appended = true;

	return NULL;
}

// forEach

LIBUI_FUNCTION(appendAttributed) {
	INIT_ARGS(3);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_STRING(s, 1);
	napi_value array = argv[2];

	uint32_t length;
	napi_status status = napi_get_array_length(env, array, &length);
	CHECK_STATUS_THROW(status, napi_get_array_length);

	size_t start = uiAttributedStringLen(str);
	size_t end = start + strlen(s);

	uiAttributedStringAppendUnattributed(str, s);
	free(s);

	for (size_t i = 0; i < length; i++) {
		napi_value v;
		status = napi_get_element(env, array, i, &v);
		CHECK_STATUS_THROW(status, napi_get_element);

		AttributeHandle *h;
		status = napi_get_value_external(env, v, (void **)&h);
		CHECK_STATUS_THROW(status, napi_get_value_external);

		uiAttributedStringSetAttribute(str, h->attr, start, end);
		h->appended = true;
	}

	return NULL;
}

LIBUI_FUNCTION(insertAttributed) {
	INIT_ARGS(4);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_STRING(s, 1);
	ARG_UINT32(start, 2);
	napi_value array = argv[3];

	uint32_t length;
	napi_status status = napi_get_array_length(env, array, &length);
	CHECK_STATUS_THROW(status, napi_get_array_length);

	size_t end = start + strlen(s);

	uiAttributedStringInsertAtUnattributed(str, s, start);
	free(s);
	for (size_t i = 0; i < length; i++) {
		napi_value v;
		status = napi_get_element(env, array, i, &v);
		CHECK_STATUS_THROW(status, napi_get_element);

		AttributeHandle *h;
		status = napi_get_value_external(env, v, (void **)&h);
		CHECK_STATUS_THROW(status, napi_get_value_external);

		uiAttributedStringSetAttribute(str, h->attr, start, end);
		h->appended = true;
	}

	return NULL;
}

LIBUI_FUNCTION(numGraphemes) {
	INIT_ARGS(1);
	ARG_POINTER(uiAttributedString, str, 0);

	return make_uint32(env, uiAttributedStringNumGraphemes(str));
}

LIBUI_FUNCTION(byteIndexToGrapheme) {
	INIT_ARGS(2);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_UINT32(pos, 1);

	return make_uint32(env, uiAttributedStringByteIndexToGrapheme(str, pos));
}

LIBUI_FUNCTION(graphemeToByteIndex) {
	INIT_ARGS(2);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_UINT32(pos, 1);

	return make_uint32(env, uiAttributedStringGraphemeToByteIndex(str, pos));
}

typedef struct {
	napi_env *env;
	napi_value *cb;
	napi_value *null;
} ForEachData;

static uiForEach forEach_cb(const uiAttributedString *s, const uiAttribute *a, size_t start,
							size_t end, void *data) {

	ForEachData *d = (ForEachData *)data;
	napi_env env = *(d->env);

	AttributeHandle *h = malloc(sizeof(AttributeHandle));
	h->attr = (uiAttribute *)a;
	h->appended = true;

	// TODO set appended
	napi_value args[3] = {create_attribute_external(env, h), make_uint32(env, start),
						  make_uint32(env, end)};

	napi_value result;

	napi_status status = napi_call_function(env, *(d->null), *(d->cb), 3, args, &result);
	// CHECK_STATUS_THROW(status, napi_call_function);

	bool b;
	status = napi_get_value_bool(env, result, &b);
	// CHECK_STATUS_THROW(status, napi_get_value_bool);

	return b ? uiForEachStop : uiForEachContinue;
}

LIBUI_FUNCTION(forEach) {
	INIT_ARGS(2);

	ARG_POINTER(uiAttributedString, str, 0);
	napi_value cb = argv[1];

	napi_value null;
	napi_status status = napi_get_null(env, &null);
	CHECK_STATUS_THROW(status, napi_get_null);

	ForEachData d = {&env, &cb, &null};

	uiAttributedStringForEachAttribute(str, forEach_cb, &d);

	return NULL;
}

napi_value _libui_init_font_string(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(toString);
	LIBUI_EXPORT(toStringLen);
	LIBUI_EXPORT(appendUnattributed);
	LIBUI_EXPORT(insertUnattributed);
	LIBUI_EXPORT(deleteString);
	LIBUI_EXPORT(setAttribute);
	LIBUI_EXPORT(appendAttributed);
	LIBUI_EXPORT(insertAttributed);

	LIBUI_EXPORT(numGraphemes);
	LIBUI_EXPORT(byteIndexToGrapheme);
	LIBUI_EXPORT(graphemeToByteIndex);

	LIBUI_EXPORT(forEach);

	return module;
}
