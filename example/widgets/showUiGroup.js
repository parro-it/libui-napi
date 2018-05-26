/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiGroup example', 320, 60, true);
win.margined = true;

const control = new libui.UiVerticalBox();
control.padded = true;
control.append(new libui.UiEntry(), false);
control.append(new libui.UiEntry(), false);
control.append(new libui.UiEntry(), false);

const group = new libui.UiGroup();
group.margined = true;
group.title = 'A group of entries';
group.setChild(control);

win.setChild(group);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
