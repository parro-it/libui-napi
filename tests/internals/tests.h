#include <node_api.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ui.h>

extern int test_counter;
extern bool test_failed;
extern char *test_error;

#define RUN_TEST(FN)                                                                               \
	{                                                                                              \
		test_failed = false;                                                                       \
		FN(env);                                                                                   \
		if (test_failed) {                                                                         \
			printf("not ok %d %s\n", test_counter++, #FN);                                         \
			printf("  ---\n    message: %s\n  ...", test_error);                                   \
		} else {                                                                                   \
			printf("ok %d %s\n", test_counter++, #FN);                                             \
		}                                                                                          \
	}

#define assert(V)                                                                                  \
	{                                                                                              \
		if (!(V)) {                                                                                \
			test_failed = true;                                                                    \
			sprintf(test_error, "assertion (%s) %s %s:%d\n", #V, __func__, __FILE__, __LINE__);    \
		}                                                                                          \
	}

#define SUITE(NAME)                                                                                \
	{ printf("# %s\n", __func__); }

void children_list_create_suite(napi_env env);
void children_list_add_child_suite(napi_env env);
void children_list_clear_children_suite(napi_env env);
void children_list_remove_child_at_suite(napi_env env);
void children_list_remove_child_suite(napi_env env);
void children_list_add_child_at_suite(napi_env env);
void control_on_destroy_suite(napi_env env);
void create_event_suite(napi_env env);
void clear_event_suite(napi_env env);
void install_event_suite(napi_env env);
