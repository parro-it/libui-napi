#include "napi_utils.h"
#include "event-loop.h"

static const char *MODULE = "EventLoop";

static napi_env *env_to_resolve;
static napi_deferred *deferred_to_resolve;
static char *error_message_to_resolve;
enum ln_loop_status new_status_to_set;
static uv_timer_t resolve_timer;

static void reject_promise_timer(uv_timer_t *handle) {
	uv_timer_stop(handle);
	uv_close((uv_handle_t *)handle, NULL);

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
	status = napi_create_string_utf8(env, "start_promise", NAPI_AUTO_LENGTH, &async_resource_name);
	CHECK_STATUS_UNCAUGHT(status, napi_create_string_utf8, );

	napi_async_context async_context;
	status = napi_async_init(env, NULL, async_resource_name, &async_context);
	CHECK_STATUS_UNCAUGHT(status, napi_async_init, );

	napi_callback_scope scope;
	status = napi_open_callback_scope(env, resource_object, async_context, &scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_callback_scope, );

	*env_to_resolve = NULL;
	*deferred_to_resolve = NULL;
	LIBUI_NODE_DEBUG("Resolving start promise");
	status = napi_reject_deferred(env, deferred, error);

	LIBUI_NODE_DEBUG("Resolved start promise");

	CHECK_STATUS_UNCAUGHT(status, napi_resolve_deferred, );

	status = napi_close_callback_scope(env, scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_callback_scope, );

	status = napi_async_destroy(env, async_context);
	CHECK_STATUS_UNCAUGHT(status, napi_async_destroy, );

	status = napi_close_handle_scope(env, handle_scope);
}

static void resolve_promise_timer(uv_timer_t *handle) {
	uv_timer_stop(handle);
	uv_close((uv_handle_t *)handle, NULL);

	napi_env env = *env_to_resolve;
	napi_deferred deferred = *deferred_to_resolve;

	napi_value null;
	napi_status status;

	status = napi_get_null(env, &null);
	CHECK_STATUS_UNCAUGHT(status, napi_get_null, );

	napi_handle_scope handle_scope;
	status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, );

	napi_value resource_object;
	status = napi_create_object(env, &resource_object);
	CHECK_STATUS_UNCAUGHT(status, napi_create_object, );

	napi_value async_resource_name;
	status = napi_create_string_utf8(env, "start_promise", NAPI_AUTO_LENGTH, &async_resource_name);
	CHECK_STATUS_UNCAUGHT(status, napi_create_string_utf8, );

	napi_async_context async_context;
	status = napi_async_init(env, NULL, async_resource_name, &async_context);
	CHECK_STATUS_UNCAUGHT(status, napi_async_init, );

	napi_callback_scope scope;
	status = napi_open_callback_scope(env, resource_object, async_context, &scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_callback_scope, );

	*env_to_resolve = NULL;
	*deferred_to_resolve = NULL;
	ln_set_loop_status(new_status_to_set);

	LIBUI_NODE_DEBUG("Resolving start promise");
	status = napi_resolve_deferred(env, deferred, null);
	LIBUI_NODE_DEBUG("Resolved start promise");

	CHECK_STATUS_UNCAUGHT(status, napi_resolve_deferred, );

	status = napi_close_callback_scope(env, scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_callback_scope, );

	status = napi_async_destroy(env, async_context);
	CHECK_STATUS_UNCAUGHT(status, napi_async_destroy, );

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, );
}

void reject_promise(napi_env *env, napi_deferred *deferred, char *error_message) {
	env_to_resolve = env;
	deferred_to_resolve = deferred;
	error_message_to_resolve = error_message;
	uv_timer_init(uv_default_loop(), &resolve_timer);
	uv_timer_start(&resolve_timer, reject_promise_timer, 1, 0);
}

void resolve_promise_null(napi_env *env, napi_deferred *deferred, enum ln_loop_status new_status) {
	env_to_resolve = env;
	deferred_to_resolve = deferred;
	new_status_to_set = new_status;
	uv_timer_init(uv_default_loop(), &resolve_timer);
	uv_timer_start(&resolve_timer, resolve_promise_timer, 1, 0);
}
