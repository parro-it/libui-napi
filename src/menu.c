#include "ui.h"
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Menu";

struct menu_item_handle {
	uiMenuItem *item;

	/*
		A reference to the JavaScript object that wrap the handle pointer,
		It prevent the JavaScript object to be garbage collected, and is
		released when the control is destroyed.
	*/
	napi_ref item_ref;

	/*
		event registered on this control
	 */
	struct event_t *event;
};

/*
	this structure represent a node of the linked list
	of menu items.
*/
struct menu_item_node {
	struct menu_item_handle *handle;
	struct menu_item_node *next;
};

/*
	this structure represent a linked list
	of menu items.
*/
struct menu_item_list {
	struct menu_item_node *head;
	struct menu_item_node *tail;
};

struct menu_handle {
	uiMenu *menu;

	/*
		A reference to the JavaScript object that wrap the handle pointer,
		It prevent the JavaScript object to be garbage collected, and is
		released when the control is destroyed.
	*/
	napi_ref menu_ref;

	/*
		event registered on this control
	 */
	struct menu_item_list items;
};

struct menu_item_handle *make_menu_item(uiMenuItem *handle) {
	struct menu_item_handle *item = calloc(1, sizeof(struct menu_item_handle));
	item->item = handle;
	return item;
}

struct menu_handle *make_menu(const char *name) {
	struct menu_handle *menu = calloc(1, sizeof(struct menu_handle));
	uiMenu *ui_menu = uiNewMenu(name);
	menu->menu = ui_menu;
	return menu;
}
struct menu_item_node *make_menu_item_node(struct menu_item_handle *handle) {
	struct menu_item_node *node = malloc(sizeof(struct menu_item_node));
	node->handle = handle;
	node->next = NULL;
	return node;
}

static napi_value add_item(napi_env env, uiMenuItem *item, struct menu_handle *menu) {
	struct menu_item_handle *handle = make_menu_item(item);

	napi_value handle_external;
	napi_status status;

	status = napi_create_external(env, handle, NULL, NULL, &handle_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	status = napi_create_reference(env, handle_external, 1, &(handle->item_ref));
	CHECK_STATUS_THROW(status, napi_create_reference);

	if (menu->items.head == NULL) {
		menu->items.head = make_menu_item_node(handle);
		menu->items.tail = menu->items.head;
	} else {
		struct menu_item_node *node = make_menu_item_node(handle);
		menu->items.tail->next = node;
		menu->items.tail = node;
	}

	return handle_external;
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(1);
	ARG_STRING(name, 0);

	struct menu_handle *menu = make_menu(name);
	free(name);

	napi_value handle_external;
	napi_status status;

	status = napi_create_external(env, menu, NULL, NULL, &handle_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	status = napi_create_reference(env, handle_external, 1, &(menu->menu_ref));
	CHECK_STATUS_THROW(status, napi_create_reference);

	return handle_external;
}

LIBUI_FUNCTION(appendItem) { // (std::string name)
	INIT_ARGS(2);
	ARG_POINTER(struct menu_handle, handle, 0);
	ARG_STRING(caption, 1);
	napi_value item = add_item(env, uiMenuAppendItem(handle->menu, caption), handle);
	free(caption);
	return item;
}

LIBUI_FUNCTION(appendCheckItem) { // (std::string name)
	INIT_ARGS(2);
	ARG_POINTER(struct menu_handle, handle, 0);
	ARG_STRING(caption, 1);
	napi_value item = add_item(env, uiMenuAppendCheckItem(handle->menu, caption), handle);
	free(caption);
	return item;
}

LIBUI_FUNCTION(appendQuitItem) {
	INIT_ARGS(1);
	ARG_POINTER(struct menu_handle, handle, 0);
	return add_item(env, uiMenuAppendQuitItem(handle->menu), handle);
}

LIBUI_FUNCTION(appendAboutItem) {
	INIT_ARGS(1);
	ARG_POINTER(struct menu_handle, handle, 0);
	return add_item(env, uiMenuAppendAboutItem(handle->menu), handle);
}

LIBUI_FUNCTION(appendSeparator) {
	INIT_ARGS(1);
	ARG_POINTER(struct menu_handle, handle, 0);
	uiMenuAppendSeparator(handle->menu);
	return add_item(env, NULL, handle);
}

LIBUI_FUNCTION(appendPreferencesItem) {
	INIT_ARGS(1);
	ARG_POINTER(struct menu_handle, handle, 0);
	return add_item(env, uiMenuAppendPreferencesItem(handle->menu), handle);
}

LIBUI_FUNCTION(enableItem) {
	INIT_ARGS(1);
	ARG_POINTER(struct menu_item_handle, item_handle, 0);
	uiMenuItemEnable(item_handle->item);
	return NULL;
}

LIBUI_FUNCTION(disableItem) {
	INIT_ARGS(1);
	ARG_POINTER(struct menu_item_handle, item_handle, 0);
	uiMenuItemDisable(item_handle->item);
	return NULL;
}

LIBUI_FUNCTION(getItemChecked) {
	INIT_ARGS(1);
	ARG_POINTER(struct menu_item_handle, item_handle, 0);
	return make_bool(env, uiMenuItemChecked(item_handle->item));
}

LIBUI_FUNCTION(setItemChecked) {
	INIT_ARGS(2);
	ARG_POINTER(struct menu_item_handle, item_handle, 0);
	ARG_BOOL(value, 1);
	uiMenuItemSetChecked(item_handle->item, value);
	return NULL;
}

static void menu_event_cb(uiMenuItem *menu_item, uiWindow *window, void *data) {
	struct event_t *event = (struct event_t *)data;
	fire_event(event);
}

LIBUI_FUNCTION(onItemClicked) {
	INIT_ARGS(2);
	ARG_POINTER(struct menu_item_handle, item_handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onItemClicked");
	if (event == NULL) {
		return NULL;
	}
	item_handle->event = event;

	uiMenuItemOnClicked(item_handle->item, menu_event_cb, event);
	return NULL;
}

napi_value _libui_init_menu(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(appendItem);
	LIBUI_EXPORT(appendCheckItem);
	LIBUI_EXPORT(appendQuitItem);
	LIBUI_EXPORT(appendPreferencesItem);
	LIBUI_EXPORT(appendAboutItem);
	LIBUI_EXPORT(appendSeparator);

	LIBUI_EXPORT(enableItem);
	LIBUI_EXPORT(disableItem);
	LIBUI_EXPORT(onItemClicked);
	LIBUI_EXPORT(getItemChecked);
	LIBUI_EXPORT(setItemChecked);

	return module;
}
