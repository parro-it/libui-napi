const {DateTimePickers} = require('..');
const {DateTimePickerBase} = require('./date-time-picker-base');

/**
 * A widgets to edit dates and times.
 * @extends DateTimePickerBase
 */
class UiDateTimePicker extends DateTimePickerBase {
	/**
	 * Create a new UiDateTimePicker object.
	 * @return {UiDateTimePicker}
	 */
	constructor() {
		super(DateTimePickers.createDateTimePicker());
	}
}

module.exports = {UiDateTimePicker};
