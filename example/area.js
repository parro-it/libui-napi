'use strict';
const libui = require('..');

const win = new libui.UiWindow('Area window', 800, 600, false);
win.margined = 1;
win.onClosing(() => {
	libui.stopLoop();
});

const hBox = new libui.UiHorizontalBox();

function logMouse(area, areaEvent) {
	console.log(area, {
		x: areaEvent.x,
		y: areaEvent.y,
		areaWidth: areaEvent.areaWidth,
		areaHeight: areaEvent.areaHeight,
		down: areaEvent.down,
		up: areaEvent.up,
		count: areaEvent.count,
		modifiers: areaEvent.modifiers,
		held1To64: areaEvent.held1To64
	});
}

const area = new libui.UiArea(() => {console.log('draw')}, logMouse,
							  () => {console.log('crossed')}, () => {},
							  () => {console.log('key')});

hBox.append(area, true);

win.setChild(hBox);
win.show();
libui.startLoop();
