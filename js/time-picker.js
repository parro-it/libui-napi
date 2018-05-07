const {DateTimePickers} = require('..');
const {DateTimePickerBase} = require('./date-time-picker-base');

/**
 * A widgets to set a time of day.
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
