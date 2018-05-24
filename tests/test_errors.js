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
	runAsync(t, startLoop, () => {
		console.log('CALL METHOD ON DESTROYED CONTROL: STARTED');
		const entry = new UiMultilineEntry();
		const win = new UiWindow(null, 42, 42, true);
		win.setChild(entry);
		win.show();
		win.close();
		t.throws(() => {
			entry.append('ciao');
		}, /Method called on destroyed control./);
		return stopLoop();
	});
});

test('call method on destroyed window', t => {
	runAsync(t, startLoop, () => {
		console.log('CALL METHOD ON DESTROYED WINDOW: STARTED');
		const win = new UiWindow(null, 42, 42, true);
		win.show();
		win.close();
		t.throws(() => win.setTitle('ciao'), /Method called on destroyed control./);
		return stopLoop();
	});
});

test('call window close before show', t => runAsync(t, startLoop, () => {
										  const win = new UiWindow(null, 42, 42, true);
										  t.throws(() => win.close(),
												   /Close called on closed window./);
										  return stopLoop();
									  }));

test('call window close more then once', t => runAsync(t, startLoop, () => {
											 const win = new UiWindow(null, 42, 42, true);
											 win.show();
											 win.close();
											 t.throws(() => win.close(),
													  /Close called on closed window./);
											 return stopLoop();
										 }));

test('call window show more then once', t => runAsync(t, startLoop, () => {
											const win = new UiWindow(null, 42, 42, true);
											win.show();
											t.throws(() => win.show(),
													 /Show called on showed window./);
											return stopLoop();
										}));

test('call method without loop', t => {
	const entry = new UiMultilineEntry();
	entry.setText('');
	t.pass();
	t.end();
});

test('call method after stopLoop',
	 t => runAsync(t, startLoop,
				   () => {
					   entry = new UiMultilineEntry();
					   const win = new UiWindow(null, 42, 42, true);
					   win.setChild(entry);
					   win.show();
					   return stopLoop().then(() => entry);
				   },
				   entry => {
					   t.throws(() => entry.append('ciao'),
								/Method called on destroyed control./);
				   }));

test('Add control to more then one container', t => {
	const entry = new UiMultilineEntry();
	const win = new UiWindow(null, 42, 42, true);
	const win2 = new UiWindow(null, 42, 42, true);
	win.setChild(entry);
	t.throws(() => win2.setChild(entry), /Child control already has parent./);
	t.end();
});

test('uncaught errors', t => {
	let resolver;

	const catchErr = (err) => {
		console.log('equal ', err)

		t.equal(err.message, 'babau');
		process.off('uncaughtException', catchErr);
		console.log('uncaughtException removed')
		t.end();
		stopLoop();
		console.log('resolver called')
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
			console.log(fn.name);
			const result = fn(value);
			console.log({result, value})
			if (result && typeof result.then === 'function') {
				return result.then(doStep);
			}
			console.log('return ', result)
			return result;
		}
		return value;
	};
	console.log('start', {})
	const result = doStep();
	console.log('last', {result})
	if (result && typeof result.then === 'function') {
		console.log('promise is pending');
		return result.then(() => t.end()).catch(err => t.fail(err))
	};
	return t.end();
}