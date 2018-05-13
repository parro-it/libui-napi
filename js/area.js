const {Area, AreaBrush, AreaContext, AreaPath} = require('..');

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

class AreaDrawParams {
	constructor(context, areaWidth, areaHeight, clipX, clipY, clipWidth, clipHeight) {
		this.context = context;
		this.areaWidth = areaWidth;
		this.areaHeight = areaHeight;
		this.clipX = clipX;
		this.clipY = clipY;
		this.clipWidth = clipWidth;
		this.clipHeight = clipHeight;
	}
}

class AreaDrawContext {
	constructor(handle) {
		this.handle = handle;
	}

	stroke(path, brush, stroke) {
		// AreaContext.stroke(this.handle, path, brush, stroke);
	}

	fill(path, brush) {
		if (!(path instanceof AreaDrawPath)) {
			throw new TypeError('The \'path\' argument has to be a AreaDrawPath object');
		}
		if (!(brush instanceof AreaDrawBrush)) {
			throw new TypeError(
				'The \'brush\' argument has to be a AreaDrawBrush object');
		}
		AreaContext.fill(this.handle, path.handle, brush.handle);
	}

	transform(UiDrawMatrix) {
		// uiDrawTransform(c, m->getStruct());
	}

	clip(UiDrawPath) {
		// uiDrawClip(c, path->getHandle());
	}

	save() {
		AreaContext.save(this.handle);
	}

	restore() {
		AreaContext.restore(this.handle);
	}
}

class AreaDrawBrush {
	constructor(r, g, b, a) {
		a = typeof a === 'undefined' ? 1 : a;
		this.handle = AreaBrush.createSolid(r, g, b, a);
	}
}

class AreaDrawPath {
	constructor(mode) {
		mode = typeof a === 'undefined' ? 0 : mode;
		this.handle = AreaPath.create(mode);
	}

	addRectangle(x, y, width, height) {
		AreaPath.addRectangle(this.handle, x, y, width, height);
	}

	end() {
		AreaPath.end(this.handle);
	}
}

module.exports = {
	AreaMouseEvent,
	AreaKeyEvent,
	AreaDrawParams,
	AreaDrawContext,
	AreaDrawBrush,
	AreaDrawPath,
	UiArea
};
