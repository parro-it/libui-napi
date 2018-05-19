#include <ui.h>
#include "napi_utils.h"
#include "values.h"

static const char *MODULE = "AttributedString";

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

	return NULL;
}

LIBUI_FUNCTION(insertUnattributed) {
	INIT_ARGS(3);
	ARG_POINTER(uiAttributedString, str, 0);
	ARG_STRING(s, 1);
	ARG_UINT32(pos, 2);

	uiAttributedStringInsertAtUnattributed(str, s, pos);

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
	ARG_POINTER(uiAttribute, a, 1);
	ARG_UINT32(start, 2);
	ARG_UINT32(end, 3);

	uiAttributedStringSetAttribute(str, a, start, end);

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
	for (size_t i = 0; i < length; i++) {
		napi_value v;
		status = napi_get_element(env, array, i, &v);
		CHECK_STATUS_THROW(status, napi_get_element);

		uiAttribute *attr;
		status = napi_get_value_external(env, v, (void **)&attr);
		CHECK_STATUS_THROW(status, napi_get_value_external);

		uiAttributedStringSetAttribute(str, attr, start, end);
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
	for (size_t i = 0; i < length; i++) {
		napi_value v;
		status = napi_get_element(env, array, i, &v);
		CHECK_STATUS_THROW(status, napi_get_element);

		uiAttribute *attr;
		status = napi_get_value_external(env, v, (void **)&attr);
		CHECK_STATUS_THROW(status, napi_get_value_external);

		uiAttributedStringSetAttribute(str, attr, start, end);
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

	return module;
}
