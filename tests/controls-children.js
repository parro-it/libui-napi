const test = require('tape');
const {ControlChildren, UiWindow, UiEntry} = require('..');

const {getChildNodeAt, controlFromChildNode, nextChildNode} = ControlChildren;

test('defines functions', t => {
	t.is(typeof ControlChildren, 'object');
	t.is(typeof getChildNodeAt, 'function');
	t.is(typeof controlFromChildNode, 'function');
	t.is(typeof nextChildNode, 'function');
	t.end();
});

test('nextChildNode return children head', t => {
	const win = new UiWindow('', 1, 1, false);
	const txt = new UiEntry();
	win.setChild(txt);

	const headNode = getChildNodeAt(win.handle, 0);

	t.is(typeof headNode, 'object');
	t.end();
});

test('nextChildNode throw for index < 0', t => {
	const win = new UiWindow('', 1, 1, false);
	const txt = new UiEntry();
	win.setChild(txt);

	t.throws(() => getChildNodeAt(win.handle, -1),
			 /^Error: Index should be great than 0\.$/);
	t.end();
});

test('nextChildNode throw for index > than number of children', t => {
	const win = new UiWindow('', 1, 1, false);
	const txt = new UiEntry();
	win.setChild(txt);

	t.throws(() => getChildNodeAt(win.handle, 1),
			 /^Error: Index should be less than number of children\.$/);

	t.end();
});

test('nextChildNode throw for index not numeric', t => {
	const win = new UiWindow('', 1, 1, false);
	const txt = new UiEntry();
	win.setChild(txt);

	t.throws(() => getChildNodeAt(win.handle, {}),
			 /^TypeError: Argument index: A number was expected$/);

	t.end();
});

test('controlFromChildNode return original handle.', t => {
	const win = new UiWindow('', 1, 1, false);
	const txt = new UiEntry();
	win.setChild(txt);

	const node = getChildNodeAt(win.handle, 0);
	const txtHandle = controlFromChildNode(node);
	t.is(txt.handle, txtHandle);
	t.end();
});