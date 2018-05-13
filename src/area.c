#include <assert.h>
#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

#define DUP(n, c) DUP##n(c)
#define DUP4(c) c c c c
#define DUP3(c) c c c
#define DUP2(c) c c
#define DUP1(c) c

static const char *MODULE = "Area";

// area-mouse-event.c
napi_value create_mouse_event(napi_env env, uiAreaMouseEvent *event);

static void event_draw_cb(uiAreaHandler *h, uiArea *a, uiAreaDrawParams *p) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, uiControl(a), &handle);
	fire_event(handle->events->head->event);
}
static void event_mouse_cb(uiAreaHandler *h, uiArea *a, uiAreaMouseEvent *e) {
	struct control_handle *handle;
	napi_value null;
	napi_status status;
	napi_handle_scope handle_scope;

	ctrl_map_get(&controls_map, uiControl(a), &handle);
	napi_env env = handle->env;

	/*
		pass null for now as area instance to the callback
		we can pass the correct instance after
		https://github.com/parro-it/libui-napi/issues/8
	*/
	status = napi_get_null(env, &null);
	CHECK_STATUS_UNCAUGHT(status, napi_get_null, /*void*/);

	/*
		a scope is needed here because create_mouse_event
		create an object
	*/
	status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, /*void*/);

	napi_value event_args[2];
	event_args[0] = null;
	event_args[1] = create_mouse_event(env, e);

	fire_event_args(handle->events->head->DUP(1, next->) event, 2, event_args);

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, /*void*/);
}
static void event_mouseCrossed_cb(uiAreaHandler *h, uiArea *a, int left) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, uiControl(a), &handle);
	struct event_t *event = handle->events->head->DUP(2, next->) event;
	napi_env env = event->env;

	napi_value null;
	napi_status status = napi_get_null(env, &null);
	CHECK_STATUS_UNCAUGHT(status, napi_get_null, /*void*/);

	napi_value event_args[2];
	event_args[0] = null;
	event_args[1] = make_bool(env, left);

	fire_event_args(event, 2, event_args);
}
static void event_dragBroken_cb(uiAreaHandler *h, uiArea *a) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, uiControl(a), &handle);
	fire_event(handle->events->head->DUP(3, next->) event);
}
static int event_key_cb(uiAreaHandler *h, uiArea *a, uiAreaKeyEvent *e) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, uiControl(a), &handle);
	struct event_t *event = handle->events->head->DUP(4, next->) event;
	// napi_env env = event->env;
	/*napi_value return_v =*/fire_event(event);

	// napi_status status = napi_get_value_int32(env, return_v, &return_i);
	return 0;
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(5);

	ARG_CB_REF(draw, 0);
	ARG_CB_REF(mouse, 1);
	ARG_CB_REF(mouseCrossed, 2);
	ARG_CB_REF(dragBroken, 3);
	ARG_CB_REF(key, 4);

	uiAreaHandler *handler = malloc(sizeof(uiAreaHandler));
	handler->Draw = event_draw_cb;
	handler->MouseEvent = event_mouse_cb;
	handler->MouseCrossed = event_mouseCrossed_cb;
	handler->DragBroken = event_dragBroken_cb;
	handler->KeyEvent = event_key_cb;

	uiArea *ui_area = uiNewArea(handler);
	napi_value value = control_handle_new(env, uiControl(ui_area), "area");

	// retrieve the original struct control_handle pointer.
	struct control_handle *ctrl_handle;
	napi_status status = napi_get_value_external(env, value, (void **)&ctrl_handle);
	CHECK_STATUS_THROW(status, napi_get_value_external);

	struct event_t *drawEvent = create_event(env, draw, "onDraw");
	if (drawEvent == NULL) {
		return NULL;
	}
	install_event(ctrl_handle->events, drawEvent);

	struct event_t *mouseEvent = create_event(env, mouse, "onMouse");
	if (mouseEvent == NULL) {
		return NULL;
	}
	install_event(ctrl_handle->events, mouseEvent);

	struct event_t *mouseCrossedEvent = create_event(env, mouseCrossed, "onMouseCrossed");
	if (mouseCrossedEvent == NULL) {
		return NULL;
	}
	install_event(ctrl_handle->events, mouseCrossedEvent);

	struct event_t *dragBrokenEvent = create_event(env, dragBroken, "onDragBroken");
	if (dragBrokenEvent == NULL) {
		return NULL;
	}
	install_event(ctrl_handle->events, dragBrokenEvent);

	struct event_t *keyEvent = create_event(env, key, "onKey");
	if (keyEvent == NULL) {
		return NULL;
	}
	install_event(ctrl_handle->events, keyEvent);

	return value;
}

LIBUI_FUNCTION(queueRedrawAll) {
	INIT_ARGS(1);

	ARG_POINTER(struct control_handle, handle, 0);

	uiAreaQueueRedrawAll(uiArea(handle->control));

	return NULL;
}

// LIBUI_FUNCTION(setSize) {
// 	INIT_ARGS(3);

// 	ARG_POINTER(struct control_handle, handle, 0);
// 	ARG_INT32(width, 1);
// 	ARG_INT32(height, 2);

// 	uiAreaSetSize(uiArea(handle->control), width, height);

// 	return NULL;
// }

// LIBUI_FUNCTION(scrollTo) {
// 	INIT_ARGS(5);

// 	ARG_POINTER(struct control_handle, handle, 0);
// 	ARG_DOUBLE(x, 1);
// 	ARG_DOUBLE(y, 2);
// 	ARG_DOUBLE(width, 3);
// 	ARG_DOUBLE(height, 4);

// 	uiAreaScrollTo(uiArea(handle->control), x, y, width, height);

// 	return NULL;
// }

napi_value _libui_init_area(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(queueRedrawAll);
	return module;
}
