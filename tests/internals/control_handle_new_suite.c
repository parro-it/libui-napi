#include <assert.h>
#include <stdlib.h>
#include <ui.h>
#include "control.h"
#include "tests.h"

static void test_return_non_null_on_success(napi_env env) {
	uiControl *ctrl = malloc(sizeof(uiControl));
	napi_value result = control_handle_new(env, ctrl, "name_test");
	assert(result != NULL);
}

void control_handle_new_suite(napi_env env) {
	RUN_TEST(test_return_non_null_on_success);
}
