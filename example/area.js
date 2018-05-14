'use strict';
const libui = require('..');

const win = new libui.UiWindow('Area window', 800, 600, false);
win.margined = 1;
win.onClosing(() => {
	libui.stopLoop();
});

const hBox = new libui.UiHorizontalBox();

const brushRed = new libui.AreaDrawBrush(1, 0, 0);
const brushBrown = new libui.AreaDrawBrush(0.7, 0.7, 0);
const brushLinear =
	new libui.AreaDrawBrushGradient(libui.AreaDrawBrushGradient.type.linear);
brushLinear.start = {
	x: 10,
	y: 10
};
brushLinear.end = {
	x: 110,
	y: 110
};
brushLinear.stops = [
	new libui.AreaDrawBrushGradient.Stop(0, {r: 1}),
	new libui.AreaDrawBrushGradient.Stop(1, {b: 1})
];
console.log(brushLinear.stops.map(v => ({pos: v.pos, c: v.color})));

const brushRadial =
	new libui.AreaDrawBrushGradient(libui.AreaDrawBrushGradient.type.radial);
brushRadial.start = {
	x: 210,
	y: 45
};
brushRadial.end = {
	x: 210,
	y: 85
};
brushRadial.stops = [
	new libui.AreaDrawBrushGradient.Stop(0, {r: 1}),
	new libui.AreaDrawBrushGradient.Stop(1, {b: 1})
];
brushRadial.outerRadius = 50;

const sp = new libui.AreaDrawStroke();
sp.thickness = 5;
sp.miterLimit = 0;

const spDashed = new libui.AreaDrawStroke();
spDashed.thickness = 5;
spDashed.dashes = [5, 5, 10, 2];

const spCap = new libui.AreaDrawStroke();
spCap.thickness = 15;
spCap.lineCap = libui.AreaDrawStroke.lineCap.round;

let i = 1;

const area = new libui.UiArea(
	(area, params) => {
		// console.log(area, params);
		let path = new libui.AreaDrawPath();
		path.addRectangle(10, 10, 100, 100);
		path.end();
		params.context.fill(path, brushLinear);
		spDashed.dashPhase = i * 10;
		params.context.stroke(path, brushLinear, spDashed);

		path = new libui.AreaDrawPath();
		path.arcTo(210, 65, 50, 0, 2 * Math.PI, false);
		path.end();
		params.context.fill(path, brushRadial);

		const matrixScale = new libui.AreaDrawMatrix();
		matrixScale.setIdentity();
		matrixScale.scale(0, 0, i, 1);

		params.context.save();
		params.context.transform(matrixScale);

		path = new libui.AreaDrawPath();
		path.newFigure(150, 150);
		path.lineTo(200, 150);
		path.arcTo(200, 200, 50, -Math.PI / 2, Math.PI, false);
		path.closeFigure();
		path.end();
		params.context.stroke(path, brushRed, sp);

		params.context.restore();

		const matrixTranslate = new libui.AreaDrawMatrix();
		matrixTranslate.setIdentity();
		matrixTranslate.translate(260, -20);
		matrixTranslate.scale(0, 0, 0.5, 0.5);

		params.context.transform(matrixTranslate);

		path = new libui.AreaDrawPath();
		path.newFigure(100, 250);
		path.bezierTo(15, 10, 495, 5, 400, 250);
		path.end();
		params.context.stroke(path, brushBrown, spCap);
	},
	(_area, mouseEvent) => {
		// console.log(_area, mouseEvent);
		i = mouseEvent.x / 300;
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
