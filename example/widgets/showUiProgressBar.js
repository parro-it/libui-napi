/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiProgressBar example', 320, 60, true);
win.margined = true;

const widget = new libui.UiProgressBar();
widget.value = 50;
win.setChild(widget);

win.onClosing(() => {
	widget.value = 0;
	win.close();
	libui.stopLoop();
});

win.show();

let interval = setInterval(() => {
	widget.value++;
	if (widget.value === 100) {
		widget.value = -1;
		clearInterval(interval)
	}
}, 30)
libui.startLoop();
