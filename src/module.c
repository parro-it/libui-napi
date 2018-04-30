#include "core.h"

static napi_value init_all (napi_env env, napi_value exports) {
	_libui_init_core(env, exports);
	_libui_init_window(env, exports);
	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init_all)
