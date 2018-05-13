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
		x: areaEvent.getX(),
		y: areaEvent.getY(),
		areaWidth: areaEvent.getAreaWidth(),
		areaHeight: areaEvent.getAreaHeight(),
		down: areaEvent.getDown(),
		up: areaEvent.getUp(),
		count: areaEvent.getCount(),
		modifiers: areaEvent.getModifiers(),
		held1To64: areaEvent.getHeld1To64()
	});
}

const area = new libui.UiArea(() => {console.log('draw')}, logMouse,
							  () => {console.log('crossed')}, () => {},
							  () => {console.log('key')});

hBox.append(area, true);

win.setChild(hBox);
win.show();
libui.startLoop();
