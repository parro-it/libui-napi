const libui = require('../..');

const win = new libui.UiWindow('UiDatePicker example', 320, 60, true);
win.margined = true;

const control = new libui.UiDatePicker();
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
