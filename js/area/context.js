const {AreaContext} = require('../..');
const {UiDrawPath, DrawBrush, DrawStrokeParams} = require('./draw');
const UiDrawMatrix = require('./matrix');

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
	 * @param {UiDrawPath} path - the path to draw
	 * @param {DrawBrush} brush - the brush to draw with
	 * @param {DrawStrokeParams} stroke - the stroke params to draw with
	 * @return {undefined}
	 */
	stroke(path, brush, stroke) {
		if (!(path instanceof UiDrawPath)) {
			throw new TypeError('The \'path\' argument has to be an UiDrawPath object');
		}
		if (!(brush instanceof DrawBrush)) {
			throw new TypeError('The \'brush\' argument has to be an DrawBrush object');
		}
		if (!(stroke instanceof DrawStrokeParams)) {
			throw new TypeError(
				'The \'stroke\' argument has to be an DrawStrokeParams object');
		}
		AreaContext.stroke(this.handle, path.handle, brush.handle, stroke.handle);
	}

	/**
	 * Draw a path (filled).
	 * @param {UiDrawPath} path - the path to draw
	 * @param {DrawBrush} brush - the brush to draw with
	 * @return {undefined}
	 */
	fill(path, brush) {
		if (!(path instanceof UiDrawPath)) {
			throw new TypeError('The \'path\' argument has to be a UiDrawPath object');
		}
		if (!(brush instanceof DrawBrush)) {
			throw new TypeError('The \'brush\' argument has to be a DrawBrush object');
		}
		AreaContext.fill(this.handle, path.handle, brush.handle);
	}

	/**
	 * Apply a matrix transformation
	 * @param {UiDrawMatrix} matrix - the matrix to apply
	 * @return {undefined}
	 */
	transform(matrix) {
		if (!(matrix instanceof UiDrawMatrix)) {
			throw new TypeError('The \'path\' argument has to be a UiDrawPath object');
		}
		AreaContext.transform(this.handle, matrix.handle);
	}

	/**
	 * TODO
	 * @param {UiDrawPath} path -
	 * @return {undefined}
	 */
	clip(path) {
		if (!(path instanceof UiDrawPath)) {
			throw new TypeError('The \'path\' argument has to be a UiDrawPath object');
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

module.exports = {
	AreaDrawParams,
	AreaDrawContext
};
