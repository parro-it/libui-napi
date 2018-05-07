const {ProgressBar} = require('..');

/**
 * Progress bar control.
 */
class UiProgressBar {
	/**
	 * Create a new UiProgressBar object.
	 * @return {UiProgressBar}
	 */
	constructor() {
		this.handle = ProgressBar.create();
	}

	/**
	 * The current position of the progress bar. Can be set to -1 to create
	 * an indeterminate progress bar.
	 * @return {number}
	 */
	get value() {
		return this._value;
	}

	set value(value) {
		this._value = Number(value);
		ProgressBar.setValue(this.handle, this._value);
	}
}

module.exports = {UiProgressBar};
