#include "events.h"


napi_value raise_event(struct callback_args *event) {
	napi_status status;
	napi_env env = event->env;

	napi_value resource_object;
	status = napi_create_object(env, &resource_object);
	CHECK_STATUS_UNCAUGHT(status, napi_create_object, NULL);

	napi_callback_scope scope;
	status = napi_open_callback_scope(
		env,
		resource_object,
		event->context,
		&scope
	);
	CHECK_STATUS_UNCAUGHT(status, napi_open_callback_scope, NULL);

	napi_value cb;
	status = napi_get_reference_value(env, event->cb_ref, &cb);
	CHECK_STATUS_UNCAUGHT(status, napi_get_reference_value, NULL);

	napi_value result;
	status = napi_make_callback(
		env,
		event->context,
		resource_object,
		cb,
		0,
		NULL,
		&result
	);

	if (status == napi_pending_exception) {
		napi_value last_exception;
		napi_get_and_clear_last_exception(env, &last_exception);
		napi_fatal_exception(env, last_exception);
		return NULL;
	}

	CHECK_STATUS_UNCAUGHT(status, napi_make_callback, NULL);

	status = napi_close_callback_scope(env, scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_callback_scope, NULL);

	return result;
}


struct callback_args *create_event(napi_env env, napi_ref cb_ref, const char *name) {
	napi_status status;

	napi_value async_resource_name;
	status = napi_create_string_utf8(env, name, NAPI_AUTO_LENGTH, &async_resource_name);
	CHECK_STATUS_THROW(status, napi_create_string_utf8);

	napi_async_context async_context;
	status = napi_async_init(env, NULL, async_resource_name, &async_context);
	CHECK_STATUS_THROW(status, napi_async_init);

	struct callback_args *args = calloc(1, sizeof(struct callback_args));
	args->cb_ref = cb_ref;
	args->env = env;
	args->context = async_context;

	return args;
}
