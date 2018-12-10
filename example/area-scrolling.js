'use strict';
const libui = require('..');

const win = new libui.UiWindow('Area window', 600, 400, false);
win.margined = true;
win.onClosing(() => {
	libui.stopLoop();
});

const hBox = new libui.UiHorizontalBox();

const brushRed = new libui.DrawBrush();
brushRed.color = new libui.Color(1, 0, 0, 1);

const area = new libui.UiArea(
	(area, params) => {
		// console.log(area, params);
		let path = new libui.UiDrawPath();
		path.addRectangle(200, 200, 100, 100);
		path.end();
		params.context.fill(path, brushRed);
	},
	(_area, mouseEvent) => {
		// console.log(_area, mouseEvent);
	},
	(area, left) => {
		// console.log('left:', left);
	},
	() => {},
	(area, keyEvent) => {
		// console.log(area, keyEvent);
		// return 's' === keyEvent.key;
	},
	1000, 1000);

hBox.append(area, true);

win.setChild(hBox);
win.show();
libui.startLoop();
