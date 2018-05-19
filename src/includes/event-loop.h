#ifndef LIBUI_NODE_EVENT_LOOP_H__
#define LIBUI_NODE_EVENT_LOOP_H__ 1

#include <node_api.h>
#include <uv.h>
#include "ui.h"

int uiEventsPending();
int uiLoopWakeup();
int waitForNodeEvents(uv_loop_t *loop, int timeout);

void stopLoop();
void startLoop();

enum ln_loop_status { stopped, stopping, started, starting };

enum ln_loop_status ln_get_loop_status();
napi_status ln_set_loop_status(enum ln_loop_status new_status);
napi_status ln_init_loop_status();

#ifdef _WIN32
#define atomic_bool bool
#else
#define atomic_bool bool _Atomic
#endif

#endif
