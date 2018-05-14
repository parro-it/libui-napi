const jsdoc2md = require('jsdoc-to-markdown')
const fs = require('fs')
const path = require('path')

function render(input, output) {
	const d = jsdoc2md.renderSync({files: input})
	fs.writeFileSync(output, d)
}

render('js/{area.js,ui-control.js}', 'docs/area.md');
render('js/{button.js,ui-control.js}', 'docs/button.md');
render('js/{checkbox.js,ui-control.js}', 'docs/checkbox.md');
render('js/{color-button.js,ui-control.js}', 'docs/color-button.md');
render('js/{combobox.js,ui-control.js}', 'docs/combobox.md');
render('js/{date-picker.js,date-time-picker-base.js,ui-control.js}',
	   'docs/date-picker.md');
render('js/{date-time-picker.js,date-time-picker-base.js,ui-control.js}',
	   'docs/date-time-picker.md');
render('js/{editable-combobox.js,ui-control.js}', 'docs/editable-combobox.md');
render('js/{entry.js,entry-base.js,ui-control.js}', 'docs/entry.md');
render('js/{form.js,ui-control.js}', 'docs/form.md');
render('js/{grid.js,ui-control.js}', 'docs/grid.md');
render('js/{group.js,ui-control.js}', 'docs/group.md');
render('js/{horizontal-box.js,box.js,ui-control.js}', 'docs/horizontal-box.md');
render('js/{horizontal-separator.js,ui-control.js}', 'docs/horizontal-separator.md');
render('js/{label.js,ui-control.js}', 'docs/label.md');
render('js/{menu.js,ui-control.js}', 'docs/menu.md');
render('js/{multiline-entry.js,ui-control.js}', 'docs/multiline-entry.md');
render('js/{password-entry.js,entry-base.js,ui-control.js}', 'docs/password-entry.md');
render('js/{progress-bar.js,ui-control.js}', 'docs/progress-bar.md');
render('js/{radio-buttons.js,ui-control.js}', 'docs/radio-buttons.md');
render('js/{search-entry.js,entry-base.js,ui-control.js}', 'docs/search-entry.md');
render('js/{slider.js,ui-control.js}', 'docs/slider.md');
render('js/{spinbox.js,ui-control.js}', 'docs/spinbox.md');
render('js/{tab.js,ui-control.js}', 'docs/tab.md');
render('js/{time-picker.js,date-time-picker-base.js,ui-control.js}',
	   'docs/time-picker.md');
render('js/{vertical-box.js,box.js,ui-control.js}', 'docs/vertical-box.md');
render('js/{vertical-separator.js,ui-control.js}', 'docs/vertical-separator.md');
render('js/{window.js,ui-control.js}', 'docs/window.md');
