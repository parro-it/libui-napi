const libui = require('../..');

const items = [
	'cat',
	'dog',
	'mouse'
];

const win = new libui.UiWindow('UiCombobox example', 320, 60, true);
win.margined = true;

const combo = new libui.UiCombobox();
for (const item of items) {
	combo.append(item);
}
combo.onSelected(() => {
	console.log(`The selected item: ${items[combo.selected]}`);
});

let i = 0;
const toggleBtn = new libui.UiButton('Toggle item');
toggleBtn.onClicked(() => {
	combo.selected = i++;
	if (i === items.length) {
		i = 0;
	}
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
