const {Box} = require('..');

class UiBox {
	constructor(handle) {
		this.handle = handle;
	}

	/**
	 * If true, the container insert some space between children.
	 * @return {boolean}
	 */
	get padded() {
		return Box.getPadded(this.handle);
	}

	set padded(value) {
		Box.setPadded(this.handle, Boolean(value));
	}

	/**
	 * Append a new child control as the last one.
	 * @param  {UiControl} control - the control to add as child.
	 * @param  {boolean} stretchy - whever the control should fill all the
	 * available space.
	 * @return {undefined}
	 */
	append(control, stretchy) {
		Box.append(this.handle, control.handle, Boolean(stretchy));
	}

	/**
	 * Remove a child control at specified position.
	 * @param  {number} index - the index of the control to remove
	 * @return {undefined}
	 */
	deleteAt(index) {
		Box.deleteAt(this.handle, index);
	}
}

module.exports = {UiBox};
