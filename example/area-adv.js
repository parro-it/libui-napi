'use strict';
const libui = require('..');

const solidBrush = new libui.AreaDrawBrush(1, 0, 0, 1);

const dashedStroke = new libui.AreaDrawStroke();
dashedStroke.thickness = 6;
dashedStroke.dashes = [10, 5];
console.log(dashedStroke.dashes);

const linearBrush =
	new libui.AreaDrawBrushGradient(libui.AreaDrawBrushGradient.type.linear);
linearBrush.start = {
	x: 0,
	y: 0
};
linearBrush.end = {
	x: 200,
	y: 200
};
linearBrush.stops = [
	new libui.AreaDrawBrushGradient.Stop(0, {r: 1, g: 0, b: 1, a: 1}),
	new libui.AreaDrawBrushGradient.Stop(1, {r: 0, g: 1, b: 0, a: 1})
];

const radialBrush =
	new libui.AreaDrawBrushGradient(libui.AreaDrawBrushGradient.type.radial);
radialBrush.start = {
	x: 250,
	y: 300
};
radialBrush.end = {
	x: 250,
	y: 300
};
radialBrush.outerRadius = 40;
radialBrush.stops = [
	new libui.AreaDrawBrushGradient.Stop(0, {r: 0, g: 0, b: 1, a: 1}),
	new libui.AreaDrawBrushGradient.Stop(1, {r: 0.5, g: 0.5, b: 1, a: 1})
];
console.log(radialBrush.stops);

const matrix = new libui.AreaDrawMatrix();
matrix.setIdentity();
matrix.rotate(70, 280, (Math.PI / 180) * 45)

function handlerDraw(area, p) {
	let path = new libui.AreaDrawPath();
	path.addRectangle(0, 0, 200, 200);
	path.end();
	p.context.fill(path, linearBrush);

	// ------

	path = new libui.AreaDrawPath();
	path.newFigure(0, 0);
	path.arcTo(250, 300, 50, 0, 2 * Math.PI, false);
	path.end();
	p.context.fill(path, radialBrush);

	path = new libui.AreaDrawPath();
	path.newFigure(250, 20);
	path.lineTo(300, 150);
	path.end();
	p.context.stroke(path, solidBrush, dashedStroke);

	path = new libui.AreaDrawPath();
	p.context.transform(matrix);
	path.addRectangle(20, 230, 100, 100);
	path.end();
	p.context.fill(path, solidBrush);
}

function noop() {}

function main() {
	const mainwin = new libui.UiWindow('libui textDrawArea Example', 400, 400, true);
	mainwin.margined = true;
	mainwin.onClosing(() => {
		mainwin.close();
		libui.stopLoop();
	});

	const textDrawArea = new libui.UiArea(handlerDraw, noop, noop, noop, noop);
	const wrapper = new libui.UiVerticalBox();
	wrapper.append(textDrawArea, true);
	mainwin.setChild(wrapper);

	mainwin.show();

	libui.startLoop();
}

main();
