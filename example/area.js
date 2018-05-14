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
const sp = new libui.AreaDrawStroke();
sp.thickness = 5;

let i = 1;

const area = new libui.UiArea(
	(area, params) => {
		const matrix = new libui.AreaDrawMatrix();
		matrix.setIdentity();
		matrix.scale(0, 0, i, 1);

		// console.log(area, params);
		let path = new libui.AreaDrawPath();
		path.addRectangle(10, 10, 100, 100);
		path.end();
		params.context.fill(path, brushRed);
		params.context.stroke(path, brushBrown, sp);

		params.context.transform(matrix);

		path = new libui.AreaDrawPath();
		path.newFigure(150, 150);
		path.lineTo(200, 150);
		path.arcTo(200, 200, 50, -Math.PI / 2, Math.PI, false);
		path.closeFigure();
		path.end();
		params.context.stroke(path, brushBrown, sp);
	},
	(_, mouseEvent) => {
		// console.log(area, mouseEvent);
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
