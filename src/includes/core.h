#include <node_api.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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


#define ARG_INT32(ARG_NAME, ARG_IDX) \
	int32_t ARG_NAME; \
	status = napi_get_value_int32(env, argv[ARG_IDX], &ARG_NAME); \
	if (status != napi_ok) { \
		const napi_extended_error_info* result; \
		napi_get_last_error_info(env, &result); \
		char err[1024]; \
		snprintf(err, 1024, "Argument " #ARG_NAME ": %s\n", result->error_message); \
		napi_throw_type_error(env, NULL, err); \
		return NULL; \
	}

#define ARG_BOOL(ARG_NAME, ARG_IDX) \
	bool ARG_NAME; \
	status = napi_get_value_bool(env, argv[ARG_IDX], &ARG_NAME); \
	if (status != napi_ok) { \
		const napi_extended_error_info* result; \
		napi_get_last_error_info(env, &result); \
		char err[1024]; \
		snprintf(err, 1024, "Argument " #ARG_NAME ": %s\n", result->error_message); \
		napi_throw_type_error(env, NULL, err); \
		return NULL; \
	}

#define ARG_STRING(ARG_NAME, ARG_IDX) \
	size_t string_len; \
	status = napi_get_value_string_utf8(env, argv[ARG_IDX], NULL, 0, &string_len); \
	CHECK_STATUS_THROW(status, napi_get_value_string_utf8);\
	char* ARG_NAME = malloc(string_len + 1); \
	status = napi_get_value_string_utf8(env, argv[ARG_IDX], ARG_NAME, string_len + 1, &string_len); \
	CHECK_STATUS_THROW(status, napi_get_value_string_utf8);\
	if (status != napi_ok) { \
		const napi_extended_error_info* result; \
		napi_get_last_error_info(env, &result); \
		char err[1024]; \
		snprintf(err, 1024, "Argument " #ARG_NAME ": %s\n", result->error_message); \
		napi_throw_type_error(env, NULL, err); \
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

void _libui_init_window (napi_env env, napi_value exports);
void _libui_init_core (napi_env env, napi_value exports);
