const {Form} = require('..');

/**
 * A container that organize children as labeled fields.
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
	 * If true, the container insert some space between children.
	 * @return {boolean}
	 */
	getPadded() {
		return Form.getPadded(this.handle);
	}

	setPadded(value) {
		Form.setPadded(this.handle, Boolean(value));
	}

	/**
	 * Append a new child control as last field with specified label.
	 * @param  {string} label - the text to use as label of the field.
	 * @param  {UiControl} control - the control to add as child.
	 * @param  {boolean} stretchy - whever the control should fill all the available space.
	 * @return {undefined}
	 */
	append(label, control, stretchy) {

		Form.append(this.handle, label, control.handle, Boolean(stretchy));
	}

	/**
	 * Remove a child control at specified position.
	 * @param  {number} index - the index of the control to remove
	 * @return {undefined}
	 */
	deleteAt(index) {
		Form.deleteAt(this.handle, index);
	}
}

module.exports = {UiForm};
