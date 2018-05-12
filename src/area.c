#include "ui.h"
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Area";

struct area_handle {
	/*
		event registered on this control
	*/
	struct event_t *event_draw;
	struct event_t *event_mouse;
	struct event_t *event_mouseCrossed;
	struct event_t *event_dragBroken;
	struct event_t *event_key;
};

static void event_draw_cb(uiAreaHandler *h, uiArea *a, uiAreaDrawParams *p) {
	// https://github.com/charto/nbind/issues/20
	// struct event_t *event = (struct event_t *)data;
	// fire_event(event);
	printf("event_draw_cb\n");
}
static void event_mouse_cb(uiAreaHandler *h, uiArea *a, uiAreaMouseEvent *e) {
	// struct event_t *event = (struct event_t *)data;
	// fire_event(event);
	printf("event_mouse_cb\n");
}
static void event_mouseCrossed_cb(uiAreaHandler *h, uiArea *a, int left) {
	// struct event_t *event = (struct event_t *)data;
	// fire_event(event);
	printf("event_mouseCrossed_cb\n");
}
static void event_dragBroken_cb(uiAreaHandler *h, uiArea *a) {
	// struct event_t *event = (struct event_t *)data;
	// fire_event(event);
	printf("event_dragBroken_cb\n");
}
static int event_key_cb(uiAreaHandler *h, uiArea *a, uiAreaKeyEvent *e) {
	// struct event_t *event = (struct event_t *)data;
	// fire_event(event);
	printf("event_key_cb\n");
	return 0;
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(5);

	ARG_CB_REF(draw, 0);
	ARG_CB_REF(mouse, 1);
	ARG_CB_REF(mouseCrossed, 2);
	ARG_CB_REF(dragBroken, 3);
	ARG_CB_REF(key, 4);

	struct area_handle *area = calloc(1, sizeof(struct area_handle));

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
	area->event_draw = drawEvent;

	struct event_t *mouseEvent = create_event(env, mouse, "onMouse");
	if (mouseEvent == NULL) {
		return NULL;
	}
	install_event(ctrl_handle->events, mouseEvent);
	area->event_mouse = mouseEvent;

	struct event_t *mouseCrossedEvent = create_event(env, mouseCrossed, "onMouseCrossed");
	if (mouseCrossedEvent == NULL) {
		return NULL;
	}
	install_event(ctrl_handle->events, mouseCrossedEvent);
	area->event_mouseCrossed = mouseCrossedEvent;

	struct event_t *dragBrokenEvent = create_event(env, dragBroken, "onDragBroken");
	if (dragBrokenEvent == NULL) {
		return NULL;
	}
	install_event(ctrl_handle->events, dragBrokenEvent);
	area->event_dragBroken = dragBrokenEvent;

	struct event_t *keyEvent = create_event(env, key, "onKey");
	if (keyEvent == NULL) {
		return NULL;
	}
	install_event(ctrl_handle->events, keyEvent);
	area->event_key = keyEvent;

	return value;
}

napi_value _libui_init_area(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	return module;
}
