#define RUN_TEST(FN)                                                                               \
	{                                                                                              \
		printf("Running %s ... ", #FN);                                                            \
		FN(env);                                                                                   \
		printf("OK\n");                                                                            \
	}

void children_list_create_suite(napi_env env);
void children_list_add_child_suite(napi_env env);
void children_list_clear_children_suite(napi_env env);
void children_list_remove_child_at_suite(napi_env env);
void children_list_remove_child_suite(napi_env env);
void children_list_add_child_at_suite(napi_env env);
void control_on_destroy_suite(napi_env env);
void create_event_suite(napi_env env);
void clear_event_suite(napi_env env);
