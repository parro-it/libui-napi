#define LIBUI_EXPORT(FN) \
	napi_value FN##_fn; \
	napi_create_function(env, #FN, NAPI_AUTO_LENGTH, FN, NULL, & FN##_fn); \
	napi_set_named_property(env, exports, #FN, FN##_fn)

#define CHECK_STATUS_THROW(STATUS, FN) \
	if (STATUS != napi_ok) { \
		const napi_extended_error_info* result; \
		napi_get_last_error_info(env, &result); \
		char err[1024]; \
		snprintf(err, 1024, #FN " failed with code %d: %s\n", result->engine_error_code, result->error_message); \
		napi_throw_error(env, NULL, err); \
		return NULL; \
	}

#define CHECK_STATUS_UNCAUGHT(STATUS, FN, ERROR_RET) \
	if (STATUS != napi_ok) { \
		const napi_extended_error_info* result; \
		napi_get_last_error_info(env, &result); \
		char err[1024]; \
		snprintf(err, 1024, #FN " failed with code %d: %s\n", result->engine_error_code, result->error_message); \
		napi_value error; \
		napi_value error_msg; \
		napi_create_string_utf8(env, err, NAPI_AUTO_LENGTH, &error_msg); \
		napi_create_error(env, NULL, error_msg, &error); \
		napi_fatal_exception(env, error); \
		return ERROR_RET; \
	}
