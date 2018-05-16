'use strict';
const libui = require('..');

const win = new libui.UiWindow('Area window', 600, 400, false);
win.margined = 1;
win.onClosing(() => {
	libui.stopLoop();
});

const hBox = new libui.UiHorizontalBox();

const brushRed = new libui.DrawBrush(1, 0, 0);
brushRed.color = new libui.Color(1, 0, 0, 1);
const brushBrown = new libui.DrawBrush(0.7, 0.5, 0);
brushBrown.color = new libui.Color(0.7, 0.5, 0, 1);
const brushLinear = new libui.DrawBrush();
brushLinear.type = libui.brushType.linearGradient;
brushLinear.start = {
	x: 10,
	y: 10
};
brushLinear.end = {
	x: 110,
	y: 110
};
brushLinear.stops = [
	new libui.BrushGradientStop(0, new libui.Color(1, 0, 0, 1)),
	new libui.BrushGradientStop(1, new libui.Color(0, 0, 1, 1))
];
console.log(brushLinear.stops.map(v => ({pos: v.pos, c: v.color})));

const brushRadial = new libui.DrawBrush();
brushRadial.type = libui.brushType.radialGradient;
brushRadial.start = {
	x: 210,
	y: 45
};
brushRadial.end = {
	x: 210,
	y: 85
};
brushRadial.stops =
	[new libui.BrushGradientStop(0, {r: 1}), new libui.BrushGradientStop(1, {b: 1})];
brushRadial.outerRadius = 50;

const sp = new libui.DrawStrokeParams();
sp.thickness = 5;
sp.miterLimit = 0;

const spDashed = new libui.DrawStrokeParams();
spDashed.thickness = 5;
spDashed.dashes = [5, 5, 10, 2];

const spCap = new libui.DrawStrokeParams();
spCap.thickness = 15;
spCap.cap = libui.DrawStrokeParams.lineCap.round;

let x = 1;
let y = 1;

const area = new libui.UiArea(
	(area, params) => {
		// console.log(area, params);
		let path = new libui.UiDrawPath();
		path.addRectangle(10, 10, 100, 100);
		path.end();
		params.context.fill(path, brushLinear);
		spDashed.dashPhase = x * 10;
		params.context.stroke(path, brushBrown, spDashed);

		path = new libui.UiDrawPath();
		path.arcTo(210, 65, 50, 0, 2 * Math.PI, false);
		path.end();
		params.context.fill(path, brushRadial);

		const matrixScale = new libui.UiDrawMatrix();
		matrixScale.setIdentity();
		matrixScale.scale(0, 0, x, y);

		params.context.save();
		params.context.transform(matrixScale);

		path = new libui.UiDrawPath();
		path.newFigure(150, 150);
		path.lineTo(200, 150);
		path.arcTo(200, 200, 50, -Math.PI / 2, Math.PI, false);
		path.closeFigure();
		path.end();
		params.context.stroke(path, brushRed, sp);

		params.context.restore();

		const matrixTranslate = new libui.UiDrawMatrix();
		matrixTranslate.setIdentity();
		matrixTranslate.translate(260, -20);
		matrixTranslate.scale(0, 0, 0.5, 0.5);

		params.context.transform(matrixTranslate);

		path = new libui.UiDrawPath();
		path.newFigure(100, 250);
		path.bezierTo(15, 10, 495, 5, 400, 250);
		path.end();
		params.context.stroke(path, brushBrown, spCap);
	},
	(area, mouseEvent) => {
		// console.log(area, mouseEvent);
		x = 0.2 + 1.5 * (mouseEvent.x / mouseEvent.areaWidth);
		y = 0.2 + 1.2 * (mouseEvent.y / mouseEvent.areaHeight);
		area.queueRedrawAll();
		if (mouseEvent.x > 10 && mouseEvent.x < 110 && mouseEvent.y > 10 &&
			mouseEvent.y < 110) {
			area.beginWindowMove();
		}
	},
	(area, left) => {
		// console.log('left:', left);
	},
	() => {},
	(area, keyEvent) => {
		// console.log(area, keyEvent);
		// return 's' === keyEvent.key;
	});

hBox.append(area, true);

win.setChild(hBox);
win.show();
libui.startLoop();
