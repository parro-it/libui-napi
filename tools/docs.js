const jsdoc2md = require('jsdoc-to-markdown')
const fs = require('fs')
const path = require('path')

function render(mainClass, input, output) {
	const data = jsdoc2md.getTemplateDataSync({files: input});
	const mainClassData =
		data.sort((i1, i2) => i1.order - i2.order)
			.filter(item => item.memberof === mainClass || item.id === mainClass)
			.map((item, idx) => ({...item, order: idx}));
	if (mainClassData.length <= 1) {
		throw new Error(`No data found for class ${mainClass} in files ${input}`);
	}
	const d = jsdoc2md.renderSync({data: mainClassData});
	fs.writeFileSync(output, d)
}

render('UiArea', 'js/{area.js,ui-control.js}', 'docs/area.md');
render('UiButton', 'js/{button.js,ui-control.js}', 'docs/button.md');

render('UiCheckbox', 'js/{checkbox.js,ui-control.js}', 'docs/checkbox.md');
render('UiColorButton', 'js/{color-button.js,ui-control.js}', 'docs/color-button.md');
render('UiCombobox', 'js/{combobox.js,ui-control.js}', 'docs/combobox.md');
render('UiDatePicker', 'js/{date-picker.js,date-time-picker-base.js,ui-control.js}',
	   'docs/date-picker.md');
render('UiDateTimePicker',
	   'js/{date-time-picker.js,date-time-picker-base.js,ui-control.js}',
	   'docs/date-time-picker.md');
render('UiEditableCombobox', 'js/{editable-combobox.js,ui-control.js}',
	   'docs/editable-combobox.md');
render('UiEntry', 'js/{entry.js,entry-base.js,ui-control.js}', 'docs/entry.md');
render('UiForm', 'js/{form.js,ui-control.js}', 'docs/form.md');
render('UiGrid', 'js/{grid.js,ui-control.js}', 'docs/grid.md');
render('UiGroup', 'js/{group.js,ui-control.js}', 'docs/group.md');
render('UiHorizontalBox', 'js/{horizontal-box.js,box.js,ui-control.js}',
	   'docs/horizontal-box.md');
render('UiHorizontalSeparator',
	   'js/{horizontal-separator.js,separator-base.js,ui-control.js}',
	   'docs/horizontal-separator.md');
render('UiLabel', 'js/{label.js,ui-control.js}', 'docs/label.md');
render('UiMenu', 'js/{menu.js,ui-control.js}', 'docs/menu.md');
render('UiMultilineEntry', 'js/{multiline-entry.js,ui-control.js}',
	   'docs/multiline-entry.md');
render('UiPasswordEntry', 'js/{password-entry.js,entry-base.js,ui-control.js}',
	   'docs/password-entry.md');
render('UiProgressBar', 'js/{progress-bar.js,ui-control.js}', 'docs/progress-bar.md');
render('UiRadioButtons', 'js/{radio-buttons.js,ui-control.js}', 'docs/radio-buttons.md');
render('UiSearchEntry', 'js/{search-entry.js,entry-base.js,ui-control.js}',
	   'docs/search-entry.md');
render('UiSlider', 'js/{slider.js,ui-control.js}', 'docs/slider.md');
render('UiSpinbox', 'js/{spinbox.js,ui-control.js}', 'docs/spinbox.md');
render('UiTab', 'js/{tab.js,ui-control.js}', 'docs/tab.md');
render('UiTimePicker', 'js/{time-picker.js,date-time-picker-base.js,ui-control.js}',
	   'docs/time-picker.md');
render('UiVerticalBox', 'js/{vertical-box.js,box.js,ui-control.js}',
	   'docs/vertical-box.md');
render('UiVerticalSeparator',
	   'js/{vertical-separator.js,separator-base.js,ui-control.js}',
	   'docs/vertical-separator.md');
render('UiWindow', 'js/{window.js,ui-control.js}', 'docs/window.md');
