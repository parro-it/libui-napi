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

// @andlabs in https://github.com/charto/nbind/issues/20 :
// Yes, you keep ownership of the uiAreaHandler. libui only cares about the address you give
// uiNewArea(); it doesn't copy anything. You can even use the same uiAreaHandler on multiple
// uiAreas, which is why you get the uiArea as a parameter in each function.
//
// In fact, this is the intent of the design: you make the first field of your handler struct a
// uiAreaHandler and stick extra fields at the end, like in COM or C++. Some people have asked for
// the more conventional void *data extra parameter, but...
static uiAreaHandler *AREA_HANDLER;

napi_ref AreaMouseEvent, AreaKeyEvent, AreaDrawParams, AreaDrawContext, BrushGradientStop, Color,
	Point, Size;

napi_value create_mouse_event(napi_env env, uiAreaMouseEvent *e) {
	napi_value constructor, value;

	napi_status status = napi_get_reference_value(env, AreaMouseEvent, &constructor);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	napi_value args[9] = {make_double(env, e->X),		  make_double(env, e->Y),
						  make_double(env, e->AreaWidth), make_double(env, e->AreaHeight),
						  make_int32(env, e->Down),		  make_int32(env, e->Up),
						  make_int32(env, e->Count),	  make_int32(env, e->Modifiers),
						  make_uint32(env, e->Held1To64)};

	status = napi_new_instance(env, constructor, 9, args, &value);
	CHECK_STATUS_THROW(status, napi_new_instance);

	return value;
}

napi_value create_key_event(napi_env env, uiAreaKeyEvent *e) {
	napi_value constructor, value;

	napi_status status = napi_get_reference_value(env, AreaKeyEvent, &constructor);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	napi_value args[5] = {make_int32(env, e->Key), make_int32(env, e->ExtKey),
						  make_int32(env, e->Modifier), make_int32(env, e->Modifiers),
						  make_uint32(env, e->Up)};

	status = napi_new_instance(env, constructor, 5, args, &value);
	CHECK_STATUS_THROW(status, napi_new_instance);

	return value;
}

napi_value create_draw_params(napi_env env, uiAreaDrawParams *p) {
	napi_value constructorParams, constructorContext, result, context;

	napi_status status = napi_get_reference_value(env, AreaDrawParams, &constructorParams);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	status = napi_get_reference_value(env, AreaDrawContext, &constructorContext);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	napi_value contextExternal;
	status = napi_create_external(env, p->Context, NULL, NULL, &contextExternal);
	CHECK_STATUS_THROW(status, napi_create_external);

	napi_value context_args[1] = {contextExternal};

	status = napi_new_instance(env, constructorContext, 1, context_args, &context);
	CHECK_STATUS_THROW(status, napi_new_instance);

	napi_value params_args[7] = {context,
								 make_double(env, p->AreaWidth),
								 make_double(env, p->AreaHeight),
								 make_double(env, p->ClipX),
								 make_double(env, p->ClipY),
								 make_double(env, p->ClipWidth),
								 make_double(env, p->ClipHeight)};

	status = napi_new_instance(env, constructorParams, 7, params_args, &result);
	CHECK_STATUS_THROW(status, napi_new_instance);

	return result;
}

static void event_draw_cb(uiAreaHandler *h, uiArea *a, uiAreaDrawParams *p) {
	struct control_handle *handle;
	ctrl_map_get(&controls_map, uiControl(a), &handle);
	napi_env env = handle->env;

	napi_value null;
	napi_status status = napi_get_null(env, &null);
	CHECK_STATUS_UNCAUGHT(status, napi_get_null, /*void*/);

	napi_handle_scope handle_scope;
	status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, /*void*/);

	napi_value event_args[2];
	event_args[0] = null;
	event_args[1] = create_draw_params(env, p);

	fire_event_args(handle->events->head->event, 2, event_args);

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, /*void*/);
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
		creates an object
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
	CHECK_STATUS_UNCAUGHT(status, napi_get_null, 0);

	/*
		a scope is needed here because create_key_event
		creates an object
	*/
	status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, 0);

	napi_value event_args[2];
	event_args[0] = null;
	event_args[1] = create_key_event(env, e);

	bool v_i;
	napi_value v = fire_event_args(handle->events->head->DUP(4, next->) event, 2, event_args);

	status = napi_coerce_to_bool(env, v, &v);
	CHECK_STATUS_UNCAUGHT(status, napi_coerce_to_bool, 0);

	status = napi_get_value_bool(env, v, &v_i);
	CHECK_STATUS_UNCAUGHT(status, napi_get_value_int32, 0);

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, 0);

	return v_i;
}

#define INSTALL_AREA_EVENTS(TO)                                                                    \
	{                                                                                              \
		struct control_handle *ctrl_handle;                                                        \
		napi_status status = napi_get_value_external(env, TO, (void **)&ctrl_handle);              \
		CHECK_STATUS_THROW(status, napi_get_value_external);                                       \
                                                                                                   \
		struct event_t *drawEvent = create_event(env, draw, "onDraw");                             \
		if (drawEvent == NULL) {                                                                   \
			return NULL;                                                                           \
		}                                                                                          \
		install_event(ctrl_handle->events, drawEvent);                                             \
                                                                                                   \
		struct event_t *mouseEvent = create_event(env, mouse, "onMouse");                          \
		if (mouseEvent == NULL) {                                                                  \
			return NULL;                                                                           \
		}                                                                                          \
		install_event(ctrl_handle->events, mouseEvent);                                            \
                                                                                                   \
		struct event_t *mouseCrossedEvent = create_event(env, mouseCrossed, "onMouseCrossed");     \
		if (mouseCrossedEvent == NULL) {                                                           \
			return NULL;                                                                           \
		}                                                                                          \
		install_event(ctrl_handle->events, mouseCrossedEvent);                                     \
                                                                                                   \
		struct event_t *dragBrokenEvent = create_event(env, dragBroken, "onDragBroken");           \
		if (dragBrokenEvent == NULL) {                                                             \
			return NULL;                                                                           \
		}                                                                                          \
		install_event(ctrl_handle->events, dragBrokenEvent);                                       \
                                                                                                   \
		struct event_t *keyEvent = create_event(env, key, "onKey");                                \
		if (keyEvent == NULL) {                                                                    \
			return NULL;                                                                           \
		}                                                                                          \
		install_event(ctrl_handle->events, keyEvent);                                              \
	}

LIBUI_FUNCTION(create) {
	INIT_ARGS(5);

	ARG_CB_REF(draw, 0);
	ARG_CB_REF(mouse, 1);
	ARG_CB_REF(mouseCrossed, 2);
	ARG_CB_REF(dragBroken, 3);
	ARG_CB_REF(key, 4);

	uiArea *ui_area = uiNewArea(AREA_HANDLER);
	napi_value value = control_handle_new(env, uiControl(ui_area), "area");

	INSTALL_AREA_EVENTS(value);

	return value;
}

LIBUI_FUNCTION(createScrolling) {
	INIT_ARGS(7);

	ARG_CB_REF(draw, 0);
	ARG_CB_REF(mouse, 1);
	ARG_CB_REF(mouseCrossed, 2);
	ARG_CB_REF(dragBroken, 3);
	ARG_CB_REF(key, 4);
	ARG_INT32(width, 5);
	ARG_INT32(height, 6);

	uiArea *ui_area = uiNewScrollingArea(AREA_HANDLER, width, height);
	napi_value value = control_handle_new(env, uiControl(ui_area), "area");

	INSTALL_AREA_EVENTS(value);

	return value;
}

LIBUI_FUNCTION(queueRedrawAll) {
	INIT_ARGS(1);

	ARG_POINTER(struct control_handle, handle, 0);

	uiAreaQueueRedrawAll(uiArea(handle->control));

	return NULL;
}

LIBUI_FUNCTION(beginWindowMove) {
	INIT_ARGS(1);

	ARG_POINTER(struct control_handle, handle, 0);

	uiAreaBeginUserWindowMove(uiArea(handle->control));

	return NULL;
}
LIBUI_FUNCTION(beginWindowResize) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_INT32(edge, 1);

	uiAreaBeginUserWindowResize(uiArea(handle->control), edge);

	return NULL;
}

LIBUI_FUNCTION(setSize) {
	INIT_ARGS(3);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_INT32(width, 1);
	ARG_INT32(height, 2);

	uiAreaSetSize(uiArea(handle->control), width, height);

	return NULL;
}

LIBUI_FUNCTION(scrollTo) {
	INIT_ARGS(5);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_DOUBLE(x, 1);
	ARG_DOUBLE(y, 2);
	ARG_DOUBLE(width, 3);
	ARG_DOUBLE(height, 4);

	uiAreaScrollTo(uiArea(handle->control), x, y, width, height);

	return NULL;
}

LIBUI_FUNCTION(init) {
	INIT_ARGS(8);

	AREA_HANDLER = malloc(sizeof(uiAreaHandler));
	AREA_HANDLER->Draw = event_draw_cb;
	AREA_HANDLER->MouseEvent = event_mouse_cb;
	AREA_HANDLER->MouseCrossed = event_mouseCrossed_cb;
	AREA_HANDLER->DragBroken = event_dragBroken_cb;
	AREA_HANDLER->KeyEvent = event_key_cb;

	ARG_CB_REF(mouseEvent, 0);
	AreaMouseEvent = mouseEvent;

	ARG_CB_REF(keyEvent, 1);
	AreaKeyEvent = keyEvent;

	ARG_CB_REF(drawParams, 2);
	AreaDrawParams = drawParams;

	ARG_CB_REF(drawContext, 3);
	AreaDrawContext = drawContext;

	ARG_CB_REF(stop, 4);
	BrushGradientStop = stop;

	ARG_CB_REF(color, 5);
	Color = color;

	ARG_CB_REF(point, 6);
	Point = point;

	ARG_CB_REF(size, 7);
	Size = size;

	return NULL;
}

napi_value _libui_init_area(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(init);
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(createScrolling);
	LIBUI_EXPORT(queueRedrawAll);
	LIBUI_EXPORT(beginWindowMove);
	LIBUI_EXPORT(beginWindowResize);
	LIBUI_EXPORT(setSize);
	LIBUI_EXPORT(scrollTo);
	return module;
}
