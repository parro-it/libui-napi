#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "napi_utils.h"
#include "control.h"
#include "event-loop.h"
#include "events.h"

static const char *MODULE = "App";

struct children_list *visible_windows = NULL;

static int c_wrap_cb(void *data) {
	struct event_t *event = (struct event_t *)data;
	napi_value ret = fire_event(event);
	if (ret == NULL) {
		return 0;
	}
	int ret_int;
	napi_get_value_int32(event->env, ret, &ret_int);
	return ret_int;
}

LIBUI_FUNCTION(onShouldQuit) {
	INIT_ARGS(1);
	ARG_CB_REF(cb_ref, 0);

	struct event_t *event = create_event(env, cb_ref, "onShouldQuit");
	if (event == NULL) {
		return NULL;
	}

	uiOnShouldQuit(c_wrap_cb, event);

	return NULL;
}

LIBUI_FUNCTION(startTimer) {
	INIT_ARGS(2);
	ARG_INT32(ms, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "startTimer");
	if (event == NULL) {
		return NULL;
	}

	uiTimer(ms, c_wrap_cb, event);

	return NULL;
}

LIBUI_FUNCTION(init) {
	uiInitOptions o;
	memset(&o, 0, sizeof(uiInitOptions));
	const char *err = uiInit(&o);
	if (err != NULL) {
		napi_throw_error(env, NULL, err);
		uiFreeInitError(err);
	}
	controls_map = ctrl_map_create(0, 1);
	visible_windows = create_children_list();
	ln_init_loop_status();

	napi_value global;
	napi_status status = napi_get_global(env, &global);
	CHECK_STATUS_THROW(status, napi_get_global);

	status = napi_create_reference(env, global, 1, &null_ref);
	CHECK_STATUS_THROW(status, napi_create_reference);

	return NULL;
}

napi_value _libui_init_core(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(onShouldQuit);
	LIBUI_EXPORT(init);
	LIBUI_EXPORT(startTimer);
	return module;
}
