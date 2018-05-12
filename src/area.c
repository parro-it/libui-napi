#include "ui.h"
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Area";

#define DUP(n, c) DUP##n(c)
#define DUP4(c) c c c c
#define DUP3(c) c c c
#define DUP2(c) c c
#define DUP1(c) c

// https://github.com/charto/nbind/issues/20

static void event_draw_cb(uiAreaHandler *h, uiArea *a, uiAreaDrawParams *p) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, uiControl(a), &handle);
	fire_event(handle->events->head->event);
}
static void event_mouse_cb(uiAreaHandler *h, uiArea *a, uiAreaMouseEvent *e) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, uiControl(a), &handle);
	fire_event(handle->events->head->DUP(1, next->) event);
}
static void event_mouseCrossed_cb(uiAreaHandler *h, uiArea *a, int left) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, uiControl(a), &handle);
	fire_event(handle->events->head->DUP(2, next->) event);
}
static void event_dragBroken_cb(uiAreaHandler *h, uiArea *a) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, uiControl(a), &handle);
	fire_event(handle->events->head->DUP(3, next->) event);
}
static int event_key_cb(uiAreaHandler *h, uiArea *a, uiAreaKeyEvent *e) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, uiControl(a), &handle);
	/*napi_value return_v =*/fire_event(handle->events->head->DUP(4, next->) event);
	// int return_i;
	// napi_status status = napi_get_value_int32(env, return_v, &return_i);
	// return return_i;

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

napi_value _libui_init_area(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	return module;
}
