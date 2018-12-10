#include "modules.h"

static napi_value init_all(napi_env env, napi_value exports) {
	_libui_init_core(env, exports);
	_libui_init_window(env, exports);
	_libui_init_multilineEntry(env, exports);
	_libui_init_event_loop(env, exports);
	_libui_init_box(env, exports);
	_libui_init_slider(env, exports);
	_libui_init_label(env, exports);
	_libui_init_form(env, exports);
	_libui_init_button(env, exports);
	_libui_init_checkbox(env, exports);
	_libui_init_colorbutton(env, exports);
	_libui_init_combobox(env, exports);
	_libui_init_datetimepicker(env, exports);
	_libui_init_editablecombobox(env, exports);
	_libui_init_entry(env, exports);
	_libui_init_group(env, exports);
	_libui_init_progressbar(env, exports);
	_libui_init_radiobuttons(env, exports);
	_libui_init_separator(env, exports);
	_libui_init_spinbox(env, exports);
	_libui_init_tab(env, exports);
	_libui_init_menu(env, exports);
	_libui_init_area(env, exports);
	_libui_init_fontbutton(env, exports);
	_libui_init_font_descriptor(env, exports);
	_libui_init_font_attribute(env, exports);
	_libui_init_font_opentype(env, exports);
	_libui_init_font_string(env, exports);
	_libui_init_area(env, exports);
	_libui_init_area_brush(env, exports);
	_libui_init_area_context(env, exports);
	_libui_init_area_path(env, exports);
	_libui_init_area_textlayout(env, exports);
	_libui_init_ui_control(env, exports);
	_libui_init_area_stroke(env, exports);
	_libui_init_area_matrix(env, exports);
	_libui_init_grid(env, exports);
	_libui_init_dialogs(env, exports);
	_libui_init_table_model(env, exports);
	_libui_init_table(env, exports);
	_libui_init_image(env, exports);

	_libui_init_tests(env, exports);

	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init_all)
