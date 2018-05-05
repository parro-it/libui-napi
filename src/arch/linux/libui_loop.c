#include "event-loop-linux.h"
#include "event-loop.h"

int uiLoopWakeup() {
	g_main_context_wakeup(NULL);
	return 0;
}

int uiEventsPending() {
	return gtk_events_pending();
}

int waitForNodeEvents(uv_loop_t *loop, int timeout) {
	int nodeBackendFd = uv_backend_fd(loop);

	if (nodeBackendFd == -1) {
		fprintf(stderr, "Invalid node backend fd.\n");
		return 0;
	}

	struct epoll_event ev;

	return epoll_wait(nodeBackendFd, &ev, 1, timeout);
}
