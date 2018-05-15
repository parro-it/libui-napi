const {UiControl} = require('./ui-control');

/**
 * A base class for date/time related entries.
 * @extends UiControl
 */
class DateTimePickerBase extends UiControl {
	constructor(handle) {
		super(handle);
	}
}

module.exports = {DateTimePickerBase};
