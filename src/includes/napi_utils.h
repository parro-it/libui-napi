#ifndef LIBUI_NODE_UTILS_H__
#define LIBUI_NODE_UTILS_H__

#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function arguments

#define INIT_ARGS(ARGS_COUNT)                                                                      \
	napi_value argv[ARGS_COUNT];                                                                   \
	size_t argc = ARGS_COUNT;                                                                      \
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);                                          \
	if (argc < ARGS_COUNT) {                                                                       \
		napi_throw_error(env, "EINVAL", "Too few arguments");                                      \
		return NULL;                                                                               \
	}

#define ARG_INT32(ARG_NAME, ARG_IDX)                                                               \
	int32_t ARG_NAME;                                                                              \
	{                                                                                              \
		napi_status status = napi_get_value_int32(env, argv[ARG_IDX], &ARG_NAME);                  \
		if (status != napi_ok) {                                                                   \
			const napi_extended_error_info *result;                                                \
			napi_get_last_error_info(env, &result);                                                \
			char err[1024];                                                                        \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s", result->error_message);              \
			napi_throw_type_error(env, NULL, err);                                                 \
			return NULL;                                                                           \
		}                                                                                          \
	}

#define ARG_UINT32(ARG_NAME, ARG_IDX)                                                              \
	uint32_t ARG_NAME;                                                                             \
	{                                                                                              \
		napi_status status = napi_get_value_uint32(env, argv[ARG_IDX], &ARG_NAME);                 \
		if (status != napi_ok) {                                                                   \
			const napi_extended_error_info *result;                                                \
			napi_get_last_error_info(env, &result);                                                \
			char err[1024];                                                                        \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s", result->error_message);              \
			napi_throw_type_error(env, NULL, err);                                                 \
			return NULL;                                                                           \
		}                                                                                          \
	}

#define ARG_INT64(ARG_NAME, ARG_IDX)                                                               \
	int64_t ARG_NAME;                                                                              \
	{                                                                                              \
		napi_status status = napi_get_value_int64(env, argv[ARG_IDX], &ARG_NAME);                  \
		if (status != napi_ok) {                                                                   \
			const napi_extended_error_info *result;                                                \
			napi_get_last_error_info(env, &result);                                                \
			char err[1024];                                                                        \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s", result->error_message);              \
			napi_throw_type_error(env, NULL, err);                                                 \
			return NULL;                                                                           \
		}                                                                                          \
	}

#define ARG_BUFFER(ARG_NAME, ARG_IDX)                                                              \
	void *ARG_NAME##__ptr;                                                                         \
	size_t ARG_NAME##__len;                                                                        \
	{                                                                                              \
		napi_status status =                                                                       \
			napi_get_buffer_info(env, argv[ARG_IDX], &ARG_NAME##__ptr, &ARG_NAME##__len);          \
		if (status != napi_ok) {                                                                   \
			const napi_extended_error_info *result;                                                \
			napi_get_last_error_info(env, &result);                                                \
			char err[1024];                                                                        \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s", result->error_message);              \
			napi_throw_type_error(env, NULL, err);                                                 \
			return NULL;                                                                           \
		}                                                                                          \
	}

#define ARG_DOUBLE(ARG_NAME, ARG_IDX)                                                              \
	double ARG_NAME;                                                                               \
	{                                                                                              \
		napi_status status = napi_get_value_double(env, argv[ARG_IDX], &ARG_NAME);                 \
		if (status != napi_ok) {                                                                   \
			const napi_extended_error_info *result;                                                \
			napi_get_last_error_info(env, &result);                                                \
			char err[1024];                                                                        \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s", result->error_message);              \
			napi_throw_type_error(env, NULL, err);                                                 \
			return NULL;                                                                           \
		}                                                                                          \
	}

#define ARG_BOOL(ARG_NAME, ARG_IDX)                                                                \
	bool ARG_NAME;                                                                                 \
	{                                                                                              \
		napi_status status = napi_get_value_bool(env, argv[ARG_IDX], &ARG_NAME);                   \
		if (status != napi_ok) {                                                                   \
			const napi_extended_error_info *result;                                                \
			napi_get_last_error_info(env, &result);                                                \
			char err[1024];                                                                        \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s", result->error_message);              \
			napi_throw_type_error(env, NULL, err);                                                 \
			return NULL;                                                                           \
		}                                                                                          \
	}

#define ARG_POINTER(ARG_TYPE, ARG_NAME, ARG_IDX)                                                   \
	ARG_TYPE *ARG_NAME;                                                                            \
	{                                                                                              \
		napi_status status = napi_get_value_external(env, argv[ARG_IDX], (void **)&ARG_NAME);      \
		if (status != napi_ok) {                                                                   \
			const napi_extended_error_info *result;                                                \
			napi_get_last_error_info(env, &result);                                                \
			char err[1024];                                                                        \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s", result->error_message);              \
			napi_throw_type_error(env, NULL, err);                                                 \
			return NULL;                                                                           \
		}                                                                                          \
	}

#define ARG_STRING(ARG_NAME, ARG_IDX)                                                              \
	char *ARG_NAME;                                                                                \
	{                                                                                              \
		size_t string_len;                                                                         \
		napi_status status = napi_get_value_string_utf8(env, argv[ARG_IDX], NULL, 0, &string_len); \
		if (status != napi_ok) {                                                                   \
			const napi_extended_error_info *result;                                                \
			napi_get_last_error_info(env, &result);                                                \
			char err[1024];                                                                        \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s", result->error_message);              \
			napi_throw_type_error(env, NULL, err);                                                 \
			return NULL;                                                                           \
		}                                                                                          \
		ARG_NAME = malloc(string_len + 1);                                                         \
		status =                                                                                   \
			napi_get_value_string_utf8(env, argv[ARG_IDX], ARG_NAME, string_len + 1, &string_len); \
		CHECK_STATUS_THROW(status, napi_get_value_string_utf8);                                    \
		if (status != napi_ok) {                                                                   \
			const napi_extended_error_info *result;                                                \
			napi_get_last_error_info(env, &result);                                                \
			char err[1024];                                                                        \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s", result->error_message);              \
			napi_throw_type_error(env, NULL, err);                                                 \
			return NULL;                                                                           \
		}                                                                                          \
	}

extern napi_ref null_ref;

#define ARG_CB_REF(ARG_NAME, ARG_IDX)                                                              \
	napi_ref ARG_NAME;                                                                             \
	{                                                                                              \
		napi_valuetype arg_type;                                                                   \
		napi_status status = napi_typeof(env, argv[ARG_IDX], &arg_type);                           \
                                                                                                   \
		if (arg_type == napi_null) {                                                               \
			ARG_NAME = null_ref;                                                                   \
		} else {                                                                                   \
			napi_value global;                                                                     \
			status = napi_get_global(env, &global);                                                \
			CHECK_STATUS_THROW(status, napi_get_global);                                           \
                                                                                                   \
			napi_value function_constructor;                                                       \
			status = napi_get_named_property(env, global, "Function", &function_constructor);      \
			CHECK_STATUS_THROW(status, napi_get_named_property);                                   \
                                                                                                   \
			bool is_function = false;                                                              \
			status = napi_instanceof(env, argv[ARG_IDX], function_constructor, &is_function);      \
			if (status != napi_ok || !is_function) {                                               \
				napi_throw_type_error(env, NULL,                                                   \
									  "Argument " #ARG_NAME ": a function was expected");          \
				return NULL;                                                                       \
			}                                                                                      \
                                                                                                   \
			status = napi_create_reference(env, argv[ARG_IDX], 1, &ARG_NAME);                      \
			if (status != napi_ok) {                                                               \
				const napi_extended_error_info *result;                                            \
				napi_get_last_error_info(env, &result);                                            \
				char err[1024];                                                                    \
				snprintf(err, 1024, "Argument " #ARG_NAME ": %s", result->error_message);          \
				napi_throw_type_error(env, NULL, err);                                             \
				return NULL;                                                                       \
			}                                                                                      \
		}                                                                                          \
	}

// return values
/*
#define RETURN_EXTERNAL(POINTER, FINALIZE_CB) \
	{ \
		napi_value ret; \
		napi_status status = napi_create_external(env, POINTER, FINALIZE_CB,
NULL, &ret); \
		CHECK_STATUS_THROW(status, napi_create_external); \
		return ret; \
	}
*/

// function export

#define LIBUI_FUNCTION(FN_NAME) static napi_value FN_NAME(napi_env env, napi_callback_info info)

#define LIBUI_EXPORT(FN)                                                                           \
	{                                                                                              \
		napi_value func;                                                                           \
		napi_status status = napi_create_function(env, #FN, NAPI_AUTO_LENGTH, FN, NULL, &func);    \
		CHECK_STATUS_THROW(status, napi_create_function);                                          \
		status = napi_set_named_property(env, module, #FN, func);                                  \
		CHECK_STATUS_THROW(status, napi_set_named_property);                                       \
	}

#define DEFINE_MODULE()                                                                            \
	napi_value module;                                                                             \
	{                                                                                              \
		napi_status status = napi_create_object(env, &module);                                     \
		CHECK_STATUS_THROW(status, napi_create_object);                                            \
		status = napi_set_named_property(env, exports, MODULE, module);                            \
		CHECK_STATUS_THROW(status, napi_set_named_property);                                       \
	}

// errors checking

#define CHECK_STATUS_THROW(STATUS, FN)                                                             \
	if (STATUS != napi_ok) {                                                                       \
		const napi_extended_error_info *result;                                                    \
		napi_get_last_error_info(env, &result);                                                    \
		char err[1024];                                                                            \
		snprintf(err, 1024, #FN " failed with code %d: %s\n", result->engine_error_code,           \
				 result->error_message);                                                           \
		napi_throw_error(env, NULL, err);                                                          \
		return NULL;                                                                               \
	}

#define CHECK_STATUS_PENDING(STATUS, FN)                                                           \
	if (STATUS != napi_ok) {                                                                       \
		const napi_extended_error_info *result;                                                    \
		napi_get_last_error_info(env, &result);                                                    \
		char err[1024];                                                                            \
		snprintf(err, 1024, #FN " failed with code %d: %s\n", result->engine_error_code,           \
				 result->error_message);                                                           \
		napi_throw_error(env, NULL, err);                                                          \
		return napi_pending_exception;                                                             \
	}

#define CHECK_STATUS_UNCAUGHT(STATUS, FN, ERROR_RET)                                               \
	if (STATUS != napi_ok) {                                                                       \
		const napi_extended_error_info *result;                                                    \
		napi_get_last_error_info(env, &result);                                                    \
		char err[1024];                                                                            \
		snprintf(err, 1024, #FN " failed with code %d: %s\n", result->engine_error_code,           \
				 result->error_message);                                                           \
		napi_value error;                                                                          \
		napi_value error_msg;                                                                      \
		napi_create_string_utf8(env, err, NAPI_AUTO_LENGTH, &error_msg);                           \
		napi_create_error(env, NULL, error_msg, &error);                                           \
		napi_fatal_exception(env, error);                                                          \
		return ERROR_RET;                                                                          \
	}

#define ENSURE_NOT_DESTROYED()                                                                     \
	{                                                                                              \
		if (handle->is_destroyed) {                                                                \
			napi_throw_error(env, NULL, "Method called on destroyed control.");                    \
			return NULL;                                                                           \
		}                                                                                          \
	}
// debug

#define UI_NODE_DEBUG 0

#if UI_NODE_DEBUG

bool debug_enabled_for_module(const char *module);
#define LIBUI_NODE_DEBUG(msg)                                                                      \
	{                                                                                              \
		if (debug_enabled_for_module(MODULE)) {                                                    \
			fprintf(stderr, msg "\n");                                                             \
		}                                                                                          \
	}
#define LIBUI_NODE_DEBUG_F(msg, ...)                                                               \
	{                                                                                              \
		if (debug_enabled_for_module(MODULE)) {                                                    \
			fprintf(stderr, msg "\n", __VA_ARGS__);                                                \
		}                                                                                          \
	}
#else

#define LIBUI_NODE_DEBUG(msg) ;
#define LIBUI_NODE_DEBUG_F(msg, ...) ;

#endif

// return values
napi_value make_double(napi_env env, double value);
napi_value make_bool(napi_env env, bool value);
napi_value make_int32(napi_env env, int value);
napi_value make_int64(napi_env env, long value);
napi_value make_uint32(napi_env env, unsigned int value);
napi_value make_utf8_string(napi_env env, const char *char_ptr);

#endif
