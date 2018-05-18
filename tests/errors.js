const test = require('tape');
const {UiSlider, UiWindow, UiVerticalBox, UiHorizontalBox} = require('..');

test('string arg are coherced', t => {
	t.plan(1);
	const w = new UiWindow(null, 42, 42, true);
	t.equal(w.title, 'null');
});

test('bad type for number argument', t => {
	t.plan(1);
	t.throws(() => new UiWindow('test', '42'), /Argument width: A number was expected/);
});

test('boolean arg are coherced', t => {
	new UiWindow('test', 42, 42, 1);
	t.end();
});

test('handler must be of correct control', t => {
	t.plan(1);
	const win = new UiWindow('test', 42, 42, 1);
	const slider = new UiSlider();
	t.throws(() => win.setTitle.call(slider, 'test'),
			 /Expect a UiWindow "this", got a UiSlider/);
});

test('handler must be of correct control - inherited', t => {
	t.plan(1);
	const win = new UiVerticalBox('test', 42, 42, 1);
	const slider = new UiSlider();
	t.throws(() => win.setPadded.call(slider, true),
			 /Expect a UiBox "this", got a UiSlider/);
});

test('handler must be of correct control - correct inheritance', t => {
	t.plan(1);
	const vBox = new UiVerticalBox('test', 42, 42, 1);
	const hBox = new UiHorizontalBox();
	vBox.setPadded.call(hBox, true);
	t.equal(hBox.padded, true);
});

test('handler must be of correct control - arguments', t => {
	t.plan(1);
	const box = new UiVerticalBox('test', 42, 42, 1);
	const win = new UiWindow(null, 42, 42, true);
	t.throws(() => box.append(win, true), /Expect a UiControl "control", got a UiWindow/);
});