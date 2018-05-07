const {DateTimePickers} = require('..');
const {DateTimePickerBase} = require('./date-time-picker-base');

/**
 * A widgets to edit times.
 * @extends DateTimePickerBase
 */
class UiTimePicker extends DateTimePickerBase {
	/**
	 * Create a new UiTimePicker object.
	 * @return {UiTimePicker}
	 */
	constructor() {
		super(DateTimePickers.createTimePicker());
	}
}

module.exports = {UiTimePicker};
