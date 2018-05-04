const {MultilineEntry} = require('..');

/**
 * A multiline text entry.
 */
class UiMultilineEntry {
	constructor(handle) {
		this.handle = MultilineEntry.create();
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
	 * Whether the user is allowed to change the entry text.
	 * @return {boolean}
	 */
	getReadOnly() {
		return MultilineEntry.getReadOnly(this.handle);
	}

	setReadOnly(value) {
		MultilineEntry.setReadOnly(this.handle, value);
	}

	/**
	 * Append specified text to the entry content.
	 * @param  {string} text - the text to append.
	 * @return {undefined}
	 */
	append(text) {
		Box.append(this.handle, text);
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry content changed.
	 *
	 * @param  {Function} callback - callback to execute when the event is fired.
	 * @return {undefined}
	 */
	onChanged(callback) {
		Window.onChanged(this.handle, callback);
	}
}

module.exports = {UiMultilineEntry};
