#include "napi_utils.h"
#include "tests.h"
static const char *MODULE = "check_c_tests";

int test_counter = 1;
int test_counter_pass = 0;
int test_counter_fail = 0;
bool test_failed = false;
char *test_error;

LIBUI_FUNCTION(run_tests) {
	INIT_ARGS(1);
	ARG_UINT32(start, 0);
	test_counter = start;

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

	napi_value result;
	napi_handle_scope handle_scope;
	napi_status status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_THROW(status, napi_open_handle_scope);

	status = napi_create_object(env, &result);
	CHECK_STATUS_THROW(status, napi_create_object);

	status = napi_set_named_property(env, result, "count", make_uint32(env, test_counter - start));
	CHECK_STATUS_THROW(status, napi_set_named_property);
	status = napi_set_named_property(env, result, "pass", make_uint32(env, test_counter_pass));
	CHECK_STATUS_THROW(status, napi_set_named_property);
	status = napi_set_named_property(env, result, "fail", make_uint32(env, test_counter_fail));
	CHECK_STATUS_THROW(status, napi_set_named_property);

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_THROW(status, napi_close_handle_scope);

	return result;
}

napi_value _libui_init_tests(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(run_tests);
	return module;
}
