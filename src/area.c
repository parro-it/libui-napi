#include "ui.h"
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Area";

struct area_handle {
	uiArea *area;

	/*
		A reference to the JavaScript object that wrap the handle pointer,
		It prevent the JavaScript object to be garbage collected, and is
		released when the control is destroyed.
	*/
	napi_ref area_ref;

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

	struct event_t *drawEvent = create_event(env, draw, "onDraw");
	if (drawEvent == NULL) {
		return NULL;
	}
	area->event_draw = drawEvent;

	struct event_t *mouseEvent = create_event(env, mouse, "onMouse");
	if (mouseEvent == NULL) {
		return NULL;
	}
	area->event_mouse = mouseEvent;

	struct event_t *mouseCrossedEvent = create_event(env, mouseCrossed, "onMouseCrossed");
	if (mouseCrossedEvent == NULL) {
		return NULL;
	}
	area->event_mouseCrossed = mouseCrossedEvent;

	struct event_t *dragBrokenEvent = create_event(env, dragBroken, "onDragBroken");
	if (dragBrokenEvent == NULL) {
		return NULL;
	}
	area->event_dragBroken = dragBrokenEvent;

	struct event_t *keyEvent = create_event(env, key, "onKey");
	if (keyEvent == NULL) {
		return NULL;
	}
	area->event_key = keyEvent;

	// we need the handler to live in the heap, or it
	// will cause undefined behaviour being deallocated
	// from the stack whne this function terminate
	uiAreaHandler *handler = malloc(sizeof(uiAreaHandler));
	handler->Draw = event_draw_cb;
	handler->MouseEvent = event_mouse_cb;
	handler->MouseCrossed = event_mouseCrossed_cb;
	handler->DragBroken = event_dragBroken_cb;
	handler->KeyEvent = event_key_cb;

	uiArea *ui_area = uiNewArea(handler);
	area->area = ui_area;

	/*
	napi_value handle_external;
	napi_status status;

	status = napi_create_external(env, area, NULL, NULL, &handle_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	status = napi_create_reference(env, handle_external, 1, &(area->area_ref));
	CHECK_STATUS_THROW(status, napi_create_reference);
	*/

	return control_handle_new(env, uiControl(ui_area), "area");
}

napi_value _libui_init_area(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	return module;
}
