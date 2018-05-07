const libui = require('../..');

const items = [
	'cat',
	'dog',
	'mouse'
];

const win = new libui.UiWindow('Entries example', 320, 60, true);
win.margined = true;

const entry = new libui.UiEntry();
entry.onChanged(() => {
	console.log(`The entry text has changed to: ${entry.text}`);
});

const entryPassword = new libui.UiPasswordEntry();
entryPassword.onChanged(() => {
	console.log(`The password entry text has changed to: ${entryPassword.text}`);
});

const entrySearch = new libui.UiSearchEntry();
entrySearch.onChanged(() => {
	console.log(`The search entry text has changed to: ${entrySearch.text}`);
});

const spinbox = new libui.UiSpinbox(0, 20);
spinbox.onChanged(() => {
	console.log(`The spinbox value has changed to: ${spinbox.text}`);
});

const toolbar = new libui.UiHorizontalBox();
let i = 0;
const setEntryBtn = new libui.UiButton('Set entry');
setEntryBtn.onClicked(() => {
	entry.text = i++;
});
toolbar.append(setEntryBtn, false);
const setSearchBtn = new libui.UiButton('Set search');
setSearchBtn.onClicked(() => {
	entrySearch.text = i++;
});
toolbar.append(setSearchBtn, false);
const setPasswordBtn = new libui.UiButton('Set password');
setPasswordBtn.onClicked(() => {
	entryPassword.text = i++;
});
toolbar.append(setPasswordBtn, false);

const setSpinboxBtn = new libui.UiButton('Set number');
setSpinboxBtn.onClicked(() => {
	spinbox.value = i++;
});
toolbar.append(setSpinboxBtn, false);

const toggleReadOnlyBtn = new libui.UiButton('Set ReadOnly');
toggleReadOnlyBtn.onClicked(() => {
	entry.readOnly = !entry.readOnly;
	entrySearch.readOnly = !entrySearch.readOnly;
	entryPassword.readOnly = !entryPassword.readOnly;
});
toolbar.append(toggleReadOnlyBtn, false);

const box = new libui.UiVerticalBox();
box.padded = true;
box.append(entry);
box.append(entrySearch);
box.append(entryPassword);
box.append(new libui.UiHorizontalSeparator());
box.append(spinbox);

box.append(new libui.UiHorizontalSeparator());
box.append(toolbar);
win.setChild(box);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
