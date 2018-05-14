const {Area, AreaBrush, AreaContext, AreaPath, AreaStrokeParams, AreaMatrix} =
	require('..');

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

	beginWindowMove() {
		Area.beginWindowMove(this.handle);
	}

	beginWindowResize(edge) {
		Area.beginWindowResize(this.handle, edge);
	}
}

UiArea.resizeEdge = {
	left 0,
	top 1,
	right 2,
	bottom 3,
	topLeft 4,
	topRight 5,
	bottomLeft 6,
	bottomRight 7
};

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
		if (!(path instanceof AreaDrawPath)) {
			throw new TypeError('The \'path\' argument has to be an AreaDrawPath object');
		}
		if (!(brush instanceof AreaDrawBrush)) {
			throw new TypeError(
				'The \'brush\' argument has to be an AreaDrawBrush object');
		}
		if (!(stroke instanceof AreaDrawStroke)) {
			throw new TypeError(
				'The \'stroke\' argument has to be an AreaDrawStroke object');
		}
		AreaContext.stroke(this.handle, path.handle, brush.handle, stroke.handle);
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

	transform(matrix) {
		AreaContext.transform(this.handle, matrix.handle);
	}

	clip(path) {
		if (!(path instanceof AreaDrawPath)) {
			throw new TypeError('The \'path\' argument has to be a AreaDrawPath object');
		}
		AreaContext.clip(this.handle, path.handle);
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

// class AreaDrawBrushSolid extends AreaDrawBrush{
// 	constructor(r, g, b, a) {
// 		a = typeof a === 'undefined' ? 1 : a;
// 		this.handle = AreaBrush.createSolid(r, g, b, a);
// 	}
// }

// class AreaDrawBrushRadial extends AreaDrawBrush{
// 	constructor(r, g, b, a) {
// 		a = typeof a === 'undefined' ? 1 : a;
// 		this.handle = AreaBrush.createGradient(r, g, b, a);
// 	}
// }

class AreaDrawPath {
	constructor(mode) {
		mode = typeof a === 'undefined' ? 0 : mode;
		this.handle = AreaPath.create(mode);
	}

	addRectangle(x, y, width, height) {
		AreaPath.addRectangle(this.handle, x, y, width, height);
	}

	newFigure(x, y) {
		AreaPath.newFigure(this.handle, x, y);
	}

	newFigureWithArc(xCenter, yCenter, radius, startAngle, sweep, negative) {
		Areapath.newFigureWithArc(this.handle, xCenter, yCenter, radius, startAngle,
								  sweep, negative);
	}

	lineTo(x, y) {
		AreaPath.lineTo(this.handle, x, y);
	}

	arcTo(xCenter, yCenter, radius, startAngle, sweep, negative) {
		AreaPath.arcTo(this.handle, xCenter, yCenter, radius, startAngle, sweep,
					   negative);
	}

	bezierTo(c1x, c1y, c2x, c2y, endX, endY) {
		AreaPath.bezierTo(c1x, c1y, c2x, c2y, endX, endY);
	}

	closeFigure() {
		AreaPath.closeFigure(this.handle);
	}

	end() {
		AreaPath.end(this.handle);
	}
}

class AreaDrawStroke {
	constructor() {
		this.handle = AreaStrokeParams.create();
	}

	set thickness(v) {
		AreaStrokeParams.setThickness(this.handle, v);
	}

	get thickness() {
		return AreaStrokeParams.getThickness(this.handle);
	}
}

class AreaDrawMatrix {
	constructor() {
		this.handle = AreaMatrix.create();
	}

	setIdentity() {
		AreaMatrix.setIdentity(this.handle);
	}

	scale(xCenter, yCenter, x, y) {
		AreaMatrix.scale(this.handle, xCenter, yCenter, x, y);
	}

	rotate(x, y, amount) {
		AreaMatrix.scale(this.handle, x, y, amount);
	}

	skew(x, y, xAmount, yAmount) {
		AreaMatrix.skew(this.handle, x, y, xAmount, yAmount);
	}

	multiply(m) {
		AreaMatrix.multiply(this.handle, m.handle);
	}

	invertible(m) {
		return AreaMatrix.invertible(this.handle);
	}

	// returns true it it worked
	invert(m) {
		return AreaMatrix.invert(this.handle);
	}
}

module.exports = {
	AreaMouseEvent,
	AreaKeyEvent,
	AreaDrawParams,
	AreaDrawContext,
	AreaDrawBrush,
	AreaDrawPath,
	AreaDrawStroke,
	AreaDrawMatrix,
	UiArea
};
