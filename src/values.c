#include "values.h"
#include "napi_utils.h"

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

napi_value make_color(napi_env env, double r, double g, double b, double a) {
	napi_value color;
	napi_value r_js;
	napi_value g_js;
	napi_value b_js;
	napi_value a_js;

	napi_status status;

	status = napi_create_object(env, &color);
	CHECK_STATUS_THROW(status, napi_create_object);

	status = napi_create_double(env, r, &r_js);
	CHECK_STATUS_THROW(status, napi_create_double);
	status = napi_create_double(env, g, &g_js);
	CHECK_STATUS_THROW(status, napi_create_double);
	status = napi_create_double(env, b, &b_js);
	CHECK_STATUS_THROW(status, napi_create_double);
	status = napi_create_double(env, a, &a_js);
	CHECK_STATUS_THROW(status, napi_create_double);

	status = napi_set_named_property(env, color, "r", r_js);
	CHECK_STATUS_THROW(status, napi_set_named_property);
	status = napi_set_named_property(env, color, "g", g_js);
	CHECK_STATUS_THROW(status, napi_set_named_property);
	status = napi_set_named_property(env, color, "b", b_js);
	CHECK_STATUS_THROW(status, napi_set_named_property);
	status = napi_set_named_property(env, color, "a", a_js);
	CHECK_STATUS_THROW(status, napi_set_named_property);

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
