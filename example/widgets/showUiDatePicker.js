const libui = require('../..');

const win = new libui.UiWindow('UiDatePicker example', 320, 60, true);
win.margined = true;

const widget = new libui.UiDatePicker();
win.setChild(widget);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
