#include <string.h>
#include <ui.h>
#include <stdlib.h>
#include <stdio.h>
#include "ui_node.h"


static int onShouldQuit_cb(void *data) {
	napi_value result;

	struct callback_args *args = (struct callback_args *)data;
	napi_env env = args->env;

	CALL_CB(args->cb_ref, args->context, result, 0);
	return 0;
}

static napi_value onShouldQuit (napi_env env, napi_callback_info info) {
	napi_status status;

	INIT_ARGS(1);

	napi_async_context async_context;
	napi_ref cb_ref;
	struct callback_args *args;

	CREATE_ASYNC_CONTEXT(async_context, onShouldQuit);
	CREATE_CB_REF(cb_ref, 0);

	CREATE_CB_ARGS(args, async_context, cb_ref);

	uiOnShouldQuit(onShouldQuit_cb, args);

	return NULL;
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
