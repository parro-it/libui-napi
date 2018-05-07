const {Label} = require('..');

/**
 * A static text label.
 */
class UiLabel {
	/**
	 * Create a new UiLabel object.
	 * @param  {string} text - initial content of the label
	 * @return {UiLabel}
	 */
	constructor(text = '') {
		this.handle = Label.create(String(text));
	}

	/**
	 * Set or return the the content of the label.
	 * @return {string}
	 */
	get text() {
		return Label.getText(this.handle);
	}

	set text(value) {
		Label.setText(this.handle, String(value));
	}
}

module.exports = {UiLabel};
