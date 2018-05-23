#include "events.h"
#include "tests.h"

static const char *test_name = "test-event-2";

static struct events_list *make_list() {
	return calloc(1, sizeof(struct events_list));
}

static struct event_t *make_event(napi_env env) {
	napi_value object;
	napi_create_object(env, &object);
	napi_ref ref;
	napi_create_reference(env, object, 0, &ref);
	struct event_t *event = create_event(env, ref, test_name);
	return event;
}

static void install_event_first_element_set_head_tail(napi_env env) {
	struct event_t *event = make_event(env);
	struct events_list *list = make_list();
	install_event(list, event);

	assert(list->head != NULL);
	assert(list->head->event == event);
	assert(list->head == list->tail);
	assert(list->head->next == NULL);
}

static void install_event_other_element_add_to_tail(napi_env env) {
	struct event_t *event1 = make_event(env);
	struct event_t *event2 = make_event(env);
	struct events_list *list = make_list();
	install_event(list, event1);
	install_event(list, event2);

	assert(list->head->event == event1);
	assert(list->tail->event == event2);
	assert(list->head->next == list->tail);
	assert(list->tail->next == NULL);
}

void install_event_suite(napi_env env) {
	SUITE();
	RUN_TEST(install_event_first_element_set_head_tail);
	RUN_TEST(install_event_other_element_add_to_tail);
}
