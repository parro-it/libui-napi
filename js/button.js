const {Button} = require('..');

/**
 * A simple button.
 */
class UiButton {
	/**
	 * Create a new UiButton object.
	 * @return {UiButton}
	 */
	constructor(label) {
		this.handle = Button.create(String(label));
	}

	/**
	 * Set or return the text of the button.
	 * @return {string}
	 */
	get text() {
		return Button.getText(this.handle);
	}

	set text(value) {
		Button.setText(this.handle, String(value));
	}

	/**
	 * Emitted when the button is clicked
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 * @return {undefined}
	 */
	onClicked(callback) {
		Button.onClicked(this.handle, callback);
	}
}

module.exports = {UiButton};
