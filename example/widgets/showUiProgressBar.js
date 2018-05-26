/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiProgressBar example', 320, 60, true);
win.margined = true;

const control = new libui.UiProgressBar();
control.value = 50;
win.setChild(control);

win.onClosing(() => {
	if (interval) {
		clearInterval(interval);
		interval = null;
	}
	win.close();
	libui.stopLoop();
});

win.show();

let interval = setInterval(() => {
	control.value++;
	if (control.value === 100) {
		control.value = -1;
		if (interval) {
			clearInterval(interval);
			interval = null;
		}
	}
}, 60)
libui.startLoop();
