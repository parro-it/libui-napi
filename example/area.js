'use strict';
const libui = require('..');

const win = new libui.UiWindow('Area window', 800, 600, false);
win.margined = 1;
win.onClosing(() => {
	libui.stopLoop();
});

const hBox = new libui.UiHorizontalBox();

const brush1 = new libui.AreaDrawBrush(1, 0, 0);
const brush2 = new libui.AreaDrawBrush(0, 1, 0);
const path = new libui.AreaDrawPath();
path.addRectangle(10, 10, 100, 100);
path.end();
const sp = new libui.AreaDrawStroke();
sp.thickness = 5;

const area = new libui.UiArea(
	(area, params) => {
		// console.log(area, params);
		params.context.fill(path, brush1);
		params.context.stroke(path, brush2, sp);
	},
	(area, mouseEvent) => {
		// console.log(area, mouseEvent);
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
