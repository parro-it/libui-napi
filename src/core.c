#include <string.h>
#include <ui.h>
#include <stdlib.h>
#include <stdio.h>
#include "uinode.h"
#include "window.h"
#include "events.h"


static int onShouldQuit_cb(void *data) {

	struct callback_args *args = (struct callback_args *)data;
	raise_event(args);

	return 0;
}

static napi_value onShouldQuit (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_CB_REF(cb_ref, 0);

	struct callback_args *args = create_event(env, cb_ref, "onShouldQuit");
	if (args == NULL) {
		return NULL;
	}

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
	controls_map = win_map_create(0, 1);
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
