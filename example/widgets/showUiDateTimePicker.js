/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiDateTimePicker example', 320, 60, true);
win.margined = true;

const control = new libui.UiDateTimePicker();
win.setChild(control);

control.onChanged(() => {
	console.log(control.time.toLocaleString());
});

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
