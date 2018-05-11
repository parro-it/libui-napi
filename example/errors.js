const libui = require('..');

const win = new libui.UiWindow('Errors example', 320, 60, true);
win.margined = true;

const msg = (err) => {
	console.log('Another click will terminate the app.');
	process.removeListener('uncaughtException', msg);
};

process.on('uncaughtException', msg);

const toolbar = new libui.UiHorizontalBox();
const setEntryBtn = new libui.UiButton('Uncaught error');
setEntryBtn.onClicked(() => {
	throw new Error('ciao');
});
toolbar.append(setEntryBtn, false);
const setSearchBtn = new libui.UiButton('No errors');
setSearchBtn.onClicked(() => {
	console.log('clicked');
});
toolbar.append(setSearchBtn, false);
const setPasswordBtn = new libui.UiButton('Set password');
setPasswordBtn.onClicked(() => {});
toolbar.append(setPasswordBtn, false);

const setSpinboxBtn = new libui.UiButton('Set number');
setSpinboxBtn.onClicked(() => {});
toolbar.append(setSpinboxBtn, false);

const toggleReadOnlyBtn = new libui.UiButton('Set ReadOnly');
toggleReadOnlyBtn.onClicked(() => {

							});
toolbar.append(toggleReadOnlyBtn, false);

const box = new libui.UiVerticalBox();
box.padded = true;
box.append(toolbar);
win.setChild(box);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
