const test = require('tape');
const {UiSlider, UiWindow} = require('..');

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
