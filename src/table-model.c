#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"

static const char *MODULE = "TableModel";

struct binding_handler {
	uiTableModelHandler handler;
	napi_ref model_ref;
	napi_env env;
	napi_async_context context;
	napi_ref jsNumColumns;
	napi_ref jsColumnType;
	napi_ref jsNumRows;
	napi_ref jsCellValue;
	napi_ref jsSetCellValue;
};

static napi_value run_handler_fn(struct binding_handler *bh, napi_ref fn_ref, int argc,
								 napi_value *argv) {
	napi_value fn;
	napi_status status = napi_get_reference_value(bh->env, fn_ref, &fn);

	napi_env env = bh->env;

	napi_value resource_object;
	status = napi_create_object(env, &resource_object);
	CHECK_STATUS_UNCAUGHT(status, napi_create_object, NULL);

	LIBUI_NODE_DEBUG("Calling model handler method");

	napi_value result;
	status = napi_make_callback(env, bh->context, resource_object, fn, argc, argv, &result);

	if (status == napi_pending_exception) {
		napi_value last_exception;
		napi_get_and_clear_last_exception(env, &last_exception);
		napi_fatal_exception(env, last_exception);
		return NULL;
	}

	CHECK_STATUS_UNCAUGHT(status, napi_make_callback, NULL);

	LIBUI_NODE_DEBUG("Method called");

	return result;
}

static int c_numColumns(uiTableModelHandler *mh, uiTableModel *m) {
	struct binding_handler *bh = (struct binding_handler *)mh;

	napi_env env = bh->env;

	napi_handle_scope handle_scope;
	napi_status status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, 0);

	napi_value result = run_handler_fn(bh, bh->jsNumColumns, 0, NULL);

	if (result == NULL) {

		return 0;
	}

	int32_t int_result;
	status = napi_get_value_int32(env, result, &int_result);
	CHECK_STATUS_UNCAUGHT(status, napi_get_value_int32, 0);

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, 0);

	return int_result;
}

static uiTableValueType c_columnType(uiTableModelHandler *mh, uiTableModel *m, int column) {
	struct binding_handler *bh = (struct binding_handler *)mh;
	napi_env env = bh->env;

	napi_handle_scope handle_scope;
	napi_status status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, 0);

	napi_value column_val;
	status = napi_create_int32(bh->env, column, &column_val);
	CHECK_STATUS_UNCAUGHT(status, napi_create_int32, 0);

	napi_value args[1] = {column_val};
	napi_value result = run_handler_fn(bh, bh->jsColumnType, 1, args);

	if (result == NULL) {
		return 0;
	}

	int32_t int_result;
	status = napi_get_value_int32(env, result, &int_result);
	CHECK_STATUS_UNCAUGHT(status, napi_get_value_int32, 0);

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, 0);

	return (uiTableValueType)int_result;
}

static int c_numRows(uiTableModelHandler *mh, uiTableModel *m) {
	struct binding_handler *bh = (struct binding_handler *)mh;
	napi_env env = bh->env;

	napi_handle_scope handle_scope;
	napi_status status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, 0);

	napi_value result = run_handler_fn(bh, bh->jsNumRows, 0, NULL);

	if (result == NULL) {
		return 0;
	}

	int32_t int_result;
	status = napi_get_value_int32(env, result, &int_result);
	CHECK_STATUS_UNCAUGHT(status, napi_get_value_int32, 0);

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, 0);

	return int_result;
}

static uiTableValue *c_cellValue(uiTableModelHandler *mh, uiTableModel *m, int row, int column) {
	struct binding_handler *bh = (struct binding_handler *)mh;
	uiTableValueType type = c_columnType(mh, m, column);

	napi_env env = bh->env;
	napi_handle_scope handle_scope;
	napi_status status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, NULL);

	napi_value column_val;
	status = napi_create_int32(bh->env, column, &column_val);
	CHECK_STATUS_UNCAUGHT(status, napi_create_int32, 0);

	napi_value row_val;
	status = napi_create_int32(bh->env, row, &row_val);
	CHECK_STATUS_UNCAUGHT(status, napi_create_int32, 0);

	napi_value args[2] = {row_val, column_val};

	napi_value result = run_handler_fn(bh, bh->jsCellValue, 2, args);

	if (result == NULL) {
		return 0;
	}
	uiTableValue *ret;

	switch (type) {
	case uiTableValueTypeString: {
		size_t string_len;
		napi_status status = napi_get_value_string_utf8(env, result, NULL, 0, &string_len);
		CHECK_STATUS_UNCAUGHT(status, napi_get_value_string_utf8, NULL);
		char *string = malloc(string_len + 1);
		status = napi_get_value_string_utf8(env, result, string, string_len + 1, &string_len);
		CHECK_STATUS_UNCAUGHT(status, napi_get_value_string_utf8, NULL);
		ret = uiNewTableValueString(string);
		free(string);
		break;
	}
	case uiTableValueTypeImage: {
		napi_value image_ext;
		napi_status status = napi_get_named_property(env, result, "_img", &image_ext);
		CHECK_STATUS_UNCAUGHT(status, napi_get_named_property, NULL);
		
		uiImage *img;
		status = napi_get_value_external(env, image_ext, (void **)&img);
		CHECK_STATUS_UNCAUGHT(status, napi_get_value_external, NULL);
		ret = uiNewTableValueImage(img);
		break;
	}
	case uiTableValueTypeInt: {
		int32_t int_result;
		napi_status status = napi_get_value_int32(env, result, &int_result);
		CHECK_STATUS_UNCAUGHT(status, napi_get_value_int32, NULL);
		ret = uiNewTableValueInt(int_result);
		break;
	}
	case uiTableValueTypeColor: {
		ret = NULL;
		break;
	}
	default: { ret = NULL; }
	}

	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, NULL);
	return ret;
}

#define HACK_uiTableValueTypeNull 424242

static void c_setCellValue(uiTableModelHandler *mh, uiTableModel *m, int row, int column,
						   const uiTableValue *value) {
	struct binding_handler *bh = (struct binding_handler *)mh;
	uiTableValueType type;
	if (value == NULL) {
		type = HACK_uiTableValueTypeNull;
	} else {
		type = uiTableValueGetType(value);
	}

	napi_env env = bh->env;
	napi_handle_scope handle_scope;
	napi_status status = napi_open_handle_scope(env, &handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_open_handle_scope, );

	napi_value column_val;
	status = napi_create_int32(bh->env, column, &column_val);
	CHECK_STATUS_UNCAUGHT(status, napi_create_int32, );

	napi_value row_val;
	status = napi_create_int32(bh->env, row, &row_val);
	CHECK_STATUS_UNCAUGHT(status, napi_create_int32, );

	napi_value ret;

	switch (type) {
	case HACK_uiTableValueTypeNull: {
		napi_status status = napi_get_null(env, &ret);
		CHECK_STATUS_UNCAUGHT(status, napi_get_null, );
		break;
	}
	case uiTableValueTypeString: {

		const char *cell_value = uiTableValueString(value);
		ret = make_utf8_string(env, cell_value);
		// free(cell_value);
		break;
	}
	case uiTableValueTypeImage: {
		ret = make_uint32(env, 0);
		break;
	}
	case uiTableValueTypeInt: {
		int32_t int_result = uiTableValueInt(value);
		ret = make_int32(env, int_result);
		break;
	}
	case uiTableValueTypeColor: {
		ret = make_uint32(env, 0);
		break;
	}
	default: { ret = make_uint32(env, 0); }
	}

	napi_value args[3] = {row_val, column_val, ret};

	run_handler_fn(bh, bh->jsSetCellValue, 3, args);
	status = napi_close_handle_scope(env, handle_scope);
	CHECK_STATUS_UNCAUGHT(status, napi_close_handle_scope, );
}

static void on_model_gc(napi_env env, void *finalize_data, void *finalize_hint) {
	uiTableModel *model = (uiTableModel *)finalize_data;
	struct binding_handler *handler = (struct binding_handler *)finalize_hint;
	/* TODO: decrease to 0 all fns references */
	/* TODO: clean up async context */
	uiFreeTableModel(model);
	free(handler);
}

LIBUI_FUNCTION(create) {
	INIT_ARGS(5);

	ARG_CB_REF(numColumns, 0);
	ARG_CB_REF(numRows, 1);
	ARG_CB_REF(columnType, 2);
	ARG_CB_REF(cellValue, 3);
	ARG_CB_REF(setCellValue, 4);

	napi_value async_resource_name;
	napi_status status =
		napi_create_string_utf8(env, "TableModel", NAPI_AUTO_LENGTH, &async_resource_name);
	CHECK_STATUS_THROW(status, napi_create_string_utf8);

	napi_async_context context;
	status = napi_async_init(env, NULL, async_resource_name, &context);
	CHECK_STATUS_THROW(status, napi_async_init);

	struct binding_handler *model_handler =
		(struct binding_handler *)malloc(sizeof(struct binding_handler));

	model_handler->jsNumColumns = numColumns;
	model_handler->jsNumRows = numRows;
	model_handler->jsColumnType = columnType;
	model_handler->jsCellValue = cellValue;
	model_handler->jsSetCellValue = setCellValue;
	model_handler->handler.NumColumns = c_numColumns;
	model_handler->handler.NumRows = c_numRows;
	model_handler->handler.ColumnType = c_columnType;
	model_handler->handler.CellValue = c_cellValue;
	model_handler->handler.SetCellValue = c_setCellValue;
	model_handler->env = env;
	model_handler->context = context;

	uiTableModel *model = uiNewTableModel((uiTableModelHandler *)model_handler);

	napi_value model_external;
	status = napi_create_external(env, model, on_model_gc, model_handler, &model_external);
	CHECK_STATUS_THROW(status, napi_create_external);

	status = napi_create_reference(env, model_external, 1, &model_handler->model_ref);
	CHECK_STATUS_THROW(status, napi_create_reference);

	return model_external;
}

LIBUI_FUNCTION(rowInserted) {
	INIT_ARGS(2);
	ARG_POINTER(uiTableModel, handle, 0);
	ARG_INT32(index, 1);
	uiTableModelRowInserted(handle, index);
	return NULL;
}

LIBUI_FUNCTION(rowChanged) {
	INIT_ARGS(2);
	ARG_POINTER(uiTableModel, handle, 0);
	ARG_INT32(index, 1);
	uiTableModelRowChanged(handle, index);
	return NULL;
}

LIBUI_FUNCTION(rowDeleted) {
	INIT_ARGS(2);
	ARG_POINTER(uiTableModel, handle, 0);
	ARG_INT32(index, 1);
	uiTableModelRowDeleted(handle, index);
	return NULL;
}

napi_value _libui_init_table_model(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);

	LIBUI_EXPORT(rowInserted);
	LIBUI_EXPORT(rowChanged);
	LIBUI_EXPORT(rowDeleted);

	return module;
}
