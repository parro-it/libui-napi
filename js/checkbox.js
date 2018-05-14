const {Checkbox} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A checkbox control.
 * @extends UiControl
 */
class UiCheckbox extends UiControl {
	/**
	 * Create a new UiCheckbox object.
	 * @return {UiCheckbox}
	 */
	constructor(label = '') {
		super(Checkbox.create(label));
	}

	/**
	 * Set or return the text label for the checkbox.
	 * @return {string}
	 */
	get text() {
		return Checkbox.getText(this.handle);
	}

	set text(value) {
		Checkbox.setText(this.handle, value);
	}

	/**
	 * Whether the control is checked.
	 * @return {boolean}
	 */
	get checked() {
		return Checkbox.getChecked(this.handle);
	}

	set checked(value) {
		Checkbox.setChecked(this.handle, value);
	}

	/**
	 * Add a listener to the `toggled` event. Emitted whenever the control
	 * `checked` state change.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 * @return {undefined}
	 */
	onToggled(callback) {
		Checkbox.onToggled(this.handle, callback);
	}
}

module.exports = {UiCheckbox};
