#include <string.h>
#include <ui.h>
#include <stdlib.h>
#include <stdio.h>
#include "core.h"

struct onShouldQuitArgs {
	napi_ref cb_ref;
	napi_env env;
	napi_async_context context;
};

static int onShouldQuit_cb(void *data) {
	napi_value result;
	napi_value resource_object;
	napi_status status;
	napi_callback_scope scope;
	napi_value cb;

	struct onShouldQuitArgs *args = (struct onShouldQuitArgs *)data;
	napi_env env = args->env;

	status = napi_create_object(env, &resource_object);
	CHECK_STATUS_UNCAUGHT(status, napi_create_object, 0);


	status = napi_open_callback_scope(
		env,
		resource_object,
		args->context,
		&scope
	);
	CHECK_STATUS_UNCAUGHT(status, napi_open_callback_scope, 0);

	status = napi_get_reference_value(env, args->cb_ref, &cb);
	CHECK_STATUS_UNCAUGHT(status, napi_get_reference_value, 0);

	status = napi_make_callback(
		env,
		args->context,
		resource_object,
		cb,
		0,
		NULL,
		&result
	);

	if (status == napi_pending_exception) {
		napi_value last_exception;
		napi_get_and_clear_last_exception(env, &last_exception);
		napi_fatal_exception(env, last_exception);
		return 0;
	}

	CHECK_STATUS_UNCAUGHT(status, napi_make_callback, 0);


	status = napi_close_callback_scope(env, scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_callback_scope, 0);

	return 0;
}

static napi_value init (napi_env env, napi_callback_info info) {
	uiInitOptions o;
	memset(&o, 0, sizeof(uiInitOptions));
	const char *err = uiInit(&o);
	if (err != NULL) {
		napi_throw_error(env, NULL, err);
		uiFreeInitError(err);
	}
	return NULL;
}

static napi_value onShouldQuit (napi_env env, napi_callback_info info) {
	napi_status status;

	INIT_ARGS(1);
	napi_value async_resource_name;
	status = napi_create_string_utf8(env, "onShouldQuit", NAPI_AUTO_LENGTH, &async_resource_name);
	CHECK_STATUS_THROW(status, napi_create_string_utf8);

	napi_async_context async_context;
	status = napi_async_init(env, NULL, async_resource_name, &async_context);
	CHECK_STATUS_THROW(status, napi_async_init);


	napi_ref cb_ref;
	status = napi_create_reference(env, argv[0], 1, &cb_ref);
	CHECK_STATUS_THROW(status, napi_create_reference);

	struct onShouldQuitArgs *args = malloc(sizeof(struct onShouldQuitArgs));
	args->cb_ref = cb_ref;
	args->env = env;
	args->context = async_context;
	uiOnShouldQuit(onShouldQuit_cb, args);

	return NULL;
}

static napi_value start (napi_env env, napi_callback_info info) {
	uiMain();
	return NULL;
}

static napi_value stop (napi_env env, napi_callback_info info) {
	uiQuit();
	return NULL;
}

void _libui_init_core (napi_env env, napi_value exports) {
	LIBUI_EXPORT(onShouldQuit);
	LIBUI_EXPORT(start);
	LIBUI_EXPORT(init);
	LIBUI_EXPORT(stop);
}
