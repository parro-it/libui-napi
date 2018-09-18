#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "Table";

LIBUI_FUNCTION(create) {
	INIT_ARGS(1);
	ARG_POINTER(uiTableModel, model, 0);
	
	uiTableParams params = {model, -1};
	uiControl *ctrl = uiControl(uiNewTable(&params));

	return control_handle_new(env, ctrl, "table");
}

LIBUI_FUNCTION(appendTextColumn) {
	INIT_ARGS(5);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(name, 1);
	ARG_INT32(textModelColumn, 2);
	ARG_INT32(textEditableModelColumn, 3);
	ENSURE_NOT_DESTROYED();
	
	uiTableTextColumnOptionalParams textParams;
	uiTableTextColumnOptionalParams *textParamsP = NULL;

	napi_valuetype arg_type;                                                                   
	napi_status status = napi_typeof(env, argv[4], &arg_type);                           
	CHECK_STATUS_THROW(status, napi_typeof);

	if (arg_type == napi_number) {                                                               
		ARG_INT32(colorModelColumn, 4);
		textParams.ColorModelColumn = colorModelColumn;
		textParamsP = &textParams;
	}

	uiTableAppendTextColumn(uiTable(handle->control), name, textModelColumn, textEditableModelColumn, textParamsP);
	free(name);
	return NULL;
}

LIBUI_FUNCTION(appendImageColumn) {
	INIT_ARGS(3);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(name, 1);
	ARG_INT32(imageModelColumn, 2);
	ENSURE_NOT_DESTROYED();

	uiTableAppendImageColumn(uiTable(handle->control), name, imageModelColumn);
	free(name);
	return NULL;
}

LIBUI_FUNCTION(appendImageTextColumn) {
	INIT_ARGS(6);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(name, 1);
	ARG_INT32(imageModelColumn, 2);
	ARG_INT32(textModelColumn, 3);
	ARG_INT32(textEditableModelColumn, 4);

	ENSURE_NOT_DESTROYED();

	
	uiTableTextColumnOptionalParams textParams;
	uiTableTextColumnOptionalParams *textParamsP = NULL;

	napi_valuetype arg_type;                                                                   
	napi_status status = napi_typeof(env, argv[5], &arg_type);                           
	CHECK_STATUS_THROW(status, napi_typeof);

	if (arg_type == napi_number) {                                                               
		ARG_INT32(colorModelColumn, 5);
		textParams.ColorModelColumn = colorModelColumn;
		textParamsP = &textParams;
	}
	uiTableAppendImageTextColumn(
		uiTable(handle->control),
		name,
		imageModelColumn,
		textModelColumn,
		textEditableModelColumn,
		&textParams
	);
	free(name);
	return NULL;
}

LIBUI_FUNCTION(appendCheckboxColumn) {
	INIT_ARGS(4);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(name, 1);
	ARG_INT32(checkboxModelColumn, 2);
	ARG_INT32(checkboxEditableModelColumn, 3);

	ENSURE_NOT_DESTROYED();

	uiTableAppendCheckboxColumn(uiTable(handle->control), name, checkboxModelColumn, checkboxEditableModelColumn);
	free(name);
	return NULL;
}

LIBUI_FUNCTION(appendCheckboxTextColumn) {
	INIT_ARGS(7);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(name, 1);
	ARG_INT32(checkboxModelColumn, 2);
	ARG_INT32(checkboxEditableModelColumn, 3);
	ARG_INT32(textModelColumn, 4);
	ARG_INT32(textEditableModelColumn, 5);

	ENSURE_NOT_DESTROYED();

	
	uiTableTextColumnOptionalParams textParams;
	uiTableTextColumnOptionalParams *textParamsP = NULL;

	napi_valuetype arg_type;                                                                   
	napi_status status = napi_typeof(env, argv[6], &arg_type);                           
	CHECK_STATUS_THROW(status, napi_typeof);

	if (arg_type == napi_number) {                                                               
		ARG_INT32(colorModelColumn, 6);
		textParams.ColorModelColumn = colorModelColumn;
		textParamsP = &textParams;
	}
	
	uiTableAppendCheckboxTextColumn(
		uiTable(handle->control), 
		name, 
		checkboxModelColumn, 
		checkboxEditableModelColumn, 
		textModelColumn, 
		textEditableModelColumn,
		&textParams
	);
	free(name);
	return NULL;
}

LIBUI_FUNCTION(appendProgressBarColumn) {
	INIT_ARGS(3);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(name, 1);
	ARG_INT32(progressModelColumn, 2);

	ENSURE_NOT_DESTROYED();

	uiTableAppendProgressBarColumn(uiTable(handle->control), name, progressModelColumn);
	free(name);
	return NULL;
}

LIBUI_FUNCTION(appendButtonColumn) {
	INIT_ARGS(4);
	ARG_POINTER(struct control_handle, handle, 0);
	ARG_STRING(name, 1);
	ARG_INT32(buttonModelColumn, 2);
	ARG_INT32(buttonClickableModelColumn, 3);

	ENSURE_NOT_DESTROYED();

	uiTableAppendButtonColumn(uiTable(handle->control), name, buttonModelColumn, buttonClickableModelColumn);
	free(name);
	return NULL;
	
}

napi_value _libui_init_table(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);

	LIBUI_EXPORT(appendTextColumn);
	LIBUI_EXPORT(appendImageColumn);
	LIBUI_EXPORT(appendImageTextColumn);
	LIBUI_EXPORT(appendCheckboxColumn);
	LIBUI_EXPORT(appendCheckboxTextColumn);
	LIBUI_EXPORT(appendProgressBarColumn);
	LIBUI_EXPORT(appendButtonColumn);

	return module;
}
