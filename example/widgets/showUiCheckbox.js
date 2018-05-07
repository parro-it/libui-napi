/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiCheckbox example', 320, 60, true);
win.margined = true;

const check = new libui.UiCheckbox();
check.text = 'sample text';
check.onToggled(() => {
	console.log(`The check is: ${check.checked}`);
});

const toggleBtn = new libui.UiButton('Toggle state');
toggleBtn.onClicked(() => {
	check.checked = !check.checked;
});

const box = new libui.UiVerticalBox();
box.setPadded(true);
box.append(check);
box.append(toggleBtn);
win.setChild(box);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
