const {Spinbox} = require('..');

/**
 * An entry control for numerical values.
 */
class UiSpinbox {
	/**
	 * Create a new UiSpinbox object.
	 * @param  {number} min - minimum allowed value of the spinbox.
	 * @param  {number} max - maximum allowed value of the spinbox.
	 * @return {UiSpinbox}
	 */
	constructor(min, max) {
		this.handle = Spinbox.create(min, max);
	}

	/**
	 * Set or return the the content of spinbox.
	 * @return {number}
	 */
	get value() {
		return Spinbox.getValue(this.handle);
	}

	set value(value) {
		Spinbox.setValue(this.handle, Number(value));
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the spinbox value changed.
	 *
	 * @param  {Function} callback - callback to execute when the event is fired.
	 * @return {undefined}
	 */
	onChanged(callback) {
		Spinbox.onChanged(this.handle, callback);
	}
}

module.exports = {UiSpinbox};
