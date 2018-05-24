#include "napi_utils.h"
#include "event-loop.h"

static const char *MODULE = "EventLoop";

enum ln_loop_status new_status_to_set;
/*
static void reject_promise_timer(uv_prepare_t *handle) {
	uv_prepare_stop(handle);

	napi_env env = *env_to_resolve;
	napi_deferred deferred = *deferred_to_resolve;
	napi_value napi_error_msg;
	napi_create_string_utf8(env, error_message_to_resolve, NAPI_AUTO_LENGTH, &napi_error_msg);

	napi_value error;
	napi_create_error(env, NULL, napi_error_msg, &error);

	napi_status status;

	napi_handle_scope handle_scope;
	status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, );

	napi_value resource_object;
	status = napi_create_object(env, &resource_object);
	CHECK_STATUS_UNCAUGHT(status, napi_create_object, );

	napi_value async_resource_name;
	status =
		napi_create_string_utf8(env, "event_loop_promise", NAPI_AUTO_LENGTH, &async_resource_name);
	CHECK_STATUS_UNCAUGHT(status, napi_create_string_utf8, );

	napi_async_context async_context;
	status = napi_async_init(env, NULL, async_resource_name, &async_context);
	CHECK_STATUS_UNCAUGHT(status, napi_async_init, );

	napi_callback_scope scope;
	status = napi_open_callback_scope(env, resource_object, async_context, &scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_callback_scope, );

	*env_to_resolve = NULL;
	*deferred_to_resolve = NULL;
	LIBUI_NODE_DEBUG("Rejecting promise");
	status = napi_reject_deferred(env, deferred, error);

	LIBUI_NODE_DEBUG("Rejecting promise");

	CHECK_STATUS_UNCAUGHT(status, napi_resolve_deferred, );

	status = napi_close_callback_scope(env, scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_callback_scope, );

	status = napi_async_destroy(env, async_context);
	CHECK_STATUS_UNCAUGHT(status, napi_async_destroy, );

	status = napi_close_handle_scope(env, handle_scope);
}

static void resolve_promise_timer(uv_prepare_t *handle) {
	LIBUI_NODE_DEBUG("resolve promise prepare");
	uv_prepare_stop(handle);
	LIBUI_NODE_DEBUG("timer stopped");
	napi_env env = *env_to_resolve;
	napi_deferred deferred = *deferred_to_resolve;

	napi_value null;
	napi_status status;

	status = napi_get_null(env, &null);
	CHECK_STATUS_UNCAUGHT(status, napi_get_null, );

	napi_handle_scope handle_scope;
	status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, );
	LIBUI_NODE_DEBUG("timer napi_open_handle_scope");

	napi_value resource_object;
	status = napi_create_object(env, &resource_object);
	CHECK_STATUS_UNCAUGHT(status, napi_create_object, );

	napi_value async_resource_name;
	status =
		napi_create_string_utf8(env, "event_loop_promise", NAPI_AUTO_LENGTH, &async_resource_name);
	CHECK_STATUS_UNCAUGHT(status, napi_create_string_utf8, );

	napi_async_context async_context;
	status = napi_async_init(env, NULL, async_resource_name, &async_context);
	CHECK_STATUS_UNCAUGHT(status, napi_async_init, );

	napi_callback_scope scope;
	status = napi_open_callback_scope(env, resource_object, async_context, &scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_callback_scope, );
	LIBUI_NODE_DEBUG("timer napi_open_callback_scope");

	*env_to_resolve = NULL;
	*deferred_to_resolve = NULL;
	ln_set_loop_status(new_status_to_set);

	LIBUI_NODE_DEBUG("Resolving promise");
	status = napi_resolve_deferred(env, deferred, null);
	LIBUI_NODE_DEBUG("Resolved promise");

	CHECK_STATUS_UNCAUGHT(status, napi_resolve_deferred, );

	status = napi_close_callback_scope(env, scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_callback_scope, );

	status = napi_async_destroy(env, async_context);
	CHECK_STATUS_UNCAUGHT(status, napi_async_destroy, );

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, );

	uv_close((uv_handle_t *)handle, NULL);
}
*/
void reject_promise(napi_env *env, napi_ref *cb_ref, char *error_message) {
	printf("%s\n", error_message);

	/*env_to_resolve = env;
	deferred_to_resolve = deferred;
	error_message_to_resolve = error_message;

	resolve_timer = malloc(sizeof(uv_timer_t));
	uv_timer_init(uv_default_loop(), resolve_timer);
	uv_timer_start(resolve_timer, reject_promise_timer, 1, 0);
	timer_initialized = true;
	*/
}

void resolve_promise_null(napi_env env, napi_ref cb_ref, enum ln_loop_status new_status) {
	printf("ciccio\n");
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
