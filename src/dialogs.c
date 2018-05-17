#include "ui.h"
#include "napi_utils.h"
#include "app.h"

static const char *MODULE = "Dialogs";

LIBUI_FUNCTION(openFile) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, parent, 0);

	char *char_ptr = uiOpenFile(uiWindow(parent->control));
	napi_value result = make_utf8_string(env, char_ptr);
	uiFreeText(char_ptr);
	return result;
}

LIBUI_FUNCTION(saveFile) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, parent, 0);

	char *char_ptr = uiSaveFile(uiWindow(parent->control));
	napi_value result = make_utf8_string(env, char_ptr);
	uiFreeText(char_ptr);
	return result;
}

LIBUI_FUNCTION(msgBox) {
	INIT_ARGS(3);
	ARG_POINTER(struct control_handle, parent, 0);
	ARG_STRING(title, 1);
	ARG_STRING(description, 2);

	uiMsgBox(uiWindow(parent->control), title, description);
	free(title);
	free(description);
	return NULL;
}

LIBUI_FUNCTION(msgBoxError) {
	INIT_ARGS(3);
	ARG_POINTER(struct control_handle, parent, 0);
	ARG_STRING(title, 1);
	ARG_STRING(description, 2);

	uiMsgBoxError(uiWindow(parent->control), title, description);
	free(title);
	free(description);
	return NULL;
}

napi_value _libui_init_dialogs(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(openFile);
	LIBUI_EXPORT(saveFile);
	LIBUI_EXPORT(msgBox);
	LIBUI_EXPORT(msgBoxError);
	return module;
}
