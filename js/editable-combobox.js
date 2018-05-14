const {EditableCombobox} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A drop down combo box that allows to select an item from list or to specify a custom
 * value.
 * @extends UiControl
 */
class UiEditableCombobox extends UiControl {
	/**
	 * Create a new UiEditableCombobox object.
	 * @return {UiEditableCombobox}
	 */
	constructor() {
		super(EditableCombobox.create());
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
	 * @param  {string} text - the item to append.
	 * @return {undefined}
	 */
	append(text) {
		EditableCombobox.append(this.handle, text);
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the text (or item) changes.
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
