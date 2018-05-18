const test = require('tape');
const {
	UiSlider,
	UiWindow,
	UiVerticalBox,
	UiHorizontalBox,
	UiMultilineEntry,
	startLoop,
	stopLoop
} = require('..');

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
	t.pass();
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

test('call method on destroyed control', t => {
	t.plan(1);
	startLoop();
	const entry = new UiMultilineEntry();
	const win = new UiWindow(null, 42, 42, true);
	win.setChild(entry);
	win.show();
	win.close();
	t.throws(() => entry.append('ciao'), /Method called on destroyed control./);
	stopLoop();
});

test('call method on destroyed window', t => {
	t.plan(1);
	startLoop();
	const win = new UiWindow(null, 42, 42, true);
	win.show();
	win.close();
	t.throws(() => win.setTitle('ciao'), /Method called on destroyed control./);
	stopLoop();
});

test('call window close before show', t => {
	t.plan(1);
	startLoop();
	const win = new UiWindow(null, 42, 42, true);
	t.throws(() => win.close(), /Close called on closed window./);
	stopLoop();
});

test('call window close more then once', t => {
	t.plan(1);
	startLoop();
	const win = new UiWindow(null, 42, 42, true);
	win.show();
	win.close();
	t.throws(() => win.close(), /Close called on closed window./);
	stopLoop();
});

test('call window show more then once', t => {
	t.plan(1);
	startLoop();
	const win = new UiWindow(null, 42, 42, true);
	win.show();
	t.throws(() => win.show(), /Show called on showed window./);
	stopLoop();
});

test('call method without loop', t => {
	const entry = new UiMultilineEntry();
	entry.setText('');
	t.pass();
	t.end();
});

test('call method after stopLoop', t => {
	t.plan(1);
	const entry = new UiMultilineEntry();
	const win = new UiWindow(null, 42, 42, true);
	win.setChild(entry);
	win.show();
	startLoop();
	stopLoop();
	t.throws(() => entry.append('ciao'), /Method called on destroyed control./);
	t.end();
});

test('Add control to more then one container', t => {
	t.plan(1);
	const entry = new UiMultilineEntry();
	const win = new UiWindow(null, 42, 42, true);
	const win2 = new UiWindow(null, 42, 42, true);
	win.setChild(entry);
	t.throws(() => win2.setChild(entry), /Child control already has parent./);
	t.end();
});