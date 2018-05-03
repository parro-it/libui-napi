#ifndef LIBUI_NODE_EVENT_LOOP_H__
#define LIBUI_NODE_EVENT_LOOP_H__ 1

#include <uv.h>
#include "ui.h"

int uiEventsPending();
int uiLoopWakeup();
int waitForNodeEvents(uv_loop_t *loop, int timeout);

void wakeupBackgroundThread();
void stopLoop();
void startLoop();

#endif
