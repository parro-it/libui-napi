const {Slider} = require('..');

/**
 * Horizontal slide to set numerical values.
 */
class UiSlider {
	/**
	 * Create a new UiSlider object.
	 * @param  {number} min - minimum allowed value of the slider.
	 * @param  {number} max - maximum allowed value of the slider.
	 * @return {UiSlider}
	 */
	constructor(min, max) {
		this.handle = Slider.create(min, max);
	}

	/**
	 * Set or return the the content of the multiline entry.
	 * @return {number}
	 */
	get value() {
		return Slider.getValue(this.handle);
	}

	set value(value) {
		Slider.setValue(this.handle, value);
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the slider value changed.
	 *
	 * @param  {Function} callback - callback to execute when the event is fired.
	 * @return {undefined}
	 */
	onChanged(callback) {
		Slider.onChanged(this.handle, callback);
	}
}

module.exports = {UiSlider};
