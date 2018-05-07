const {Combobox} = require('..');

/**
 * A drop down combo box that allow list selection only.
 */
class UiCombobox {
	/**
	 * Create a new UiCombobox object.
	 * @return {UiCombobox}
	 */
	constructor() {
		this.handle = Combobox.create();
	}

	/**
	 * Return or set the current selected item by index.
	 * @return {string}
	 */
	get selected() {
		return Combobox.getSelected(this.handle);
	}

	set selected(value) {
		Combobox.setSelected(this.handle, value);
	}

	/**
	 * Append a new text item to the drop down list.
	 * @param  {string} text - the item to append.
	 * @return {undefined}
	 */
	append(text) {
		Combobox.append(this.handle, text);
	}

	/**
	 * Add a listener to the `selected` event. Emitted whenever the selected
	 * item changes.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 * @return {undefined}
	 */
	onSelected(callback) {
		Combobox.onSelected(this.handle, callback);
	}
}

module.exports = {UiCombobox};
