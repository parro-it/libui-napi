const {Area, AreaBrush, AreaContext, AreaPath, AreaStrokeParams, AreaMatrix} =
	require('..');
const {UiControl} = require('./ui-control');

/**
 * An area to draw on.
 * @extends UiControl
 */
class UiArea extends UiControl {
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
		super(Area.create(draw || (() => {}), mouse || (() => {}),
						  mouseCrossed || (() => {}), dragBroken || (() => {}),
						  keyEvent || (() => {})));
	}

	/**
	 * Force a redraw of the area (calls draw callback).
	 * @return {undefined}
	 */
	queueRedrawAll() {
		Area.queueRedrawAll(this.handle);
	}

	/**
	 * Let the mouse move the window (only callable in the draw callback)
	 * @return {undefined}
	 */
	beginWindowMove() {
		Area.beginWindowMove(this.handle);
	}

	/**
	 * Let the mouse resize the window (only callable in the draw callback)
	 * @param {number} edge - the size which is held by the mouse
	 * @return {undefined}
	 */
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

	/**
	 * Draw a path (the outline).
	 * @param {AreaDrawPath} path - the path to draw
	 * @param {AreaDrawBrush} brush - the brush to draw with
	 * @param {AreaDrawStroke} stroke - the stroke params to draw with
	 * @return {undefined}
	 */
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

	/**
	 * Draw a path (filled).
	 * @param {AreaDrawPath} path - the path to draw
	 * @param {AreaDrawBrush} brush - the brush to draw with
	 * @return {undefined}
	 */
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

	/**
	 * Apply a matrix transformation
	 * @param {AreaDrawMatrix} matrix - the matrix to apply
	 * @return {undefined}
	 */
	transform(matrix) {
		AreaContext.transform(this.handle, matrix.handle);
	}

	/**
	 * TODO
	 * @param {AreaDrawPath} path -
	 * @return {undefined}
	 */
	clip(path) {
		if (!(path instanceof AreaDrawPath)) {
			throw new TypeError('The \'path\' argument has to be a AreaDrawPath object');
		}
		AreaContext.clip(this.handle, path.handle);
	}

	/**
	 * Save a transformation state.
	 * @return {undefined}
	 */
	save() {
		AreaContext.save(this.handle);
	}

	/**
	 * Restore a transformation state.
	 * @return {undefined}
	 */
	restore() {
		AreaContext.restore(this.handle);
	}
}

/**
 * A solid draw brush
 */
class AreaDrawBrush {
	/**
	 * @param {number} r - the red component (0-1)
	 * @param {number} g - the blue component (0-1)
	 * @param {number} b - the blue component (0-1)
	 * @param {number} a - the alpha component (0-1)
	 * @return {UiArea}
	 */
	constructor(r, g, b, a) {
		a = typeof a === 'undefined' ? 1 : a;
		this.handle = AreaBrush.createSolid(r, g, b, a);
	}
}

/**
 * A gradient brush
 */
class AreaDrawBrushGradient {

	/**
	 * @param {number} type - the gradient type
	 * @return {UiArea}
	 */
	constructor(type) {
		if (!(1 <= type && type <= 2)) {
			throw new TypeError('The \'type\' parameter');
		}
		this.type = type;
		this.handle = AreaBrush.createGradient(type);
	}

	/**
	 * Set the gradient stops
	 * @param {Array<AreaDrawBrushGradient.Stop>} value - the gradients stops
	 * @return {string}
	 */
	set stops(value) {
		AreaBrush.setStops(this.handle, value.map(x => x.handle));
	}

	/**
	 * Get the gradient stops
	 * @return {Array<AreaDrawBrushGradient.Stop>}
	 */
	get stops() {
		return AreaBrush.getStops(this.handle);
	}

	/**
	 * Set the start position of the gradient
	 * (Radial gradients: the inner circle's center)
	 * @param {Object} pos - the coordinates
	 * @return {undefined}
	 */
	set start(value) {
		AreaBrush.setStart(this.handle, value.x, value.y);
	}

	/**
	 * Get the start position of the gradient
	 * (Radial gradients: the inner circle's center)
	 * @return {Object}
	 */
	get start() {
		return AreaBrush.getStart(this.handle);
	}

	/**
	 * Set the end position of the gradient
	 * (Radial gradients: the outer circle's center)
	 * @param {Object} pos - the coordinates
	 * @return {undefined}
	 */
	set end(value) {
		AreaBrush.setEnd(this.handle, value.x, value.y);
	}

	/**
	 * Get the end position of the gradient
	 * (Radial gradients: the outer circle's center)
	 * @return {Object}
	 */
	get end() {
		return AreaBrush.getEnd(this.handle);
	}

	/**
	 * Set the radius of the gradient's outer circle (radial gradients only)
	 * @param {number} r - the outer radius
	 * @return {undefined}
	 */
	set outerRadius(value) {
		if (this.type !== AreaDrawBrushGradient.type.radial) {
			throw new TypeError('Only radial gradients have a outerRadius!');
		}
		return AreaBrush.setOuterRadius(this.handle, value);
	}

	/**
	 * Get the radius of the gradient's outer circle (radial gradients only)
	 * @return {number}
	 */
	get outerRadius() {
		if (this.type !== AreaDrawBrushGradient.type.radial) {
			throw new TypeError('Only radial gradients have a outerRadius!');
		}
		return AreaBrush.getOuterRadius(this.handle);
	}
}

AreaDrawBrushGradient.type = {
	linear: 1,
	radial: 2
};

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

	set pos(value) {
		AreaBrush.stop_setPos(this.handle, value);
	}

	get pos() {
		return AreaBrush.stop_getPos(this.handle);
	}

	set color(value) {
		AreaBrush.stop_setColor(this.handle, value.r || 0, value.g || 0, value.b || 0,
								typeof value.a === 'undefined' ? 1 : value.a);
	}

	get color() {
		return AreaBrush.stop_getColor(this.handle);
	}
}

class AreaDrawPath {
	constructor(mode) {
		mode = typeof a === 'undefined' ? AreaDrawPath.fillMode.winding : mode;
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

AreaDrawPath.fillMode = {
	winding: 0,
	alternate: 1
};

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
		AreaMatrix.rotate(this.handle, x, y, amount);
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

	set(i, j, v) {
		if (i < 0 || 2 < i) {
			throw new TypeError('i has to be: 0 <= i <= 2')
		}
		if (j < 0 || 2 < j) {
			throw new TypeError('j has to be: 0 <= j <= 2')
		}
		AreaMatrix.set(this.handle, i, j, v);
	}

	get(i, j) {
		if (i < 0 || 2 < i) {
			throw new TypeError('i has to be: 0 <= i <= 2')
		}
		if (j < 0 || 2 < j) {
			throw new TypeError('j has to be: 0 <= j <= 2')
		}
		return AreaMatrix.get(this.handle, i, j);
	}

	// for matrix[0][1] (getter & setter)
	_getter(i) {
		return new Proxy({}, {
			get: (target, propertyName, receiver) => {
				return this.get(i, parseInt(propertyName));
			},
			set: (target, propertyName, value, receiver) => {
				this.set(i, Number(propertyName), value);
				return true;
			}
		});
	}

	get 0() {
		return this._getter(0);
	}

	get 1() {
		return this._getter(1);
	}

	get 2() {
		return this._getter(2);
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
