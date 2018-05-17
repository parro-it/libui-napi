#ifndef LIBUI_NODE_EVENT_LOOP_H__
#define LIBUI_NODE_EVENT_LOOP_H__ 1

#include <uv.h>
#include "ui.h"

int uiEventsPending();
int uiLoopWakeup();
int waitForNodeEvents(uv_loop_t *loop, int timeout);

void stopLoop();
void startLoop();

#ifdef _WIN32
#define atomic_bool bool
#else
#define atomic_bool bool _Atomic
#endif

#endif
