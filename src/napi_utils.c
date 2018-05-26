#include "napi_utils.h"
#include <uv.h>
#define UNINITIALIZED 100042

#if UI_NODE_DEBUG
static char enabled_debug_module[100];
#endif

napi_ref null_ref;
size_t env_var_size = UNINITIALIZED;

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

napi_value make_int64(napi_env env, long value) {
	napi_value value_js;

	napi_status status = napi_create_int64(env, value, &value_js);
	CHECK_STATUS_THROW(status, napi_create_int64);

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
#if UI_NODE_DEBUG

bool debug_enabled_for_module(const char *module) {
	if (env_var_size == UNINITIALIZED) {
		uv_os_getenv("DEBUG", enabled_debug_module, &env_var_size);
	}

	return (strncmp(module, enabled_debug_module, env_var_size) == 0);
}

#endif