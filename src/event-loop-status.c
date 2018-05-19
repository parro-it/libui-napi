#include "event-loop.h"

static enum ln_loop_status status = stopped;
static uv_sem_t sem_status;

enum ln_loop_status ln_get_loop_status() {
	uv_sem_wait(&sem_status);
	enum ln_loop_status ret = status;
	uv_sem_post(&sem_status);
	printf("status ? %d\n", ret);

	return ret;
}

napi_status ln_init_loop_status() {
	if (uv_sem_init(&sem_status, 1) != 0) {
		return napi_generic_failure;
	};
	return napi_ok;
}

napi_status ln_set_loop_status(enum ln_loop_status new_status) {
	printf("status ! %d\n", status);
	printf("new_status ! %d\n", new_status);

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
	printf("status = %d\n", status);
	uv_sem_post(&sem_status);

	return napi_ok;
}
