const jsdoc2md = require('jsdoc-to-markdown')
const fs = require('fs')
const path = require('path')
const map = require('p-map')
const toDotCase = require('to-dot-case');

async function render([mainClass, input]) {
	const data = await jsdoc2md.getTemplateData({files: input});
	const mainClassData =
		data.sort((i1, i2) => i1.order - i2.order)
			.filter(item => item.memberof === mainClass || item.id === mainClass)
			.map((item, idx) => ({...item, order: idx}));
	if (mainClassData.length <= 1) {
		throw new Error(`No data found for class ${mainClass} in files ${input}`);
	}

	const output = 'docs/' + toDotCase(mainClass.slice(2)).replace(/\./g, '-') + '.md';
	const d = await jsdoc2md.render({data: mainClassData});
	await fs.promises.writeFile(output, d);
	console.log(`${mainClass} -> ${output}`);
}

function renderAll(...classes) {
	map(classes, render, {concurrency: 5})
		.then(() => console.log('Documentation generation completed.'))
		.catch(err => console.error(err));
}

renderAll(
	['UiArea', 'js/{area.js,ui-control.js}'],
	['UiButton', 'js/{button.js,ui-control.js}'],
	['UiCheckbox', 'js/{checkbox.js,ui-control.js}'],
	['UiColorButton', 'js/{color-button.js,ui-control.js}'],
	['UiCombobox', 'js/{combobox.js,ui-control.js}'],
	[
		'UiDatePicker',
		'js/{date-picker.js,date-time-picker-base.js,ui-control.js}',
	],
	[
		'UiDateTimePicker',
		'js/{date-time-picker.js,date-time-picker-base.js,ui-control.js}',
	],
	[
		'UiEditableCombobox',
		'js/{editable-combobox.js,ui-control.js}',
	],
	['UiEntry', 'js/{entry.js,entry-base.js,ui-control.js}'],
	['UiForm', 'js/{form.js,ui-control.js}'], ['UiGrid', 'js/{grid.js,ui-control.js}'],
	['UiGroup', 'js/{group.js,ui-control.js}'],
	[
		'UiHorizontalBox',
		'js/{horizontal-box.js,box.js,ui-control.js}',
	],
	[
		'UiHorizontalSeparator',
		'js/{horizontal-separator.js,separator-base.js,ui-control.js}',
	],
	['UiLabel', 'js/{label.js,ui-control.js}'], ['UiMenu', 'js/{menu.js,ui-control.js}'],
	[
		'UiMultilineEntry',
		'js/{multiline-entry.js,ui-control.js}',
	],
	[
		'UiPasswordEntry',
		'js/{password-entry.js,entry-base.js,ui-control.js}',
	],
	['UiProgressBar', 'js/{progress-bar.js,ui-control.js}'],
	['UiRadioButtons', 'js/{radio-buttons.js,ui-control.js}'],
	[
		'UiSearchEntry',
		'js/{search-entry.js,entry-base.js,ui-control.js}',
	],
	['UiSlider', 'js/{slider.js,ui-control.js}'],
	['UiSpinbox', 'js/{spinbox.js,ui-control.js}'],
	['UiTab', 'js/{tab.js,ui-control.js}'],
	[
		'UiTimePicker',
		'js/{time-picker.js,date-time-picker-base.js,ui-control.js}',
	],
	[
		'UiVerticalBox',
		'js/{vertical-box.js,box.js,ui-control.js}',
	],
	[
		'UiVerticalSeparator',
		'js/{vertical-separator.js,separator-base.js,ui-control.js}',
	],
	['UiWindow', 'js/{window.js,ui-control.js}']);
