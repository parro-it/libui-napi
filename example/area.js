'use strict';
const libui = require('..');

const win = new libui.UiWindow('Area window', 800, 600, false);
win.margined = 1;
win.onClosing(() => {
	libui.stopLoop();
});

const hBox = new libui.UiHorizontalBox();

const area = new libui.UiArea(
	(area, params) => {
		console.log(area, params);
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
