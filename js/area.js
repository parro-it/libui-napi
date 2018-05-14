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
	left: 0,
	top: 1,
	right: 2,
	bottom: 3,
	topLeft: 4,
	topRight: 5,
	bottomLeft: 6,
	bottomRight: 7
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
		if (!(brush instanceof AreaDrawBrush || brush instanceof AreaDrawBrushGradient)) {
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
		if (!(brush instanceof AreaDrawBrush || brush instanceof AreaDrawBrushGradient)) {
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

class AreaDrawBrushGradient {
	constructor(type) {
		if (!(1 <= type && type <= 2)) {
			throw new TypeError('The \'type\' parameter');
		}
		this.handle = AreaBrush.createGradient(type);
	}

	set stops(v) {
		AreaBrush.setStops(this.handle, v.map(x => x.handle));
	}

	get stops() {
		return AreaBrush.getStops(this.handle);
	}

	set start(v) {
		AreaBrush.setStart(this.handle, v.x, v.y);
	}

	get start() {
		return AreaBrush.getStart(this.handle);
	}

	set end(v) {
		AreaBrush.setEnd(this.handle, v.x, v.y);
	}

	get end() {
		return AreaBrush.getEnd(this.handle);
	}

	set outerRadius(v) {
		return AreaBrush.setOuterRadius(this.handle, v);
	}

	get outerRadius() {
		return AreaBrush.getOuterRadius(this.handle);
	}
}

AreaDrawBrushGradient.Stop = class AreaDrawBrushGradientStop {
	constructor(pos, color, g, b, a) {
		if (typeof g === 'undefined') {
			this.handle =
				AreaBrush.stop_create(pos, color.r || 0, color.g || 0, color.b || 0,
									  typeof color.a === 'undefined' ? 1 : color.a);
		} else {
			this.handle = AreaBrush.stop_create(pos, color, g, b, a);
		}
	}

	set pos(v) {
		AreaBrush.stop_setPos(this.handle, v);
	}

	get pos() {
		return AreaBrush.stop_getPos(this.handle);
	}

	set color(color) {
		AreaBrush.stop_setColor(this.handle, color.r || 0, color.g || 0, color.b || 0,
								typeof color.a === 'undefined' ? 1 : color.a);
	}

	get color() {
		return AreaBrush.stop_getColor(this.handle);
	}
}

AreaDrawBrushGradient.type = {
	linear: 1,
	radial: 2
};

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
		AreaPath.bezierTo(this.handle, c1x, c1y, c2x, c2y, endX, endY);
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

	set lineCap(v) {
		AreaStrokeParams.setLineCap(this.handle, v);
	}

	get lineCap() {
		return AreaStrokeParams.getLineCap(this.handle);
	}

	set lineJoin(v) {
		AreaStrokeParams.setLineJoin(this.handle, v);
	}

	get lineJoin() {
		return AreaStrokeParams.getLineJoin(this.handle);
	}

	set miterLimit(v) {
		AreaStrokeParams.setMiterLimit(this.handle, v);
	}

	get miterLimit() {
		return AreaStrokeParams.getMiterLimit(this.handle);
	}

	set dashes(v) {
		AreaStrokeParams.setDashes(this.handle, v);
	}

	get dashes() {
		return AreaStrokeParams.getDashes(this.handle);
	}

	set dashPhase(v) {
		AreaStrokeParams.setDashPhase(this.handle, v);
	}

	get dashPhase() {
		AreaStrokeParams.getDashPhase(this.handle);
	}
}

AreaDrawStroke.lineCap = {
	flat: 0,
	round: 1,
	square: 2
};

AreaDrawStroke.lineJoin = {
	miter: 0,
	round: 1,
	bevel: 2
};

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

	translate(x, y) {
		AreaMatrix.translate(this.handle, x, y);
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
	AreaDrawBrushGradient,
	AreaDrawPath,
	AreaDrawStroke,
	AreaDrawMatrix,
	UiArea
};
