#include "napi_utils.h"
#include "event-loop.h"

static enum ln_loop_status status = stopped;
static bool main_thread_waiting = false;
static bool main_thread_quitted = false;
static bool background_thread_waiting = false;

static uv_sem_t sem_status;
static uv_sem_t sem_quitted;
static uv_sem_t sem_main_thread;
static uv_sem_t sem_background_thread;

#if UI_NODE_DEBUG
static const char *MODULE = "EventLoop";
#endif

void ln_set_main_thread_quitted(bool value) {
	uv_sem_wait(&sem_quitted);
	main_thread_quitted = value;
	uv_sem_post(&sem_quitted);
}

bool ln_get_main_thread_quitted() {
	uv_sem_wait(&sem_quitted);
	bool ret = main_thread_quitted;
	uv_sem_post(&sem_quitted);

	return ret;
}

void ln_set_main_thread_waiting(bool value) {
	uv_sem_wait(&sem_main_thread);
	main_thread_waiting = value;
	uv_sem_post(&sem_main_thread);
}
void ln_set_background_thread_waiting(bool value) {
	uv_sem_wait(&sem_background_thread);
	background_thread_waiting = value;
	uv_sem_post(&sem_background_thread);
}

bool ln_get_main_thread_waiting() {
	uv_sem_wait(&sem_main_thread);
	bool ret = main_thread_waiting;
	uv_sem_post(&sem_main_thread);

	return ret;
}

bool ln_get_background_thread_waiting() {
	uv_sem_wait(&sem_background_thread);
	bool ret = background_thread_waiting;
	uv_sem_post(&sem_background_thread);

	return ret;
}

enum ln_loop_status ln_get_loop_status() {
	uv_sem_wait(&sem_status);
	enum ln_loop_status ret = status;
	uv_sem_post(&sem_status);
	LIBUI_NODE_DEBUG_F("status ? %d\n", ret);

	return ret;
}

napi_status ln_init_loop_status() {
	if (uv_sem_init(&sem_status, 1) != 0) {
		return napi_generic_failure;
	};
	if (uv_sem_init(&sem_main_thread, 1) != 0) {
		return napi_generic_failure;
	};
	if (uv_sem_init(&sem_background_thread, 1) != 0) {
		return napi_generic_failure;
	};
	if (uv_sem_init(&sem_quitted, 1) != 0) {
		return napi_generic_failure;
	};
	return napi_ok;
}

napi_status ln_set_loop_status(enum ln_loop_status new_status) {
	LIBUI_NODE_DEBUG_F("status ! %d\n", status);
	LIBUI_NODE_DEBUG_F("new_status ! %d\n", new_status);

	switch (status) {
	case stopped:
		if (new_status != starting) {
			return napi_invalid_arg;
		}
		break;
	case stopping:
		if (new_status != stopped) {
			return napi_invalid_arg;
		}
		break;
	case started:
		if (new_status != stopping) {
			return napi_invalid_arg;
		}
		break;
	case starting:
		if (new_status != started) {
			return napi_invalid_arg;
		}
		break;
	default:
		return napi_invalid_arg;
	}

	uv_sem_wait(&sem_status);
	status = new_status;
	uv_sem_post(&sem_status);
	LIBUI_NODE_DEBUG_F("status = %d\n", status);

	return napi_ok;
}
