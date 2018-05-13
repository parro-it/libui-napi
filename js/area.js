const {Area} = require('..');

/**
 * An area to draw on.
 */
class UiArea {
	/**
	 * Create a new UiArea object.
	 * @param {Function} draw - callback to draw onto area
	 * @param {Function} mouse - callback for mouse events
	 * @param {Function} mouseCrossed - callback for entering or leaving the area
	 * @param {Function} dragBroken - callback
	 * @param {Function} keyEvent - callback for key events
	 * @return {UiArea}
	 */
	constructor(draw, mouse, mouseCrossed, dragBroken, keyEvent) {
		this.handle = Area.create(draw || (() => {}), mouse || (() => {}),
								  mouseCrossed || (() => {}), dragBroken || (() => {}),
								  keyEvent || (() => {}));
	}

	/**
	 * Force a redraw of the area (calls draw callback).
	 * @return {undefined}
	 */
	queueRedrawAll() {
		Area.queueRedrawAll(this.handle);
	}
}

class AreaMouseEvent {
	constructor(x, y, areaWidth, areaHeight, down, up, count, modifiers, held1To64) {
		this.x = x;
		this.y = y;
		this.areaWidth = areaWidth;
		this.areaHeight = areaHeight;
		this.down = down;
		this.up = up;
		this.count = count;
		this.modifiers = modifiers;
		this.held1To64 = held1To64;
	}
}

class AreaKeyEvent {
	constructor(key, extKey, mofifierKey, modifiers, up) {
		this.key = String.fromCharCode(key);
		this.extKey = extKey;
		this.mofifierKey = mofifierKey;
		this.modifiers = modifiers;
		this.up = up;
	}
}

module.exports = {
	AreaMouseEvent,
	AreaKeyEvent,
	UiArea
};
