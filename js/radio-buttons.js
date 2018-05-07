const {RadioButtons} = require('..');

/**
 * A widget that represent a group of radio options.
 */
class UiRadioButtons {
	/**
	 * Create a new UiRadioButtons object.
	 * @return {UiRadioButtons}
	 */
	constructor() {
		this.handle = RadioButtons.create();
	}

	/**
	 * Return or set the current selected item by index.
	 * @return {string}
	 */
	get selected() {
		return RadioButtons.getSelected(this.handle);
	}

	set selected(value) {
		RadioButtons.setSelected(this.handle, value);
	}

	/**
	 * Append a new radio option as last one with specified text.
	 * @param  {string} text - the text to append.
	 * @return {undefined}
	 */
	append(text) {
		RadioButtons.append(this.handle, text);
	}

	/**
	 * Add a listener to the `selected` event. Emitted whenever the selected
	 * option changes.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 * @return {undefined}
	 */
	onSelected(callback) {
		RadioButtons.onSelected(this.handle, callback);
	}
}

module.exports = {UiRadioButtons};
