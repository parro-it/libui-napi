#include "napi_utils.h"
#include "tests.h"
static const char *MODULE = "check_c_tests";

int test_counter = 1;
bool test_failed = false;
char *test_error;

LIBUI_FUNCTION(run_tests) {
	test_error = malloc(sizeof(char) * 256);

	children_list_create_suite(env);
	children_list_add_child_suite(env);
	children_list_clear_children_suite(env);
	children_list_remove_child_at_suite(env);
	children_list_remove_child_suite(env);
	children_list_add_child_at_suite(env);
	control_on_destroy_suite(env);
	create_event_suite(env);
	clear_event_suite(env);
	install_event_suite(env);

	free(test_error);
	return NULL;
}

napi_value _libui_init_tests(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(run_tests);
	return module;
}
