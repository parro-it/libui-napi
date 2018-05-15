const {Slider} = require('..');
const {UiControl} = require('./ui-control');

/**
 * Horizontal slider to set numerical values.
 * @extends UiControl
 */
class UiSlider extends UiControl {
	/**
	 * Create a new UiSlider object.
	 * @param  {number} min - minimum value of the slider.
	 * @param  {number} max - maximum value of the slider.
	 * @return {UiSlider}
	 */
	constructor(min, max) {
		super(Slider.create(min, max));
	}

	/**
	 * Set or return the the content of the slider.
	 * @return {number}
	 */
	get value() {
		return Slider.getValue(this.handle);
	}

	set value(value) {
		Slider.setValue(this.handle, Number(value));
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the slider value
	 * changed.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onChanged(callback) {
		Slider.onChanged(this.handle, callback);
	}
}

module.exports = {UiSlider};
