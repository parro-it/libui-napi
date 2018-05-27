const {RadioButtons} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A control that represents a group of single-choise options.
 * @extends UiControl
 */
class UiRadioButtons extends UiControl {
	/**
	 * Create a new UiRadioButtons object.
	 * @return {UiRadioButtons}
	 */
	constructor() {
		super(RadioButtons.create());
		this.itemsCount = 0;
	}

	/**
	 * Return or set the currently selected item by index.
	 * @return {string}
	 */
	get selected() {
		this._ensureType(UiRadioButtons);
		return RadioButtons.getSelected(this.handle);
	}

	set selected(value) {
		this._ensureType(UiRadioButtons);
		if (value < 0 || value > this.itemsCount - 1) {
			return;
		}
		RadioButtons.setSelected(this.handle, Number(value));
	}

	/**
	 * Append a new radio option as the last item with the specified text.
	 * @param  {string} text - the text to append.
	 */
	append(text) {
		this._ensureType(UiRadioButtons);
		this.itemsCount++;
		RadioButtons.append(this.handle, String(text));
	}

	/**
	 * Add a listener to the `selected` event. Emitted whenever the selected
	 * option changes.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onSelected(callback) {
		this._ensureType(UiRadioButtons);
		RadioButtons.onSelected(this.handle, callback);
	}
}

module.exports = {UiRadioButtons};
