'use strict';
const os = require('os');
const libui = require('..');

const menu = new libui.UiMenu('Libui');
const item = menu.appendItem('Click me!');
item.onClicked(() => console.log('Menu clicked'));
const chkItem = menu.appendItem('I check');
chkItem.onClicked(() => chkItem.checked = !chkItem.checked);
menu.appendSeparator();
menu.appendQuitItem();
menu.appendPreferencesItem();
menu.appendAboutItem();

const menuEdit = new libui.UiMenu('Edit');
menuEdit.appendItem('Copy');
menuEdit.appendItem('Cut');
menuEdit.appendItem('Paste');

const win = new libui.UiWindow('Test window', 800, 600, true);
win.margined = true;

const box = new libui.UiVerticalBox();
const hBox = new libui.UiHorizontalBox();
const e1 = new libui.UiEntry();
e1.enabled = false;
const lblCiao = new libui.UiLabel('ciao');
hBox.append(lblCiao, false);

hBox.append(e1, false);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

box.append(new libui.UiEntry(), false);
box.append(hBox, false);

if (os.platform() !== 'darwin') {
	box.append(new libui.UiSearchEntry(), false);
}

box.append(new libui.UiPasswordEntry(), false);

const cmb = new libui.UiCombobox();

cmb.append('item 1');
cmb.append('item 2');
cmb.append('item 3');

box.append(cmb, false);
const hBox4 = new libui.UiHorizontalBox();

const dtPick = new libui.UiDateTimePicker();
dtPick.time = new Date(2018, 2, 12, 13, 2, 0);
dtPick.onChanged(() => {
	console.log(dtPick.time.toLocaleString());
});

hBox4.append(dtPick, false);

hBox4.append(new libui.UiVerticalSeparator(), false);
hBox4.append(new libui.UiEditableCombobox(), false);
hBox4.append(new libui.UiCheckbox('Optionally'), false);

box.append(hBox4, false);

const group = new libui.UiGroup('Options');
const radios = new libui.UiRadioButtons();
radios.append('option 1');
radios.append('option 2');
radios.append('option 3');

group.setChild(radios);
box.append(group, true);

box.append(new libui.UiHorizontalSeparator(), true);

const hBox2 = new libui.UiHorizontalBox();
const spin = new libui.UiSpinbox(0, 100);
spin.value = 33;
hBox2.append(new libui.UiLabel('Number'), false);
hBox2.append(spin, true);
box.append(hBox2, false);

const hBox3 = new libui.UiHorizontalBox();
const slider = new libui.UiSlider(0, 100);
slider.value = 33;
hBox3.append(new libui.UiLabel('Number'), false);
hBox3.append(slider, false);
box.append(hBox3, false);

box.append(new libui.UiMultilineEntry(), false);

const buttons = new libui.UiHorizontalBox();

const btnOk = new libui.UiButton('Ok');
btnOk.onClicked(() => {
	dtPick.time = new Date();
});
buttons.append(btnOk, false);
buttons.append(new libui.UiButton('Maybe'), false);
buttons.append(new libui.UiButton('Cancel'), false);

box.append(new libui.UiProgressBar(), false);
const fontBtn = new libui.UiFontButton();
box.append(fontBtn, false);
const f1 = fontBtn.font;
console.log('default font', {
	family: f1.getFamily(),
	size: f1.getSize(),
	weight: f1.getWeight(),
	italic: f1.getItalic(),
	stretch: f1.getStretch()
});
fontBtn.onChanged(() => {
	const f2 = fontBtn.font;
	console.log('default font', {
		family: f2.getFamily(),
		size: f2.getSize(),
		weight: f2.getWeight(),
		italic: f2.getItalic(),
		stretch: f2.getStretch()
	});
});

box.append(buttons, false);

const tabs = new libui.UiTab();

tabs.append('controls', box);
tabs.append('text', new libui.UiMultilineEntry());

win.setChild(tabs);

win.show();
libui.startLoop();
