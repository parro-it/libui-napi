#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ui.h>
#include "events.h"
#include "tests.h"

static const char *test_name = "test-event";

static struct event_t *make_event(napi_env env) {
	napi_value object;
	napi_create_object(env, &object);
	napi_ref ref;
	napi_create_reference(env, object, 0, &ref);
	struct event_t *event = create_event(env, ref, test_name);
	return event;
}

static void create_event_set_reference(napi_env env) {
	struct event_t *event = make_event(env);

	uint32_t ref_count;
	napi_reference_unref(env, event->cb_ref, &ref_count);
	assert(ref_count == 0);
}

static void create_event_set_name(napi_env env) {
	struct event_t *event = make_event(env);
	assert(event->name == test_name);
}

static void create_event_set_env(napi_env env) {
	struct event_t *event = make_event(env);
	assert(event->env == env);
}

void create_event_suite(napi_env env) {
	RUN_TEST(create_event_set_reference);
	RUN_TEST(create_event_set_name);
	RUN_TEST(create_event_set_env);
}
