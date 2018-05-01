#ifndef __LIBUI_NODE_H__
#define __LIBUI_NODE_H__

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

#define INIT_ARGS(ARGS_COUNT) \
	napi_value argv[ARGS_COUNT]; \
	size_t argc = ARGS_COUNT; \
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL); \
	if (argc < ARGS_COUNT) { \
		napi_throw_error(env, "EINVAL", "Too few arguments"); \
		return NULL; \
	}

#define ARG_INT32(ARG_NAME, ARG_IDX) \
	int32_t ARG_NAME; \
	{ \
		napi_status status = napi_get_value_int32(env, argv[ARG_IDX], &ARG_NAME); \
		if (status != napi_ok) { \
			const napi_extended_error_info* result; \
			napi_get_last_error_info(env, &result); \
			char err[1024]; \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s\n", result->error_message); \
			napi_throw_type_error(env, NULL, err); \
			return NULL; \
		} \
	}

#define ARG_BOOL(ARG_NAME, ARG_IDX) \
	bool ARG_NAME; \
	{ \
		napi_status status = napi_get_value_bool(env, argv[ARG_IDX], &ARG_NAME); \
		if (status != napi_ok) { \
			const napi_extended_error_info* result; \
			napi_get_last_error_info(env, &result); \
			char err[1024]; \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s\n", result->error_message); \
			napi_throw_type_error(env, NULL, err); \
			return NULL; \
		} \
	}

#define ARG_POINTER(ARG_TYPE, ARG_NAME, ARG_IDX) \
	ARG_TYPE *ARG_NAME; \
	{ \
		napi_status status = napi_get_value_external(env, argv[ARG_IDX], (void **) &ARG_NAME); \
		if (status != napi_ok) { \
			const napi_extended_error_info* result; \
			napi_get_last_error_info(env, &result); \
			char err[1024]; \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s\n", result->error_message); \
			napi_throw_type_error(env, NULL, err); \
			return NULL; \
		} \
	}

#define ARG_STRING(ARG_NAME, ARG_IDX) \
	char* ARG_NAME; \
	{ \
		size_t string_len; \
		napi_status status = napi_get_value_string_utf8(env, argv[ARG_IDX], NULL, 0, &string_len); \
		CHECK_STATUS_THROW(status, napi_get_value_string_utf8);\
		ARG_NAME = malloc(string_len + 1); \
		status = napi_get_value_string_utf8(env, argv[ARG_IDX], ARG_NAME, string_len + 1, &string_len); \
		CHECK_STATUS_THROW(status, napi_get_value_string_utf8);\
		if (status != napi_ok) { \
			const napi_extended_error_info* result; \
			napi_get_last_error_info(env, &result); \
			char err[1024]; \
			snprintf(err, 1024, "Argument " #ARG_NAME ": %s\n", result->error_message); \
			napi_throw_type_error(env, NULL, err); \
			return NULL; \
		} \
	}

#define RETURN_EXTERNAL(POINTER, FINALIZE_CB) \
	{ \
		napi_value ret; \
		napi_status status = napi_create_external(env, POINTER, FINALIZE_CB, NULL, &ret); \
		CHECK_STATUS_THROW(status, napi_create_external); \
		return ret; \
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

#define ARG_CB_REF(CB_REF, ARG_IDX) \
	{ \
		status = napi_create_reference(env, argv[ARG_IDX], 1, &CB_REF); \
		CHECK_STATUS_THROW(status, napi_create_reference); \
	}

#define CREATE_ASYNC_CONTEXT(CONTEXT_VAR, EVENT_NAME) \
	{ \
		napi_value async_resource_name; \
		status = napi_create_string_utf8(env, #EVENT_NAME, NAPI_AUTO_LENGTH, &async_resource_name); \
		CHECK_STATUS_THROW(status, napi_create_string_utf8); \
		status = napi_async_init(env, NULL, async_resource_name, &CONTEXT_VAR); \
		CHECK_STATUS_THROW(status, napi_async_init); \
	}

#define CALL_CB(CB_REF, ASYNC_CONTEXT, RESULT, ERROR_RET) \
	{ \
		napi_value resource_object; \
		napi_callback_scope scope; \
		napi_value cb; \
		napi_status status = napi_create_object(env, &resource_object); \
		CHECK_STATUS_UNCAUGHT(status, napi_create_object, ERROR_RET); \
		\
		status = napi_open_callback_scope( \
			env, \
			resource_object, \
			ASYNC_CONTEXT, \
			&scope \
		); \
		CHECK_STATUS_UNCAUGHT(status, napi_open_callback_scope, ERROR_RET); \
		\
		status = napi_get_reference_value(env, CB_REF, &cb); \
		CHECK_STATUS_UNCAUGHT(status, napi_get_reference_value, ERROR_RET); \
		\
		status = napi_make_callback( \
			env, \
			ASYNC_CONTEXT, \
			resource_object, \
			cb, \
			ERROR_RET, \
			NULL, \
			&RESULT \
		); \
		if (status == napi_pending_exception) { \
			napi_value last_exception; \
			napi_get_and_clear_last_exception(env, &last_exception); \
			napi_fatal_exception(env, last_exception); \
			return ERROR_RET; \
		} \
		CHECK_STATUS_UNCAUGHT(status, napi_make_callback, ERROR_RET); \
		status = napi_close_callback_scope(env, scope); \
		CHECK_STATUS_UNCAUGHT(status, napi_close_callback_scope, ERROR_RET); \
	}

#define CREATE_CB_ARGS(ARGS, ASYNC_CONTEXT, CB_REF) \
	{ \
		ARGS = calloc(1, sizeof(struct callback_args)); \
		ARGS->cb_ref = CB_REF; \
		ARGS->env = env; \
		ARGS->context = ASYNC_CONTEXT; \
	}

struct callback_args {
	napi_ref cb_ref;
	napi_env env;
	napi_async_context context;
};

void _libui_init_window (napi_env env, napi_value exports);
void _libui_init_core (napi_env env, napi_value exports);

#endif
