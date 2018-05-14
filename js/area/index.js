const {UiArea, AreaMouseEvent, AreaKeyEvent} = require('./area');
const {AreaDrawParams, AreaDrawContext} = require('./context');
const {DrawBrush, BrushGradientStop, UiDrawPath, DrawStrokeParams} = require('./draw');

const UiDrawMatrix = require('./matrix');

class Point {
	constructor(x, y) {
		this.x = x;
		this.y = y;
	}
}

class Color {
	constructor(r, g, b, a) {
		this.r = r;
		this.g = g;
		this.b = b;
		this.a = a;
	}
}

class Size {
	constructor(w, h) {
		this.width = w;
		this.height = h;
	}
}

module.exports = {
	UiArea,
	AreaMouseEvent,
	AreaKeyEvent,
	AreaDrawParams,
	AreaDrawContext,
	DrawBrush,
	BrushGradientStop,
	UiDrawPath,
	DrawStrokeParams,
	UiDrawMatrix,
	Point,
	Color,
	Size
};
