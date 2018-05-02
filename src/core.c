#include <string.h>
#include <ui.h>
#include <stdlib.h>
#include <stdio.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static int onShouldQuit_cb(void *data) {

	struct event_t *event = (struct event_t *)data;
	fire_event(event);

	return 0;
}

static napi_value onShouldQuit (napi_env env, napi_callback_info info) {
	INIT_ARGS(1);
	ARG_CB_REF(cb_ref, 0);

	struct event_t *event = create_event(env, cb_ref, "onShouldQuit");
	if (event == NULL) {
		return NULL;
	}

	uiOnShouldQuit(onShouldQuit_cb, event);

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
	controls_map = ctrl_map_create(0, 1);
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
