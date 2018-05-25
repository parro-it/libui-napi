const test = require('tape');

const {
	startLoop,
	startTimer,
	stopLoop,
	UiHorizontalBox,
	UiMultilineEntry,
	UiSlider,
	UiVerticalBox,
	UiWindow
} = require('..');

test('control constructor argument type', t => {
	const win = new UiWindow(null, 42, 42, true);
	t.equal(win.title, 'null', 'string arg are coherced');

	t.doesNotThrow(() => new UiWindow('test', 42, 42, 1), /A boolean was expected/,
				   'boolean arg are coherced');

	t.throws(() => new UiWindow('test', '42'), /Argument width: A number was expected/,
			 'bad type for number argument');

	const slider = new UiSlider();
	t.throws(() => win.setTitle.call(slider, 'test'),
			 /Expect a UiWindow "this", got a UiSlider/,
			 'handler must be of correct control');

	const vBox = new UiVerticalBox('test', 42, 42, 1);
	t.throws(() => vBox.setPadded.call(slider, true),
			 /Expect a UiBox "this", got a UiSlider/,
			 'handler must be of correct control - inherited');

	const hBox = new UiHorizontalBox();
	vBox.setPadded.call(hBox, true);
	t.equal(hBox.padded, true,
			'handler must be of correct control - correct inheritance');

	t.throws(() => vBox.append(win, true), /Expect a UiControl "control", got a UiWindow/,
			 'handler must be of correct control - arguments');
	t.end();
});

test('Add control to more then one container', t => {
	const entry = new UiMultilineEntry();
	const win = new UiWindow(null, 42, 42, true);
	const win2 = new UiWindow(null, 42, 42, true);
	win.setChild(entry);
	t.throws(() => win2.setChild(entry), /Child control already has parent./);
	t.end();
});

test('call method on destroyed window', t => {
	runAsync(t, startLoop,
			 () => {
				 const entry = new UiMultilineEntry();
				 const win = new UiWindow(null, 42, 42, true);
				 win.setChild(entry);
				 win.show();
				 win.close();
				 t.throws(() => {
					 entry.append('ciao');
				 }, /Method called on destroyed control./, 'modify control');
				 return stopLoop();
			 },
			 startLoop,
			 () => {
				 const win = new UiWindow(null, 42, 42, true);
				 win.show();
				 win.close();
				 t.throws(() => win.setTitle('ciao'),
						  /Method called on destroyed control./, 'window title');
				 return stopLoop();
			 },
			 startLoop,
			 () => {
				 const win = new UiWindow(null, 42, 42, true);
				 t.throws(() => win.close(), /Close called on closed window./,
						  'call window close before show');
				 return stopLoop();
			 },
			 startLoop,
			 () => {
				 const win = new UiWindow(null, 42, 42, true);
				 win.show();
				 win.close();
				 t.throws(() => win.close(), /Close called on closed window./,
						  'call window close more then once');
				 return stopLoop();
			 });
});

// test('call window show more then once', t => {
// 	runAsync(t, startLoop, () => {
// 		const win = new UiWindow(null, 42, 42, true);
// 		win.show();
// 		t.throws(() => win.show(), /Show called on showed window./);
// 		return stopLoop();
// 	});
// });

test('event loop', t => {
	const entry = new UiMultilineEntry();
	entry.setText('');
	t.pass('call method without loop');

	runAsync(t, startLoop,
			 () => {
				 const entry = new UiMultilineEntry();
				 const win = new UiWindow(null, 42, 42, true);
				 win.setChild(entry);
				 win.show();
				 return stopLoop().then(() => entry);
			 },
			 entry => {
				 t.throws(() => entry.append('ciao'),
						  /Method called on destroyed control./,
						  'call method after stopLoop');
			 });
});

test('uncaught errors', t => {
	let resolver;

	const catchErr = (err) => {
		t.equal(err.message, 'babau');
		process.removeListener('uncaughtException', catchErr);
		t.end();
		stopLoop();
	};

	process.on('uncaughtException', catchErr);

	startLoop().then(() => {
		startTimer(10, () => {
			throw new Error('babau');
		});
	});
});

function runAsync(t, ...thens) {
	const fns = [...thens];
	const doStep = value => {
		const fn = fns.shift();
		if (fn) {
			const result = fn(value);
			if (result && typeof result.then === 'function') {
				return result.then(doStep);
			}
			return result;
		}
		return value;
	};
	const result = doStep();
	if (result && typeof result.then === 'function') {
		return result.then(() => t.end()).catch(err => t.fail(err));
	}
	return t.end();
}
