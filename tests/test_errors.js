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

test('string arg are coherced', t => {
	const w = new UiWindow(null, 42, 42, true);
	t.equal(w.title, 'null');
	t.end();
});

test('bad type for number argument', t => {
	t.throws(() => new UiWindow('test', '42'), /Argument width: A number was expected/);
	t.end();
});

test('boolean arg are coherced', t => {
	new UiWindow('test', 42, 42, 1);
	t.pass();
	t.end();
});

test('handler must be of correct control', t => {
	const win = new UiWindow('test', 42, 42, 1);
	const slider = new UiSlider();
	t.throws(() => win.setTitle.call(slider, 'test'),
			 /Expect a UiWindow "this", got a UiSlider/);
	t.end();
});

test('handler must be of correct control - inherited', t => {
	const win = new UiVerticalBox('test', 42, 42, 1);
	const slider = new UiSlider();
	t.throws(() => win.setPadded.call(slider, true),
			 /Expect a UiBox "this", got a UiSlider/);
	t.end();
});

test('handler must be of correct control - correct inheritance', t => {
	const vBox = new UiVerticalBox('test', 42, 42, 1);
	const hBox = new UiHorizontalBox();
	vBox.setPadded.call(hBox, true);
	t.equal(hBox.padded, true);
	t.end();
});

test('handler must be of correct control - arguments', t => {
	const box = new UiVerticalBox('test', 42, 42, 1);
	const win = new UiWindow(null, 42, 42, true);
	t.throws(() => box.append(win, true), /Expect a UiControl "control", got a UiWindow/);
	t.end();
});

test('call method on destroyed control', t => {
	console.log('CALL METHOD ON DESTROYED CONTROL');
	startLoop()
		.then(() => {
			console.log('CALL METHOD ON DESTROYED CONTROL: STARTED');
			const entry = new UiMultilineEntry();
			const win = new UiWindow(null, 42, 42, true);
			win.setChild(entry);
			win.show();
			win.close();
			t.throws(() => {
				entry.append('ciao');
			}, /Method called on destroyed control./);
			console.log('STOPSTOP')
			return stopLoop();
		})
		.then(() => {
			console.log('TEST ENDED');
			t.end();
			console.log('TEST ENDED DONE');
		})
		.catch(err => t.fail(err));
});

test('call method on destroyed window', t => {
	console.log('CALL METHOD ON DESTROYED WINDOW');
	startLoop()
		.then(() => {
			console.log('CALL METHOD ON DESTROYED WINDOW: STARTED');
			const win = new UiWindow(null, 42, 42, true);
			win.show();
			win.close();
			t.throws(() => win.setTitle('ciao'), /Method called on destroyed control./);
			return stopLoop();
		})
		.then(() => {
			console.log('TEST ENDED');
			t.end();
			console.log('TEST ENDED DONE');
		})
		.catch(err => t.fail(err));
});
/*
test('call window close before show', t => {
	startLoop();
	const win = new UiWindow(null, 42, 42, true);
	t.throws(() => win.close(), /Close called on closed window./);
	stopLoop();
	setTimeout(() => t.end(), 100);
});

test('call window close more then once', t => {
	startLoop();
	const win = new UiWindow(null, 42, 42, true);
	win.show();
	win.close();
	t.throws(() => win.close(), /Close called on closed window./);
	stopLoop();
	setTimeout(() => t.end(), 100);
});

test('call window show more then once', t => {
	startLoop();
	const win = new UiWindow(null, 42, 42, true);
	win.show();
	t.throws(() => win.show(), /Show called on showed window./);
	stopLoop();
	setTimeout(() => t.end(), 100);
});

test('call method without loop', t => {
	const entry = new UiMultilineEntry();
	entry.setText('');
	t.pass();
	t.end();
});

test('call method after stopLoop', t => {
	const entry = new UiMultilineEntry();
	const win = new UiWindow(null, 42, 42, true);
	win.setChild(entry);
	win.show();
	startLoop();
	stopLoop();
	t.throws(() => entry.append('ciao'), /Method called on destroyed control./);
	setTimeout(() => t.end(), 100);
});

test('Add control to more then one container', t => {
	const entry = new UiMultilineEntry();
	const win = new UiWindow(null, 42, 42, true);
	const win2 = new UiWindow(null, 42, 42, true);
	win.setChild(entry);
	t.throws(() => win2.setChild(entry), /Child control already has parent./);
	t.end();
});

test.skip('uncaught errors', t => {
	let done = false;
	const catchErr = (err) => {
		t.equal(err.message, 'babau');
		t.end();
		process.removeListener('uncaughtException', catchErr);
		done = true;
	};
	process.on('uncaughtException', catchErr);
	startTimer(10, () => {
		if (done) {
			setTimeout(() => stopLoop());

			return false;
		}
		throw new Error('babau');
	});
	startLoop();
});
*/