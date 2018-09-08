#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "TableModel";

/*
// NumColumns returns the number of model columns in the
	// uiTableModel. This value must remain constant through the
	// lifetime of the uiTableModel. This method is not guaranteed
	// to be called depending on the system.
	// TODO strongly check column numbers and types on all platforms so these clauses can go away
	int (*NumColumns)(uiTableModelHandler *, uiTableModel *);
	// ColumnType returns the value type of the data stored in
	// the given model column of the uiTableModel. The returned
	// values must remain constant through the lifetime of the
	// uiTableModel. This method is not guaranteed to be called
	// depending on the system.
	uiTableValueType (*ColumnType)(uiTableModelHandler *, uiTableModel *, int);
	// NumRows returns the number or rows in the uiTableModel.
	// This value must be non-negative.
	int (*NumRows)(uiTableModelHandler *, uiTableModel *);
	// CellValue returns a uiTableValue corresponding to the model
	// cell at (row, column). The type of the returned uiTableValue
	// must match column's value type. Under some circumstances,
	// NULL may be returned; refer to the various methods that add
	// columns to uiTable for details. Once returned, the uiTable
	// that calls CellValue will free the uiTableValue returned.
	uiTableValue *(*CellValue)(uiTableModelHandler *mh, uiTableModel *m, int row, int column);
	// SetCellValue changes the model cell value at (row, column)
	// in the uiTableModel. Within this function, either do nothing
	// to keep the current cell value or save the new cell value as
	// appropriate. After SetCellValue is called, the uiTable will
	// itself reload the table cell. Under certain conditions, the
	// uiTableValue passed in can be NULL; refer to the various
	// methods that add columns to uiTable for details. Once
	// returned, the uiTable that called SetCellValue will free the
	// uiTableValue passed in.
	void (*SetCellValue)(uiTableModelHandler *, uiTableModel *, int, int, const uiTableValue *);
*/


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
