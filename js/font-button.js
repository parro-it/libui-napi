const {FontButton} = require('..');
const {FontDescriptor} = require('./font-descriptor');

/**
 * A button that opens a popup to choose a font.
 */
class UiFontButton {
	/**
	 * Create a new UiFontButton object.
	 * @return {UiFontButton}
	 */
	constructor() {
		this.handle = FontButton.create();
	}

	/**
	 * return the FontButton font value.
	 * @return {FontDescriptor}
	 */
	get font() {
		return new FontDescriptor(FontButton.getFont(this.handle));
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the user
	 * changed the selected font.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 * @return {undefined}
	 */
	onChanged(callback) {
		FontButton.onChanged(this.handle, callback);
	}
}

module.exports = {UiFontButton};
