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
	uiTableAppendTextColumn(uiTable(ctrl), "Nome", 0, 2, NULL);
	uiTableAppendTextColumn(uiTable(ctrl), "Cognome", 1, 2, NULL);

	return control_handle_new(env, ctrl, "table");
}


napi_value _libui_init_table(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	return module;
}
