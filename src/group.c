#include "ui.h"
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Group";

LIBUI_FUNCTION(setMargined) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_BOOL(value, 1);

	uiGroupSetMargined(uiGroup(handle->control), value);
	return NULL;
}

LIBUI_FUNCTION(getMargined) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	bool value = uiGroupMargined(uiGroup(handle->control));
	return make_bool(env, value);
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(1);
	ARG_STRING(title, 0);
	uiControl *ctrl = uiControl(uiNewGroup(title));
	free(title);
	return control_handle_new(env, ctrl, "group");
}

LIBUI_FUNCTION(getTitle) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	char *char_ptr = uiGroupTitle(uiGroup(handle->control));
	napi_value result;

	napi_status status = napi_create_string_utf8(env, char_ptr, NAPI_AUTO_LENGTH, &result);
	CHECK_STATUS_THROW(status, napi_create_string_utf8);

	uiFreeText(char_ptr);
	return result;
}

LIBUI_FUNCTION(setTitle) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_STRING(title, 1);
	uiGroupSetTitle(uiGroup(handle->control), title);
	free(title);
	return NULL;
}

LIBUI_FUNCTION(setChild) {
	INIT_ARGS(2);
	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_POINTER(struct control_handle, child, 1);
	clear_children(env, handle->children);
	if (add_child(env, handle->children, child) != napi_ok) {
		return NULL;
	}
	uiGroupSetChild(uiGroup(handle->control), child->control);
	return NULL;
}

napi_value _libui_init_group(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(setChild);
	LIBUI_EXPORT(getTitle);
	LIBUI_EXPORT(setTitle);
	LIBUI_EXPORT(getMargined);
	LIBUI_EXPORT(setMargined);

	return module;
}
