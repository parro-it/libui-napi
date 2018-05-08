#define RUN_TEST(FN)                                                                               \
	{                                                                                              \
		printf("Running %s ... ", #FN);                                                            \
		FN(env);                                                                                   \
		printf("OK\n");                                                                            \
	}

void children_list_create_suite(napi_env env);
void children_list_add_child_suite(napi_env env);
void control_handle_new_suite(napi_env env);
void children_list_clear_children_suite(napi_env env);
void children_list_remove_child_at_suite(napi_env env);
void children_list_remove_child_suite(napi_env env);
