#include <assert.h>
#include <stdbool.h>
#include "napi_utils.h"
#include "app.h"
#include "event-loop.h"
static const char *MODULE = "EventLoop";

static uv_barrier_t all_threads_are_waiting;
static uv_barrier_t all_threads_are_awaked;

static napi_deferred event_loop_closed_deferred = NULL;
static napi_deferred event_loop_started_deferred = NULL;
static napi_env resolution_env = NULL;

static uv_async_t keep_alive;

static uv_thread_t thread;

static uv_timer_t main_thread_timer;

void wait_node_io(int timeout) {
	int ret;
	do {

		LIBUI_NODE_DEBUG_F("--- entering wait with timeout %d", timeout);
		/*
			wait for pending events
			a timeout of -1 means to wait forever.
		*/
		ret = waitForNodeEvents(uv_default_loop(), timeout);
		LIBUI_NODE_DEBUG("--- wait done");
	} while (ret == -1 && errno == EINTR);
}

/*
   This function is executed in the
   background thread and is responsible for continuosly polling
   the node backend for pending events.

   When pending node events are found, the native GUI
   event loop is wake up by calling uiLoopWakeup().
*/
static void background_thread(void *arg) {
	LIBUI_NODE_DEBUG("--- start background_thread ");

	while (!ln_get_main_thread_quitted()) {
		LIBUI_NODE_DEBUG("--- wait on all_threads_are_waiting.");

		ln_set_background_thread_waiting(true);

		// wait for the main thread
		// to be blocked waiting for GUI events
		uv_barrier_wait(&all_threads_are_waiting);
		LIBUI_NODE_DEBUG("--- all_threads_are_waiting passed.");

		int timeout = uv_backend_timeout(uv_default_loop());
		LIBUI_NODE_DEBUG_F("--- uv_backend_timeout == %d", timeout);

		// if timeout == 0, it means there are
		// already some callback to execute, so no
		// IO wait is necessary.
		if (timeout != 0) {
			LIBUI_NODE_DEBUG("--- wait node io");
			wait_node_io(timeout);
			LIBUI_NODE_DEBUG("--- done wait node io");

			if (ln_get_main_thread_waiting()) {
				LIBUI_NODE_DEBUG("--- wake up main thread");
				ln_set_background_thread_waiting(false);
				uiLoopWakeup();
			}
		} else {
			ln_set_background_thread_waiting(false);
		}

		// wait for the main thread
		// to be blocked waiting for GUI events
		uv_barrier_wait(&all_threads_are_awaked);
	}

	LIBUI_NODE_DEBUG("--- background terminating.");
}

/*
	This function run all pending native GUI event in the loop
	using libui calls.

	It first do a blocking call to uiMainStep that
	wait for pending GUI events.
	The function also exit when there are pending node
	events, because uiLoopWakeup function posts a GUI event
	from the background thread for this purpose.
 */
static void main_thread(uv_timer_t *handle) {
	enum ln_loop_status status = ln_get_loop_status();
	LIBUI_NODE_DEBUG_F("+++ start main_thread with status %d", status);
	uv_timer_stop(handle);

	if (status == starting) {
		assert(event_loop_started_deferred != NULL);

		napi_value null;
		napi_get_null(resolution_env, &null);
		napi_handle_scope handle_scope;

		napi_open_handle_scope(resolution_env, &handle_scope);
		napi_resolve_deferred(resolution_env, event_loop_started_deferred, null);
		napi_close_handle_scope(resolution_env, handle_scope);
		resolution_env = NULL;
		event_loop_started_deferred = NULL;
		ln_set_loop_status(started);
		LIBUI_NODE_DEBUG("🧐 LOOP STARTED");
	}

	LIBUI_NODE_DEBUG("+++ wait on all_threads_are_waiting");

	// wait for the background thread
	// to be blocked waiting for node events
	uv_barrier_wait(&all_threads_are_waiting);

	LIBUI_NODE_DEBUG("+++ passed all_threads_are_waiting");

	int timeout = uv_backend_timeout(uv_default_loop());

	int gui_running = 1;

	if (timeout != 0) {

		LIBUI_NODE_DEBUG("+++ wait GUI events");

		ln_set_main_thread_waiting(true);
		LIBUI_NODE_DEBUG("+++ ln_set_main_thread_waiting true");

		gui_running = uiMainStep(true);
		LIBUI_NODE_DEBUG("+++ uiWaitForEvents done");

		ln_set_main_thread_waiting(false);
		LIBUI_NODE_DEBUG("+++ ln_set_main_thread_waiting false");
	}

	if (ln_get_background_thread_waiting()) {
		LIBUI_NODE_DEBUG("+++ wake up background thread");
		uv_async_send(&keep_alive);
	}

	/* dequeue and run every event pending */
	while (gui_running && uiEventsPending()) {
		gui_running = uiMainStep(false);
	}
	LIBUI_NODE_DEBUG("+++ all GUI events worked.");

	if (!gui_running && ln_get_loop_status() == stopping) {
		ln_set_main_thread_quitted(true);
	}

	// wait for the background thread
	// to be unblocked from waiting for node events
	LIBUI_NODE_DEBUG("+++ wait all_threads_are_awaked");
	uv_barrier_wait(&all_threads_are_awaked);
	LIBUI_NODE_DEBUG("+++ passed all_threads_are_awaked");

	LIBUI_NODE_DEBUG_F("+++ libui is running: %d", gui_running);

	if (gui_running || ln_get_loop_status() != stopping) {
		LIBUI_NODE_DEBUG("+++ schedule next main_thread call.");
		uv_timer_start(&main_thread_timer, main_thread, 10, 0);
	} else {
		uv_close((uv_handle_t *)&main_thread_timer, NULL);
		LIBUI_NODE_DEBUG("+++ main_thread_timer closed");

		/* await for the background thread to finish */
		LIBUI_NODE_DEBUG("uv_thread_join wait");
		uv_thread_join(&thread);
		LIBUI_NODE_DEBUG("uv_thread_join done");

		assert(event_loop_closed_deferred != NULL);

		napi_value null;
		napi_get_null(resolution_env, &null);
		napi_handle_scope handle_scope;
		LIBUI_NODE_DEBUG("resolving stop promise");

		napi_open_handle_scope(resolution_env, &handle_scope);
		napi_resolve_deferred(resolution_env, event_loop_closed_deferred, null);
		napi_close_handle_scope(resolution_env, handle_scope);
		LIBUI_NODE_DEBUG("resolved stop promise");

		resolution_env = NULL;
		event_loop_closed_deferred = NULL;
		ln_set_loop_status(stopped);

		/* stop keep alive timer */
		uv_close((uv_handle_t *)&keep_alive, NULL);
		LIBUI_NODE_DEBUG("uv_close keep_alive done");

		LIBUI_NODE_DEBUG("🧐 LOOP STOPPED");
	}
}

static void reject_promise(napi_env env, napi_deferred deferred, const char *error_message) {
	napi_value napi_error_msg;
	napi_create_string_utf8(env, error_message, NAPI_AUTO_LENGTH, &napi_error_msg);

	napi_value error;
	napi_create_error(env, NULL, napi_error_msg, &error);

	napi_handle_scope handle_scope;
	napi_open_handle_scope(env, &handle_scope);
	napi_reject_deferred(env, deferred, error);
	napi_close_handle_scope(env, handle_scope);
}

/* This function start the event loop and exit immediately */
LIBUI_FUNCTION(start) {
	napi_value promise;
	napi_deferred deferred;

	napi_status status = napi_create_promise(env, &deferred, &promise);
	CHECK_STATUS_THROW(status, napi_create_promise);

	if (event_loop_closed_deferred != NULL) {
		reject_promise(env, deferred, "Cannot start. A stop loop operation is pending.");
		return promise;
	}

	if (event_loop_started_deferred != NULL) {
		reject_promise(env, deferred, "Cannot start. A start loop operation is pending.");
		return promise;
	}

	LIBUI_NODE_DEBUG("🧐 LOOP STARTING");
	uv_barrier_init(&all_threads_are_waiting, 2);
	uv_barrier_init(&all_threads_are_awaked, 2);

	event_loop_started_deferred = deferred;

	resolution_env = env;

	ln_set_loop_status(starting);
	ln_set_main_thread_waiting(false);
	ln_set_background_thread_waiting(false);
	ln_set_main_thread_quitted(false);

	/* init libui event loop */
	uiMainSteps();
	LIBUI_NODE_DEBUG("libui loop initialized");

	/* start the background thread that check for node evnts pending */
	uv_thread_create(&thread, background_thread, NULL);
	LIBUI_NODE_DEBUG("background thread started...");

	// Add dummy handle for libuv, otherwise libuv would quit when there is
	// nothing to do.
	uv_async_init(uv_default_loop(), &keep_alive, NULL);

	/* start main_thread timer */
	uv_timer_init(uv_default_loop(), &main_thread_timer);
	uv_timer_start(&main_thread_timer, main_thread, 1, 0);

	LIBUI_NODE_DEBUG("startLoop async started");

	return promise;
}

LIBUI_FUNCTION(stop) {
	napi_value promise;
	napi_deferred deferred;

	napi_status status = napi_create_promise(env, &deferred, &promise);
	CHECK_STATUS_THROW(status, napi_create_promise);
	LIBUI_NODE_DEBUG("🧐 LOOP STOPPING");

	printf("start event_loop_closed_deferred %p event_loop_started_deferred %p",
		   event_loop_closed_deferred, event_loop_started_deferred);

	if (event_loop_closed_deferred != NULL) {
		reject_promise(env, deferred, "Cannot start. A stop loop operation is pending.");
		return promise;
	}

	if (event_loop_started_deferred != NULL) {
		reject_promise(env, deferred, "Cannot start. A start loop operation is pending.");
		return promise;
	}

	ln_set_loop_status(stopping);

	event_loop_closed_deferred = deferred;
	resolution_env = env;

	destroy_all_children(env, visible_windows);
	clear_children(env, visible_windows);
	visible_windows = create_children_list();

	LIBUI_NODE_DEBUG("visible windows cleaned up");

	uiQuit();

	LIBUI_NODE_DEBUG("uiQuit called");

	return promise;
}

// this function signal make background
// to stop awaiting node events, allowing it
// to update the list of handles it's
// awaiting for.
LIBUI_FUNCTION(wakeupBackgroundThread) {
	if (uv_is_active(&keep_alive)) {
		uv_async_send(&keep_alive);
	}
	return NULL;
}

napi_value _libui_init_event_loop(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(wakeupBackgroundThread);
	LIBUI_EXPORT(start);
	LIBUI_EXPORT(stop);
	return module;
}
