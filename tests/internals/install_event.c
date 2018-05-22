#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ui.h>
#include "events.h"
#include "tests.h"

static struct events_list *make_list() {
	return calloc(1, sizeof(struct events_list));
}

static struct event_t *make_event(napi_env env, char *name) {
	napi_value object;
	napi_create_object(env, &object);
	napi_ref ref;
	napi_create_reference(env, object, 0, &ref);
	struct event_t *event = create_event(env, ref, name);
	return event;
}

static void install_event_first_element_set_head_tail(napi_env env) {
	struct event_t *event = make_event(env, "test-event-1");
	struct events_list *list = make_list();
	install_event(list, event);

	assert(list->head != NULL);
	assert(list->head->event == event);
	assert(list->head == list->tail);
	assert(list->head->next == NULL);
}

static void install_event_other_element_add_to_tail(napi_env env) {
	struct event_t *event1 = make_event(env, "test-event-1");
	struct event_t *event2 = make_event(env, "test-event-2");
	struct events_list *list = make_list();
	install_event(list, event1);
	install_event(list, event2);

	assert(list->head->event == event1);
	assert(list->tail->event == event2);
	assert(list->head->next == list->tail);
	assert(list->tail->next == NULL);
}

static void install_event_replace_element_at_head(napi_env env) {
	struct event_t *event1 = make_event(env, "test-event-1");
	struct event_t *event2 = make_event(env, "test-event-1");
	struct events_list *list = make_list();
	install_event(list, event1);
	install_event(list, event2);

	assert(list->head->event == event2);
	assert(list->tail->event == event2);
	assert(list->head->next == NULL);
	assert(list->tail->next == NULL);
}

static void install_event_replace_element_at_tail(napi_env env) {
	struct event_t *event1 = make_event(env, "test-event-1");
	struct event_t *event2 = make_event(env, "test-event-2");
	struct event_t *event2_2 = make_event(env, "test-event-2");
	struct events_list *list = make_list();
	install_event(list, event1);
	install_event(list, event2);
	install_event(list, event2_2);

	assert(list->head->event == event1);
	assert(list->tail->event == event2_2);
	assert(list->head->next == list->tail);
	assert(list->tail->next == NULL);
}

static void install_event_replace_element_middle(napi_env env) {
	struct event_t *event1 = make_event(env, "test-event-1");
	struct event_t *event2 = make_event(env, "test-event-2");
	struct event_t *event3 = make_event(env, "test-event-3");
	struct event_t *event2_2 = make_event(env, "test-event-2");
	struct events_list *list = make_list();
	install_event(list, event1);
	install_event(list, event2);
	install_event(list, event3);
	install_event(list, event2_2);

	assert(list->head->event == event1);
	assert(list->head->next->event == event3);
	assert(list->tail->event == event2_2);
	assert(list->head->next->next == list->tail);
	assert(list->tail->next == NULL);
}

void install_event_suite(napi_env env) {
	RUN_TEST(install_event_first_element_set_head_tail);
	RUN_TEST(install_event_other_element_add_to_tail);
	RUN_TEST(install_event_replace_element_at_head);
	RUN_TEST(install_event_replace_element_at_tail);
	RUN_TEST(install_event_replace_element_middle);
}
