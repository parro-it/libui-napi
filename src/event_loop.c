#include <stdbool.h>
#include "napi_utils.h"
#include "app.h"
#include "event-loop.h"

static const char *MODULE = "EventLoop";

static napi_deferred event_loop_closed_deferred = NULL;
static napi_deferred event_loop_started_deferred = NULL;
static napi_env resolution_env = NULL;

atomic_bool running;

atomic_bool mainThreadStillWaitingGuiEvents;

static uv_mutex_t mainThreadWaitingGuiEvents;
static uv_mutex_t mainThreadAwakenFromBackground;
static uv_prepare_t mainThreadAwakenPhase;
static uv_async_t keepAliveTimer;

static uv_thread_t thread;
static uv_timer_t redrawTimer;
static uv_timer_t closeTimer;

/*
   This function is executed in the
   background thread and is responsible for continuosly polling
   the node backend for pending events.

   When pending node events are found, the native GUI
   event loop is wake up by calling uiLoopWakeup().
*/
static void backgroundNodeEventsPoller(void *arg) {
	while (running) {
		LIBUI_NODE_DEBUG("--- wait mainThreadWaitingGuiEvents.\n");

		// wait for the main thread
		// to be blocked waiting for GUI events
		uv_mutex_lock(&mainThreadWaitingGuiEvents);

		// immediately release the lock
		uv_mutex_unlock(&mainThreadWaitingGuiEvents);

		int pendingEvents = 1;
		int timeout = uv_backend_timeout(uv_default_loop());
		LIBUI_NODE_DEBUG_F("--- uv_backend_timeout == %d\n", timeout);

		if (timeout != 0) {
			do {

				LIBUI_NODE_DEBUG_F("--- entering wait with timeout %d\n", timeout);
				/* wait for pending events*/
				pendingEvents = waitForNodeEvents(uv_default_loop(), timeout);

				if (pendingEvents == 0 && timeout > 0) {
					// timers
					pendingEvents = 1;
				}
			} while (pendingEvents == -1 && errno == EINTR);
		}

		LIBUI_NODE_DEBUG_F("--- pendingEvents == %d\n", pendingEvents);

		if (running && mainThreadStillWaitingGuiEvents && pendingEvents > 0) {
			LIBUI_NODE_DEBUG("--- wake up main thread\n");
			// this allow the background thread
			// to wait for the main thread to complete
			// running node callbacks
			uiLoopWakeup();
		}

		if (running && pendingEvents > 0) {
			// wait for the main thread to complete
			// its awaken phase.
			LIBUI_NODE_DEBUG("--- mainThreadAwakenFromBackground locking.\n");
			uv_mutex_lock(&mainThreadAwakenFromBackground);
			LIBUI_NODE_DEBUG("--- mainThreadAwakenFromBackground locked.\n");

			// immediately release the lock
			uv_mutex_unlock(&mainThreadAwakenFromBackground);
		}
	}
	LIBUI_NODE_DEBUG("--- Background terminating.\n");
}

static void redraw(uv_timer_t *handle);

static void uv_awaken_cb(uv_prepare_t *handle) {
	uv_prepare_stop(&mainThreadAwakenPhase);

	if (!running) {
		return;
	}

	LIBUI_NODE_DEBUG("+++ mainThreadAwakenFromBackground unlocking.\n");
	uv_mutex_unlock(&mainThreadAwakenFromBackground);
	LIBUI_NODE_DEBUG("+++ mainThreadAwakenFromBackground unlocked.\n");

	// schedule another call to redraw as soon as possible
	// how to find a correct amount of time to schedule next call?
	//.because too long and UI is not responsive, too short and node
	// become really slow
	uv_timer_start(&redrawTimer, redraw, 10, 0);
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
static void redraw(uv_timer_t *handle) {
	if (!running) {
		return;
	}
	uv_timer_stop(handle);

	// signal the background poller thread
	// that the main one is about to enter
	// the blocking call to wait for GUI events.
	uv_mutex_unlock(&mainThreadWaitingGuiEvents);
	mainThreadStillWaitingGuiEvents = true;

	LIBUI_NODE_DEBUG("+++ locking mainThreadAwakenFromBackground\n");
	uv_mutex_lock(&mainThreadAwakenFromBackground);
	LIBUI_NODE_DEBUG("+++ locked mainThreadAwakenFromBackground\n");

	if (event_loop_started_deferred != NULL) {
		napi_value null;
		napi_get_null(resolution_env, &null);
		napi_handle_scope handle_scope;

		napi_open_handle_scope(resolution_env, &handle_scope);
		napi_resolve_deferred(resolution_env, event_loop_started_deferred, null);
		napi_close_handle_scope(resolution_env, handle_scope);
		resolution_env = NULL;
		event_loop_started_deferred = NULL;
		LIBUI_NODE_DEBUG("🧐 LOOP STARTED");
	}

	/* Blocking call that wait for a node or GUI event pending */
	LIBUI_NODE_DEBUG("+++ blocking GUI\n");
	uiMainStep(true);
	mainThreadStillWaitingGuiEvents = false;
	uv_mutex_lock(&mainThreadWaitingGuiEvents);
	LIBUI_NODE_DEBUG("+++ mainThreadWaitingGuiEvents locked.\n");

	/* dequeue and run every event pending */
	while (uiEventsPending()) {
		running = uiMainStep(false);
		LIBUI_NODE_DEBUG("+++ other GUI event dequeued.\n");
	}
	LIBUI_NODE_DEBUG("+++ all GUI events dequeued.\n");

	// uv_mutex_unlock(&mainThreadAwakenFromBackground);

	// uv_timer_start(redrawTimer, redraw, 100, 0);

	if (running) {
		uv_prepare_start(&mainThreadAwakenPhase, uv_awaken_cb);
		LIBUI_NODE_DEBUG("+++ prepare handler started.\n");
	}
}

/* This function start the event loop and exit immediately */
static void stopAsync(uv_timer_t *handle) {

	LIBUI_NODE_DEBUG_F("stopAsync %d\n", running);
	if (!running) {
		return;
	}

	uv_timer_stop(&closeTimer);
	uv_close((uv_handle_t *)&closeTimer, NULL);

	running = false;

	LIBUI_NODE_DEBUG("stopAsync starting\n");

	/* stop redraw handler */
	uv_timer_stop(&redrawTimer);
	uv_close((uv_handle_t *)&redrawTimer, NULL);
	LIBUI_NODE_DEBUG("redrawTimer stopped\n");

	if (uv_mutex_trylock(&mainThreadWaitingGuiEvents)) {
		uv_mutex_unlock(&mainThreadWaitingGuiEvents);
	}

	if (uv_mutex_trylock(&mainThreadAwakenFromBackground)) {
		uv_mutex_unlock(&mainThreadAwakenFromBackground);
	}

	/* await for the background thread to finish */
	LIBUI_NODE_DEBUG("uv_thread_join wait\n");
	uv_async_send(&keepAliveTimer);
	uv_thread_join(&thread);
	LIBUI_NODE_DEBUG("uv_thread_join done\n");

	uv_mutex_destroy(&mainThreadWaitingGuiEvents);
	LIBUI_NODE_DEBUG("uv_mutex_destroy mainThreadWaitingGuiEvents done\n");

	// TODO: improve synchronization
	// some examples crash while running this
	// uv_mutex_destroy(&mainThreadAwakenFromBackground);
	LIBUI_NODE_DEBUG("uv_mutex_destroy mainThreadAwakenFromBackground done\n");

	/* stop keep alive timer */
	uv_close((uv_handle_t *)&keepAliveTimer, NULL);

	LIBUI_NODE_DEBUG("uv_close keepAliveTimer done\n");

	uv_close((uv_handle_t *)&mainThreadAwakenPhase, NULL);

	/* quit libui event loop */
	uiQuit();

	if (event_loop_closed_deferred != NULL) {
		napi_value null;
		napi_get_null(resolution_env, &null);
		napi_handle_scope handle_scope;
		napi_open_handle_scope(resolution_env, &handle_scope);
		napi_resolve_deferred(resolution_env, event_loop_closed_deferred, null);
		napi_close_handle_scope(resolution_env, handle_scope);
		resolution_env = NULL;
		event_loop_closed_deferred = NULL;
		LIBUI_NODE_DEBUG("🧐 LOOP STOPPED");
	}
}

/* This function start the event loop and exit immediately */
void startLoop() {
	/* if the loop is already running, this is a noop */
	if (running) {
		return;
	}

	running = true;
	mainThreadStillWaitingGuiEvents = false;
	/* init libui event loop */
	uiMainSteps();
	LIBUI_NODE_DEBUG("libui loop initialized");

	// this is used to signal the background thread
	// that the main one is entering a blocking call
	// waiting for GUI events.
	uv_mutex_init(&mainThreadWaitingGuiEvents);

	// lock the mutex to signal that main
	// thread is not yet blocked waiting
	// for GUI events
	uv_mutex_lock(&mainThreadWaitingGuiEvents);

	// this is used to signal the background thread
	// when all pending callback of current tick are
	// called.
	uv_mutex_init(&mainThreadAwakenFromBackground);

	uv_prepare_init(uv_default_loop(), &mainThreadAwakenPhase);

	/* start the background thread that check for node evnts pending */
	uv_thread_create(&thread, backgroundNodeEventsPoller, NULL);
	LIBUI_NODE_DEBUG("background thread started...\n");

	// Add dummy handle for libuv, otherwise libuv would quit when there is
	// nothing to do.
	uv_async_init(uv_default_loop(), &keepAliveTimer, NULL);

	/* start redraw timer */
	uv_timer_init(uv_default_loop(), &redrawTimer);
	uv_timer_start(&redrawTimer, redraw, 1, 0);
}

/* This function start the event loop and exit immediately */
LIBUI_FUNCTION(start) {
	napi_value promise;
	napi_deferred deferred;

	napi_status status = napi_create_promise(env, &deferred, &promise);
	CHECK_STATUS_THROW(status, napi_create_promise);
	LIBUI_NODE_DEBUG("🧐 LOOP STARTING");

	printf("start event_loop_closed_deferred %p event_loop_started_deferred %p\n",
		   event_loop_closed_deferred, event_loop_started_deferred);

	if (event_loop_closed_deferred != NULL) {
		napi_value error;
		napi_value error_msg;
		napi_create_string_utf8(env, "Cannot start. A stop loop operation is pending.",
								NAPI_AUTO_LENGTH, &error_msg);

		napi_create_error(env, NULL, error_msg, &error);
		napi_handle_scope handle_scope;
		napi_open_handle_scope(env, &handle_scope);
		napi_reject_deferred(env, deferred, error);
		napi_close_handle_scope(env, handle_scope);
		return promise;
	}

	if (event_loop_started_deferred != NULL) {
		napi_value error;
		napi_value error_msg;
		napi_create_string_utf8(env, "Cannot start. A start loop operation is pending.",
								NAPI_AUTO_LENGTH, &error_msg);

		napi_create_error(env, NULL, error_msg, &error);

		napi_handle_scope handle_scope;
		napi_open_handle_scope(env, &handle_scope);
		napi_reject_deferred(env, deferred, error);
		napi_close_handle_scope(env, handle_scope);
		return promise;
	}

	event_loop_started_deferred = deferred;

	resolution_env = env;

	startLoop();

	LIBUI_NODE_DEBUG("startLoop async started");

	return promise;
}

LIBUI_FUNCTION(stop) {
	napi_value promise;
	napi_deferred deferred;

	napi_status status = napi_create_promise(env, &deferred, &promise);
	CHECK_STATUS_THROW(status, napi_create_promise);
	LIBUI_NODE_DEBUG("🧐 LOOP STARTING");

	printf("start event_loop_closed_deferred %p event_loop_started_deferred %p\n",
		   event_loop_closed_deferred, event_loop_started_deferred);

	if (event_loop_closed_deferred != NULL) {
		napi_value error;
		napi_value error_msg;
		napi_create_string_utf8(env, "Cannot start. A stop loop operation is pending.",
								NAPI_AUTO_LENGTH, &error_msg);

		napi_create_error(env, NULL, error_msg, &error);
		napi_handle_scope handle_scope;
		napi_open_handle_scope(env, &handle_scope);
		napi_reject_deferred(env, deferred, error);
		napi_close_handle_scope(env, handle_scope);
		return promise;
	}

	if (event_loop_started_deferred != NULL) {
		napi_value error;
		napi_value error_msg;
		napi_create_string_utf8(env, "Cannot start. A start loop operation is pending.",
								NAPI_AUTO_LENGTH, &error_msg);

		napi_create_error(env, NULL, error_msg, &error);

		napi_handle_scope handle_scope;
		napi_open_handle_scope(env, &handle_scope);
		napi_reject_deferred(env, deferred, error);
		napi_close_handle_scope(env, handle_scope);
		return promise;
	}

	event_loop_closed_deferred = deferred;
	resolution_env = env;

	destroy_all_children(env, visible_windows);
	clear_children(env, visible_windows);
	visible_windows = create_children_list();

	LIBUI_NODE_DEBUG("visible windows cleaned up");

	uv_timer_init(uv_default_loop(), &closeTimer);
	uv_timer_start(&closeTimer, stopAsync, 1, 0);

	LIBUI_NODE_DEBUG("stop async started");

	return promise;
}

// this function signal make background
// to stop awaiting node events, allowing it
// to update the list of handles it's
// awaiting for.
LIBUI_FUNCTION(wakeupBackgroundThread) {
	uv_async_send(&keepAliveTimer);
	return NULL;
}

napi_value _libui_init_event_loop(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(wakeupBackgroundThread);
	LIBUI_EXPORT(start);
	LIBUI_EXPORT(stop);
	return module;
}
