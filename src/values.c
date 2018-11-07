#include "values.h"
#include "napi_utils.h"

// area.c
extern napi_ref Color, Point, Size;

napi_value make_size_int(napi_env env, int width, int height) {
	napi_value size, constructor;

	napi_status status = napi_get_reference_value(env, Size, &constructor);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	napi_value args[2] = {make_int32(env, width), make_int32(env, height)};

	status = napi_new_instance(env, constructor, 2, args, &size);
	CHECK_STATUS_THROW(status, napi_new_instance);

	return size;
}

napi_value make_size_double(napi_env env, double width, double height) {
	napi_value size, constructor;

	napi_status status = napi_get_reference_value(env, Size, &constructor);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	napi_value args[2] = {make_double(env, width), make_double(env, height)};

	status = napi_new_instance(env, constructor, 2, args, &size);
	CHECK_STATUS_THROW(status, napi_new_instance);

	return size;
}

napi_value make_point(napi_env env, double x, double y) {
	napi_value point, constructor;

	napi_status status = napi_get_reference_value(env, Point, &constructor);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	napi_value args[2] = {make_double(env, x), make_double(env, y)};

	status = napi_new_instance(env, constructor, 2, args, &point);
	CHECK_STATUS_THROW(status, napi_new_instance);

	return point;
}

napi_value make_color(napi_env env, double r, double g, double b, double a) {
	napi_value color, constructor;

	napi_status status = napi_get_reference_value(env, Color, &constructor);
	CHECK_STATUS_THROW(status, napi_get_reference_value);

	napi_value args[4] = {make_double(env, r), make_double(env, g), make_double(env, b),
						  make_double(env, a)};

	status = napi_new_instance(env, constructor, 4, args, &color);
	CHECK_STATUS_THROW(status, napi_new_instance);

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
