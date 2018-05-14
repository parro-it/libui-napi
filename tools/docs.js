const jsdoc2md = require('jsdoc-to-markdown')
const fs = require('fs')
const path = require('path')

function render(input, output) {
	const d = jsdoc2md.renderSync({files: input})
	fs.writeFileSync(output, d)
}

render('js/area/*.js', 'docs/area.md');
render('js/button.js', 'docs/button.md');
render('js/checkbox.js', 'docs/checkbox.md');
render('js/color-button.js', 'docs/color-button.md');
render('js/combobox.js', 'docs/combobox.md');
render('js/{date-picker.js,date-time-picker-base.js}', 'docs/date-picker.md');
render('js/{date-time-picker.js,date-time-picker-base.js}', 'docs/date-time-picker.md');
render('js/editable-combobox.js', 'docs/editable-combobox.md');
render('js/{entry.js,entry-base.js}', 'docs/entry.md');
render('js/form.js', 'docs/form.md');
render('js/grid.js', 'docs/grid.md');
render('js/group.js', 'docs/group.md');
render('js/{horizontal-box.js,box.js}', 'docs/horizontal-box.md');
render('js/horizontal-separator.js', 'docs/horizontal-separator.md');
render('js/label.js', 'docs/label.md');
render('js/menu.js', 'docs/menu.md');
render('js/multiline-entry.js', 'docs/multiline-entry.md');
render('js/{password-entry.js,entry-base.js}', 'docs/password-entry.md');
render('js/progress-bar.js', 'docs/progress-bar.md');
render('js/radio-buttons.js', 'docs/radio-buttons.md');
render('js/{search-entry.js,entry-base.js}', 'docs/search-entry.md');
render('js/slider.js', 'docs/slider.md');
render('js/spinbox.js', 'docs/spinbox.md');
render('js/tab.js', 'docs/tab.md');
render('js/{time-picker.js,date-time-picker-base.js}', 'docs/time-picker.md');
render('js/{vertical-box.js,box.js}', 'docs/vertical-box.md');
render('js/vertical-separator.js', 'docs/vertical-separator.md');
render('js/window.js', 'docs/window.md');
