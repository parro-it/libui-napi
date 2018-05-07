const {Form} = require('..');

/**
 * A container that organizes children as labeled fields.
 */
class UiForm {
	/**
	 * Create a new UiForm object.
	 * @return {UiForm}
	 */
	constructor() {
		this.handle = Form.create();
	}

	/**
	 * If true, the container inserts some space between children.
	 * @return {boolean}
	 */
	get padded() {
		return Form.getPadded(this.handle);
	}

	set padded(value) {
		Form.setPadded(this.handle, Boolean(value));
	}

	/**
	 * Append a new child control as the last field with the specified label.
	 * @param  {string} label - the text to use as label of the field.
	 * @param  {UiControl} control - the control to add as child.
	 * @param  {boolean} stretchy - whether the control should fill all the
	 * available space.
	 * @return {undefined}
	 */
	append(label, control, stretchy) {

		Form.append(this.handle, label, control.handle, Boolean(stretchy));
	}

	/**
	 * Remove a child control at the specified position.
	 * @param  {number} index - the index of the control to remove
	 * @return {undefined}
	 */
	deleteAt(index) {
		Form.deleteAt(this.handle, index);
	}
}

module.exports = {UiForm};
