#include "napi_utils.h"
#include "event-loop.h"

static const char *MODULE = "EventLoop";

void resolve_promise_null(napi_env env, napi_ref cb_ref, enum ln_loop_status new_status) {
	ln_set_loop_status(new_status);

	LIBUI_NODE_DEBUG("uv_timer_init");
	napi_value null;
	napi_status status;

	napi_handle_scope handle_scope;
	status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, );
	LIBUI_NODE_DEBUG("timer napi_open_handle_scope");

	status = napi_get_null(env, &null);
	CHECK_STATUS_UNCAUGHT(status, napi_get_null, );

	napi_value async_resource_name;
	status =
		napi_create_string_utf8(env, "event_loop_promise", NAPI_AUTO_LENGTH, &async_resource_name);
	CHECK_STATUS_UNCAUGHT(status, napi_create_string_utf8, );

	napi_async_context async_context;
	status = napi_async_init(env, NULL, async_resource_name, &async_context);
	CHECK_STATUS_UNCAUGHT(status, napi_async_init, );

	napi_value resource_object;
	status = napi_create_object(env, &resource_object);
	CHECK_STATUS_UNCAUGHT(status, napi_create_object, );

	napi_value cb;
	status = napi_get_reference_value(env, cb_ref, &cb);
	CHECK_STATUS_UNCAUGHT(status, napi_get_reference_value, );

	napi_value result;
	status = napi_make_callback(env, async_context, resource_object, cb, 0, NULL, &result);

	if (status == napi_pending_exception) {
		napi_value last_exception;
		napi_get_and_clear_last_exception(env, &last_exception);
		napi_fatal_exception(env, last_exception);
		return;
	}

	CHECK_STATUS_UNCAUGHT(status, napi_make_callback, );

	uint32_t new_ref_count;
	status = napi_reference_unref(env, cb_ref, &new_ref_count);
	CHECK_STATUS_UNCAUGHT(status, napi_reference_unref, );

	status = napi_async_destroy(env, async_context);
	CHECK_STATUS_UNCAUGHT(status, napi_async_destroy, );

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, );
}
