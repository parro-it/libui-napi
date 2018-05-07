const {DateTimePickers} = require('..');
const {DateTimePickerBase} = require('./date-time-picker-base');

/**
 * A widgets to edit dates.
 * @extends DateTimePickerBase
 */
class UiDatePicker extends DateTimePickerBase {
	/**
	 * Create a new UiDatePicker object.
	 * @return {UiDatePicker}
	 */
	constructor() {
		super(DateTimePickers.createDatePicker());
	}
}

module.exports = {UiDatePicker};
