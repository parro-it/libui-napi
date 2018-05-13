const {Grid} = require('..');

/**
 * A container that organizes children as labeled fields.
 */
class UiGrid {
	/**
	 * Create a new UiGrid object.
	 * @return {UiGrid}
	 */
	constructor() {
		this.handle = Grid.create();
	}

	/**
	 * If true, the container inserts some space between children.
	 * @return {boolean}
	 */
	get padded() {
		return Grid.getPadded(this.handle);
	}

	set padded(value) {
		Grid.setPadded(this.handle, Boolean(value));
	}

	/**
	 * Insert a new child control before specified control.
	 * @param  {UiControl} child - the control to insert
	 * @param  {UiControl} before - the control will be inserted before this position
	 * @param  {number} at      [description]
	 * @param  {number} xspan   [description]
	 * @param  {number} yspan   [description]
	 * @param  {number} hexpand [description]
	 * @param  {number} halign  [description]
	 * @param  {number} vexpan  [description]
	 * @param  {number} valign  [description]
	 * @return {undefined}
	 */
	insertAt(child, before, at, xspan, yspan, hexpand, halign, vexpan, valign) {
		Tab.insertAt(this.handle, child.handle, before.handle, at, xspan, yspan, hexpand,
					 halign, vexpan, valign);
	}

	/**
	 * Insert a new child control.
	 * @param  {UiControl} child - the control to add as child.
	 * @param  {number} left    [description]
	 * @param  {number} top     [description]
	 * @param  {number} xspan   [description]
	 * @param  {number} yspan   [description]
	 * @param  {number} hexpand [description]
	 * @param  {number} halign  [description]
	 * @param  {number} vexpand [description]
	 * @param  {number} valign  [description]
	 * @return {undefined}
	 */
	append(child, left, top, xspan, yspan, hexpand, halign, vexpand, valign) {
		Grid.append(this.handle, child.handle, left, top, xspan, yspan, hexpand, halign,
					vexpand, valign);
	}
}

module.exports = {UiGrid};
