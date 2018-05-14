#include "values.h"
#include "napi_utils.h"

// area.c
extern napi_ref Color, Point;

napi_value make_size(napi_env env, uint32_t width, uint32_t height) {
	napi_value size;
	napi_value width_js;
	napi_value height_js;
	napi_status status;

	status = napi_create_object(env, &size);
	CHECK_STATUS_THROW(status, napi_create_object);

	status = napi_create_uint32(env, width, &width_js);
	CHECK_STATUS_THROW(status, napi_create_uint32);

	status = napi_create_uint32(env, height, &height_js);
	CHECK_STATUS_THROW(status, napi_create_uint32);

	status = napi_set_named_property(env, size, "width", width_js);
	CHECK_STATUS_THROW(status, napi_set_named_property);

	status = napi_set_named_property(env, size, "height", height_js);
	CHECK_STATUS_THROW(status, napi_set_named_property);

	return size;
}

napi_value make_point(napi_env env, double x, double y) {
	napi_value point, constructor;

	napi_handle_scope handle_scope;
	napi_status status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_THROW(status, napi_open_handle_scope);

	status = napi_get_reference_value(env, Point, &constructor);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	napi_value args[2] = {make_double(env, x), make_double(env, y)};

	status = napi_new_instance(env, constructor, 2, args, &point);
	CHECK_STATUS_THROW(status, napi_new_instance);

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_THROW(status, napi_close_handle_scope);

	return point;
}

napi_value make_color(napi_env env, double r, double g, double b, double a) {
	napi_value color, constructor;

	napi_handle_scope handle_scope;
	napi_status status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_THROW(status, napi_open_handle_scope);

	status = napi_get_reference_value(env, Color, &constructor);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	napi_value args[4] = {make_double(env, r), make_double(env, g), make_double(env, b),
						  make_double(env, a)};

	status = napi_new_instance(env, constructor, 4, args, &color);
	CHECK_STATUS_THROW(status, napi_new_instance);

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_THROW(status, napi_close_handle_scope);

	return color;
}

/*
napi_value from_size(napi_env env, napi_value size, uint32_t *width, uint32_t
*height) { napi_value width_js; napi_value height_js; napi_status status;

	status = napi_get_named_property(env, size, "width", &width_js);
	CHECK_STATUS_THROW(status, napi_get_named_property);

	status = napi_get_named_property(env, size, "height", &height_js);
	CHECK_STATUS_THROW(status, napi_get_named_property);

	status =  napi_get_value_uint32(env, width_js, width);
	CHECK_STATUS_THROW(status, napi_get_named_property);

	status =  napi_get_value_uint32(env, height_js, height);
	CHECK_STATUS_THROW(status, napi_get_named_property);

	return NULL;
}
*/
