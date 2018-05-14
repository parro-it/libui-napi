const {ControlBase} = require('..');

/**
 * A simple button.
 */
class UiControl {
	/**
	 * Create a new UiControl object.
	 * @return {UiControl}
	 */
	constructor(handle) {
		this.handle = handle;
	}

	/**
	 * Set or return whether the control is enabled.
	 * @return {boolean}
	 */
	get enabled() {
		return ControlBase.getEnabled(this.handle);
	}

	/**
	 * Set or return whether the control is visible.
	 * @return {boolean}
	 */
	get visible() {
		return ControlBase.getVisible(this.handle);
	}

	/**
	 * Set or return whether the control is a top level one.
	 * @return {boolean}
	 */
	get toplevel() {
		return ControlBase.toplevel(this.handle);
	}

	set visible(value) {
		ControlBase.setVisible(this.handle, Boolean(value));
	}

	set enabled(value) {
		ControlBase.setEnabled(this.handle, Boolean(value));
	}
}

module.exports = {UiControl};
