#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "TableModel";

static int numColumns (uiTableModelHandler *mh, uiTableModel *m) {
	
}
static uiTableValueType columnType (uiTableModelHandler *mh, uiTableModel *m, int column) {
	
}
static int numRows (uiTableModelHandler *mh, uiTableModel *m) {
	
}
static uiTableValue *cellValue (uiTableModelHandler *mh, uiTableModel *m, int row, int column) {
	
}
static void setCellValue (uiTableModelHandler *mh, uiTableModel *m, int row, int column, const uiTableValue *value) {
	
}


struct binding_handler {
	uiTableModelHandler handler;
	napi_ref jsNumColumns;
	napi_ref jsColumnType;
	napi_ref jsNumRows;
	napi_ref jsCellValue;
	napi_ref jsSetCellValue;
};

LIBUI_FUNCTION(create) {
	INIT_ARGS(5);

	ARG_CB_REF(numColumns, 0);
	ARG_CB_REF(numRows, 1);
	ARG_CB_REF(columnType, 2);
	ARG_CB_REF(cellValue, 3);
	ARG_CB_REF(setCellValue, 4);

	return NULL;
}
/*
LIBUI_FUNCTION(onClicked) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onClicked");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiButtonOnClicked(uiButton(handle->control), CALLBACK_OF(uiButton, control_event_cb), event);

	return NULL;
}

LIBUI_FUNCTION(setText) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	ARG_STRING(value, 1);
	uiButtonSetText(uiButton(handle->control), value);
	free(value);
	return NULL;
}

LIBUI_FUNCTION(getText) {
	INIT_ARGS(1);

	ARG_POINTER(struct control_handle, handle, 0);
	ENSURE_NOT_DESTROYED();
	char *char_ptr = uiButtonText(uiButton(handle->control));
	napi_value result = make_utf8_string(env, char_ptr);
	uiFreeText(char_ptr);
	return result;
}
*/
napi_value _libui_init_table_model(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	
	return module;
}
