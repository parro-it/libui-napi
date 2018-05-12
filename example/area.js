'use strict';
const libui = require('..');

const win = new libui.UiWindow('Area window', 800, 600, false);
win.margined = 1;
win.onClosing(() => {
	libui.stopLoop();
});

const hBox = new libui.UiHorizontalBox();

const area = new libui.UiArea();
console.log(area);

hBox.append(area, 1);

win.setChild(hBox);
win.show();
libui.startLoop();
