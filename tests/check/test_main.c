#include "napi_utils.h"
#include "tests.h"
static const char *MODULE = "check_c_tests";

LIBUI_FUNCTION(run_tests) {
	children_list_create_suite(env);
	control_handle_new_suite(env);
	children_list_add_child_suite(env);
	return NULL;
}

napi_value _libui_init_tests(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(run_tests);
	return module;
}
