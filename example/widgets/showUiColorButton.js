const libui = require('../..');

const colors = [
	{r: 1, g: 0, b: 0, a: 1},
	{r: 0, g: 1, b: 0, a: 1},
	{r: 0, g: 0, b: 1, a: 1},
	{r: 1, g: 0, b: 0, a: 0.3},
	{r: 0, g: 1, b: 0, a: 0.3},
	{r: 0, g: 0, b: 1, a: 0.3}
];

const win = new libui.UiWindow('UiColorButton example', 320, 60, true);
win.margined = true;

const colorBtn = new libui.UiColorButton();
colorBtn.onChanged(() => {
	const c = colorBtn.color
	console.log(`The color is: ${c.r} ${c.g} ${c.b} ${c.a}`);
});

let i = 0;
const toggleBtn = new libui.UiButton('Toggle color');
toggleBtn.onClicked(() => {
	colorBtn.color = colors[i++];
	if (i === colors.length) {
		i = 0;
	}
});

const box = new libui.UiVerticalBox();
box.setPadded(true);
box.append(colorBtn);
box.append(toggleBtn);
win.setChild(box);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
