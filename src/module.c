#include "modules.h"

static napi_value init_all (napi_env env, napi_value exports) {
	_libui_init_core(env, exports);
	_libui_init_window(env, exports);
	_libui_init_multilineEntry(env, exports);
	_libui_init_event_loop(env, exports);
	_libui_init_box(env, exports);
	_libui_init_slider(env, exports);
	_libui_init_label(env, exports);
	_libui_init_form(env, exports);

	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init_all)
