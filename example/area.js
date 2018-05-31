'use strict';
const libui = require('..');

const win = new libui.UiWindow('Area window', 600, 400, false);
win.margined = 1;
win.onClosing(() => {
	libui.stopLoop();
});

const vBox = new libui.UiVerticalBox();

function transformHelper(params, change, f) {
	const matrix = new libui.UiDrawMatrix();
	matrix.setIdentity();
	change(matrix);

	params.context.save();
	params.context.transform(matrix);

	f();

	params.context.restore();
}

const brushRed = new libui.DrawBrush();
brushRed.color = new libui.Color(1, 0, 0, 1);
const brushBrown = new libui.DrawBrush();
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
let down = 0;

const area = new libui.UiArea(
	(area, params) => {
		// console.log(area, params);
		let path = new libui.UiDrawPath();
		path.addRectangle(10, 10, 100, 100);
		path.end();
		params.context.fill(path, brushLinear);
		spDashed.dashPhase = x * 10;
		params.context.stroke(path, brushBrown, spDashed);

		//

		path = new libui.UiDrawPath();
		path.newFigure(0, 0);
		path.arcTo(210, 65, 50, 0, 2 * Math.PI, false);
		path.end();
		params.context.fill(path, brushRadial);

		transformHelper(params,
						matrix => {
							matrix.scale(0, 0, 0.5, 0.5);
							matrix.translate(0, 350);
						},
						() => {
							const path = new libui.UiDrawPath(libui.fillMode.alternate);
							path.newFigure(230, 230);
							path.lineTo(5, 230);
							path.lineTo(5, 5);
							path.lineTo(230, 5);
							path.lineTo(230, 230);
							path.closeFigure();

							path.newFigure(200, 200);
							path.lineTo(42, 200);
							path.lineTo(42, 42);
							path.lineTo(200, 42);
							path.lineTo(200, 200);
							path.closeFigure();

							path.end();
							params.getContext().fill(path, brushRed);
							params.getContext().stroke(path, brushBrown, sp);
						})

		transformHelper(params,
						matrix => {
							matrix.scale(0, 0, x, y);
						},
						() => {
							const path = new libui.UiDrawPath();
							path.newFigure(150, 150);
							path.lineTo(200, 150);
							path.arcTo(200, 200, 50, -Math.PI / (down + 1), Math.PI,
									   false);
							path.closeFigure();
							path.end();
							params.context.stroke(path, brushRed, sp);
						});

		transformHelper(params,
						matrix => {
							matrix.translate(260, -20);
							matrix.scale(0, 0, 0.5, 0.5);
						},
						() => {
							const path = new libui.UiDrawPath();
							path.newFigure(100, 250);
							path.bezierTo(15, 10, 495, 5, 400, 250);
							path.end();
							params.context.stroke(path, brushBrown, spCap);
						});
	},
	(area, mouseEvent) => {
		// console.log(area, mouseEvent);
		x = 0.2 + 1.5 * (mouseEvent.x / mouseEvent.areaWidth);
		y = 0.2 + 1.2 * (mouseEvent.y / mouseEvent.areaHeight);
		if (mouseEvent.down) {
			down = mouseEvent.down;
		} else if (mouseEvent.up) {
			down = 0;
		}
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

vBox.append(new libui.UiLabel('Try clicking (left & right mouse button)!'), false);
vBox.append(area, true);

win.setChild(vBox);
win.show();
libui.startLoop();
