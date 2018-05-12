#include "napi_utils.h"

napi_value make_bool(napi_env env, bool value) {
	napi_value value_js;

	napi_status status = napi_get_boolean(env, value, &value_js);
	CHECK_STATUS_THROW(status, napi_get_boolean);

	return value_js;
}

napi_value make_double(napi_env env, double value) {
	napi_value value_js;

	napi_status status = napi_create_double(env, value, &value_js);
	CHECK_STATUS_THROW(status, napi_create_double);

	return value_js;
}

napi_value make_int32(napi_env env, int value) {
	napi_value value_js;

	napi_status status = napi_create_int32(env, value, &value_js);
	CHECK_STATUS_THROW(status, napi_create_int32);

	return value_js;
}

napi_value make_uint32(napi_env env, unsigned int value) {
	napi_value value_js;

	napi_status status = napi_create_uint32(env, value, &value_js);
	CHECK_STATUS_THROW(status, napi_create_uint32);

	return value_js;
}

napi_value make_utf8_string(napi_env env, const char *char_ptr) {
	napi_value result;

	napi_status status = napi_create_string_utf8(env, char_ptr, NAPI_AUTO_LENGTH, &result);
	CHECK_STATUS_THROW(status, napi_create_string_utf8);

	return result;
}
