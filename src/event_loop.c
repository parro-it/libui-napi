#include <assert.h>
#include <stdbool.h>
#include "napi_utils.h"
#include "app.h"
#include "event-loop.h"
static const char *MODULE = "EventLoop";

static uv_barrier_t all_threads_are_waiting;
static uv_barrier_t all_threads_are_awaked;

static napi_ref event_loop_closed_cb_ref = NULL;
static napi_ref event_loop_started_cb_ref = NULL;
static napi_env resolution_env = NULL;

static uv_async_t *keep_alive;

static uv_thread_t thread;
static uv_timer_t main_thread_timer;

/*
	wait for pending events

*/
void wait_node_io(int timeout) {
	int ret;
	LIBUI_NODE_DEBUG_F("--- entering wait with timeout %d", timeout);
	do {
		ret = waitForNodeEvents(uv_default_loop(), timeout);
	} while (ret == -1 && errno == EINTR);
	LIBUI_NODE_DEBUG("--- wait done");
}

/*
	This function is executed in the
	background thread and is responsible for continuosly polling
	the node backend for pending events.

	When pending node events are found, the main GUI
	thread, if it's waiting, is wake up by calling uiLoopWakeup().
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
		// If timeout == -1, it means to wait forever.
		// When timeout > 0. it means there are one or more timers
		// pending, and the first one will expire in
		// `timeout` ms

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
		// to be unblocked.
		uv_barrier_wait(&all_threads_are_awaked);
	}

	LIBUI_NODE_DEBUG("--- background terminating.");
}

/*
	This function run all pending native GUI event in the loop
	using libui calls.

	It first do a blocking call to uiMainStep that
	wait for pending GUI events. This blocking call also exit
	when there are pending node events, because uiLoopWakeup
	function posts a GUI event
	from the background thread for this purpose.
 */
static void main_thread(uv_timer_t *handle) {
	enum ln_loop_status status = ln_get_loop_status();
	LIBUI_NODE_DEBUG_F("+++ start main_thread with status %d", status);
	uv_timer_stop(handle);
	if (status == starting) {
		assert(event_loop_started_cb_ref != NULL);

		LIBUI_NODE_DEBUG("🧐 LOOP STARTED");
		napi_ref ref = event_loop_started_cb_ref;
		event_loop_started_cb_ref = NULL;
		resolve_promise_null(resolution_env, ref, started);
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
		uv_async_send(keep_alive);
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
		// uv_close((uv_handle_t *)&main_thread_timer, NULL);
		LIBUI_NODE_DEBUG("+++ main_thread_timer closed");

		/* await for the background thread to finish */
		LIBUI_NODE_DEBUG("uv_thread_join wait");
		uv_thread_join(&thread);
		LIBUI_NODE_DEBUG("uv_thread_join done");

		/* stop keep alive timer */
		uv_close((uv_handle_t *)keep_alive, NULL);
		LIBUI_NODE_DEBUG("uv_close keep_alive done");

		assert(event_loop_closed_cb_ref != NULL);

		LIBUI_NODE_DEBUG("🧐 LOOP STOPPED");
		napi_ref ref = event_loop_closed_cb_ref;
		event_loop_closed_cb_ref = NULL;
		resolve_promise_null(resolution_env, ref, stopped);

		LIBUI_NODE_DEBUG("resolved stop promise");
	}
}

/* This function start the event loop and exit immediately */
LIBUI_FUNCTION(start) {
	INIT_ARGS(1);
	ARG_CB_REF(cb_ref, 0);

	if (event_loop_closed_cb_ref != NULL) {
		napi_throw_error(env, NULL, "Cannot start. A stop loop operation is pending.");
		return NULL;
	}

	if (event_loop_started_cb_ref != NULL) {
		napi_throw_error(env, NULL, "Cannot start. A start loop operation is pending.");
		return NULL;
	}

	LIBUI_NODE_DEBUG("🧐 LOOP STARTING");
	uv_barrier_init(&all_threads_are_waiting, 2);
	uv_barrier_init(&all_threads_are_awaked, 2);

	event_loop_started_cb_ref = cb_ref;

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
	keep_alive = malloc(sizeof(uv_async_t));
	uv_async_init(uv_default_loop(), keep_alive, NULL);

	/* start main_thread timer */
	uv_timer_init(uv_default_loop(), &main_thread_timer);
	uv_timer_start(&main_thread_timer, main_thread, 1, 0);

	LIBUI_NODE_DEBUG("startLoop async started");

	return NULL;
}

LIBUI_FUNCTION(stop) {
	INIT_ARGS(1);
	ARG_CB_REF(cb_ref, 0);

	LIBUI_NODE_DEBUG("🧐 LOOP STOPPING");

	if (event_loop_closed_cb_ref != NULL) {
		napi_throw_error(env, NULL, "Cannot start. A stop loop operation is pending.");
		return NULL;
	}

	if (event_loop_started_cb_ref != NULL) {
		napi_throw_error(env, NULL, "Cannot start. A start loop operation is pending.");
		return NULL;
	}

	ln_set_loop_status(stopping);

	event_loop_closed_cb_ref = cb_ref;
	resolution_env = env;

	destroy_all_children(env, visible_windows);
	clear_children(env, visible_windows);
	visible_windows = create_children_list();

	LIBUI_NODE_DEBUG("visible windows cleaned up");

	uiQuit();

	LIBUI_NODE_DEBUG("uiQuit called");

	return NULL;
}

// this function signal background thread
// to stop awaiting node events, allowing it
// to update the list of handles it's
// awaiting on.
LIBUI_FUNCTION(wakeupBackgroundThread) {
	if (uv_is_active((const uv_handle_t *)keep_alive)) {
		uv_async_send(keep_alive);
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
