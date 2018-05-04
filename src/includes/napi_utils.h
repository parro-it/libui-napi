#ifndef LIBUI_NODE_UTILS_H__
#define LIBUI_NODE_UTILS_H__

#include <node_api.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// function arguments

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

#define ARG_CB_REF(ARG_NAME, ARG_IDX) \
	napi_ref ARG_NAME; \
	{ \
		napi_status status = napi_create_reference(env, argv[ARG_IDX], 1, &ARG_NAME); \
		CHECK_STATUS_THROW(status, napi_create_reference); \
	}

// return values
/*
#define RETURN_EXTERNAL(POINTER, FINALIZE_CB) \
	{ \
		napi_value ret; \
		napi_status status = napi_create_external(env, POINTER, FINALIZE_CB, NULL, &ret); \
		CHECK_STATUS_THROW(status, napi_create_external); \
		return ret; \
	}
*/

// function export

#define LIBUI_EXPORT(FN) \
	{ \
		napi_value func; \
		napi_status status = napi_create_function(env, #FN, NAPI_AUTO_LENGTH, FN, NULL, & func); \
		CHECK_STATUS_THROW(status, napi_create_function); \
		status = napi_set_named_property(env, module, #FN, func); \
		CHECK_STATUS_THROW(status, napi_set_named_property); \
	} \

#define DEFINE_MODULE() \
	napi_value module; \
	{ \
		napi_status status = napi_create_object(env, &module); \
		CHECK_STATUS_THROW(status, napi_create_object); \
		status = napi_set_named_property(env, exports, MODULE, module); \
		CHECK_STATUS_THROW(status, napi_set_named_property); \
	}

// errors checking

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

// debug

#define UI_NODE_DEBUG 0

#if UI_NODE_DEBUG
	#define DEBUG(msg) fprintf(stderr, msg "\n")
	#define DEBUG_F(msg, ...) fprintf(stderr, msg "\n", __VA_ARGS__)
#else
	#define DEBUG(msg) ;
	#define DEBUG_F(msg, ...) ;
#endif

#endif
