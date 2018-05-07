const {EditableCombobox} = require('..');

/**
 * A drop down combo box that allow selection from list or free text entry.
 */
class UiEditableCombobox {
	/**
	 * Create a new UiEditableCombobox object.
	 * @return {UiEditableCombobox}
	 */
	constructor() {
		this.handle = EditableCombobox.create();
	}

	/**
	 * Return or set the current text.
	 * @return {string}
	 */
	get text() {
		return EditableCombobox.getText(this.handle);
	}

	set text(value) {
		EditableCombobox.setText(this.handle, String(value));
	}

	/**
	 * Append a new text item to the drop down list.
	 * @param  {string} text - the text to append.
	 * @return {undefined}
	 */
	append(text) {
		EditableCombobox.append(this.handle, text);
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the text changes.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 * @return {undefined}
	 */
	onChanged(callback) {
		EditableCombobox.onChanged(this.handle, callback);
	}
}

module.exports = {UiEditableCombobox};
