const {MultilineEntry} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A multiline text entry.
 * @extends UiControl
 */
class UiMultilineEntry extends UiControl {
	/**
	 * Create a new UiMultilineEntry object.
	 * @return {UiMultilineEntry}
	 */
	constructor() {
		super(MultilineEntry.create());
	}

	/**
	 * Set or return the the content of the multiline entry.
	 * @return {string}
	 */
	get text() {
		return MultilineEntry.getText(this.handle);
	}

	set text(value) {
		MultilineEntry.setText(this.handle, value);
	}

	/**
	 * Whether the user is allowed to change the entry's contents.
	 * @return {boolean}
	 */
	get readOnly() {
		return MultilineEntry.getReadOnly(this.handle);
	}

	set readOnly(value) {
		MultilineEntry.setReadOnly(this.handle, value);
	}

	/**
	 * Append the specified text to the entry's contents.
	 * @param  {string} text - the text to append.
	 * @return {undefined}
	 */
	append(text) {
		MultilineEntry.append(this.handle, text);
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry's contents
	 * changed.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 * @return {undefined}
	 */
	onChanged(callback) {
		MultilineEntry.onChanged(this.handle, callback);
	}
}

module.exports = {UiMultilineEntry};
