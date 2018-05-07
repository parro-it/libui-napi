
const libui = require('../..');

const items = [
	'cat',
	'dog',
	'mouse'
];

const win = new libui.UiWindow('UiRadioButtons example', 320, 60, true);
win.margined = true;

const radioBtns = new libui.UiRadioButtons();
for (const item of items) {
	radioBtns.append(item);
}
radioBtns.onSelected(() => {
	console.log(`The selected item: ${items[radioBtns.selected]}`);
});

let i = 0;
const toggleBtn = new libui.UiButton('Toggle selected');
toggleBtn.onClicked(() => {
	radioBtns.selected = i++;
	if (i === items.length) {
		i = 0;
	}
});

const box = new libui.UiVerticalBox();
box.padded = true;
box.append(radioBtns);
box.append(toggleBtn);
win.setChild(box);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
