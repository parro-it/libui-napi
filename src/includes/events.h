#ifndef LIBUI_NODE_EVENTS_H__
#define LIBUI_NODE_EVENTS_H__

#include "ui.h"
#include "napi_utils.h"
#include "control.h"

/*
	this structure represent a node of the linked list
	of events in a control.
*/
struct events_node {
	struct event_t *event;
	struct events_node *next;
};

/*
	this structure represent a linked list
	of events in a control.
*/
struct events_list {
	struct events_node *head;
	struct events_node *tail;
};

/*
	this structure represent an event of the framework
*/
struct event_t {
	/*
		This flag is set when a struct event_t
		represent an empty event, used to remove
		existing events from an events_list
	*/
	bool is_empty;

	/*
		a reference to the JavaScript function to call when event is fired.
		It prevent the JavaScript function to be garbage collected, and is
	   normally released when the event control is destroyed.
	 */
	napi_ref cb_ref;

	/*
		the JavaScript environment instance to execute the event callback on
	*/
	napi_env env;

	/*
		the async context to use to call the callback.
		it allow to integrate the callback with async hooks, allowing
		debuggers to provide async stack trace for the call.
	*/
	napi_async_context context;

	const char *name;
};

/*
	create and return a structure that represent an event, given
	the JavaScript environment, a reference to the JavaScript function
	to call when the event is fired, and the name of the event to use
	for async hooks integrations.
*/
struct event_t *create_event(napi_env env, napi_ref cb_ref, const char *name);

/*
	call the JavaScript function associated with an event.
*/
napi_value fire_event(struct event_t *event);
napi_value fire_event_args(struct event_t *event, int argc, napi_value *argv);

/*
	release the reference to the JavaScript function associated with an event,
	making the function garbage collectable (if it isn't accessible in JS side
	from other references).
	Also free the memory asociated with the event struct.
*/
napi_value clear_event(struct event_t *event);

/*
	install a new event into a control handle.
*/
void install_event(struct events_list *events, struct event_t *event);

/*
	remove and free all events of a control.
*/
void clear_all_events(struct events_list *events);

#endif
