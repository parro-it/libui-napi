const libui = require('../..');

const items = ['cat', 'dog', 'mouse'];

const win = new libui.UiWindow('UiEditableCombobox example', 320, 60, true);
win.margined = true;

const combo = new libui.UiEditableCombobox();
for (const item of items) {
	combo.append(item);
}
combo.onChanged(() => {
	console.log(`The text has changed to: ${combo.text}`);
});

let i = 0;
const toggleBtn = new libui.UiButton('Set text');
toggleBtn.onClicked(() => {
	combo.text = i++;
});

const box = new libui.UiVerticalBox();
box.padded = true;
box.append(combo);
box.append(toggleBtn);
win.setChild(box);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
