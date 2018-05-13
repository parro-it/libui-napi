#include <ui.h>
#include "napi_utils.h"

/*
	this macro create a napi function from given native function
	using the `uiAreaMouseEvent *event` as data argument.
	the native functiong will keep care of retrieveving
	the `uiAreaMouseEvent *event` using EVENT_FROM_DATA_ARG arg.

 */
// #define ADD_METHOD(FN)                                                                             \
// 	{                                                                                              \
// 		napi_value FN##_VALUE;                                                                     \
// 		napi_status status =                                                                       \
// 			napi_create_function(env, #FN, NAPI_AUTO_LENGTH, FN, event, &FN##_VALUE);              \
// 		CHECK_STATUS_THROW(status, napi_create_function);                                          \
// 		status = napi_set_named_property(env, mouse_event, #FN, FN##_VALUE);                       \
// 		CHECK_STATUS_THROW(status, napi_set_named_property);                                       \
// 	}

// #define EVENT_FROM_DATA_ARG()                                                                      \
// 	uiAreaMouseEvent *e;                                                                           \
// 	{                                                                                              \
// 		napi_status status = napi_get_cb_info(env, info, 0, NULL, NULL, (void **)&e);              \
// 		CHECK_STATUS_THROW(status, napi_get_cb_info);                                              \
// 	}

// LIBUI_FUNCTION(getX) {
// 	EVENT_FROM_DATA_ARG();
// 	return make_double(env, e->X);
// }

// LIBUI_FUNCTION(getY) {
// 	EVENT_FROM_DATA_ARG();
// 	return make_double(env, e->Y);
// }

// LIBUI_FUNCTION(getAreaWidth) {
// 	EVENT_FROM_DATA_ARG();
// 	return make_double(env, e->AreaWidth);
// }

// LIBUI_FUNCTION(getAreaHeight) {
// 	EVENT_FROM_DATA_ARG();
// 	return make_double(env, e->AreaHeight);
// }

// LIBUI_FUNCTION(getDown) {
// 	EVENT_FROM_DATA_ARG();
// 	return make_int32(env, e->Down);
// }

// LIBUI_FUNCTION(getUp) {
// 	EVENT_FROM_DATA_ARG();
// 	return make_int32(env, e->Up);
// }

// LIBUI_FUNCTION(getCount) {
// 	EVENT_FROM_DATA_ARG();
// 	return make_int32(env, e->Count);
// }

// LIBUI_FUNCTION(getModifiers) {
// 	EVENT_FROM_DATA_ARG();
// 	return make_int32(env, e->Modifiers);
// }

// LIBUI_FUNCTION(getHeld1To64) {
// 	EVENT_FROM_DATA_ARG();
// 	return make_uint32(env, e->Held1To64);
// }

// /*
// 	this function create a lot of object
// 	on each call, and being used by UiArea,
// 	it would be worth to try to optmize it,
// 	maybe creating a prototype (that I don't know how to do ATM)
// */
napi_value create_mouse_event(napi_env env, uiAreaMouseEvent *e) {
	napi_value global, constructor, value;
	napi_status status = napi_get_global(env, &global);
	CHECK_STATUS_THROW(status, napi_get_global);

	status = napi_get_named_property(env, global, "AreaMouseEvent", &constructor);
	CHECK_STATUS_THROW(status, napi_get_named_property);

	napi_value args[9] = {make_double(env, e->X),		  make_double(env, e->Y),
						  make_double(env, e->AreaWidth), make_double(env, e->AreaHeight),
						  make_int32(env, e->Down),		  make_int32(env, e->Up),
						  make_int32(env, e->Count),	  make_int32(env, e->Modifiers),
						  make_uint32(env, e->Held1To64)};

	status = napi_new_instance(env, constructor, 9, args, &value);

	return value;

	// napi_value mouse_event;
	// napi_status status = napi_create_object(env, &mouse_event);
	// CHECK_STATUS_THROW(status, napi_create_object);

	// ADD_METHOD(getX);
	// ADD_METHOD(getY);
	// ADD_METHOD(getAreaWidth);
	// ADD_METHOD(getAreaHeight);
	// ADD_METHOD(getDown);
	// ADD_METHOD(getUp);
	// ADD_METHOD(getCount);
	// ADD_METHOD(getModifiers);
	// ADD_METHOD(getHeld1To64);

	// return mouse_event;
}
