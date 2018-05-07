const {App, Window, MultilineEntry, Box} = require('.');

App.init();
App.onShouldQuit(() => {
	App.stop();
	global.gc();
});

function createWindow() {
	let win = Window.create('Test Window', 800, 600, false);
	Window.setMargined(win, true);
	const logEntry = MultilineEntry.create();

	const entry = MultilineEntry.create();
	MultilineEntry.setText(entry, 'A test line\n');
	MultilineEntry.append(entry, 'A second test line\n');
	MultilineEntry.onChanged(entry, () => {
		const msg = `Text changed to ${MultilineEntry.getText(entry)}`;
		console.log(msg);
		MultilineEntry.append(logEntry, msg + '\n');
	});

	const box = Box.createHorizontal();
	Box.setPadded(box, true);
	Box.append(box, entry, true);
	Box.append(box, logEntry, true);

	Window.setChild(win, box);

	Window.onContentSizeChanged(win, () => {
		const size = Window.getContentSize(win);
		console.log(`size changed to ${size.width}x${size.height}`);
	});
	let step = 0;
	Window.onClosing(win, () => {
		if (Window.getTitle(win) == 'Test Window') {
			let interval = setInterval(() => {
				if (step === 0) {
					Window.setContentSize(win, 400, 300);
				}
				if (step === 1) {
					Window.setMargined(win, true);
				}
				if (step === 2) {
					Window.setMargined(win, false);
					Window.setFullscreen(win, true);
				}
				if (step === 3) {
					Window.setFullscreen(win, false);
					Window.setBorderless(win, true);
				}
				if (step === 4) {
					Window.setBorderless(win, false);
				}

				if (step > 4) {
					clearInterval(interval);
				}

				step++;

				console.log({
					Margined: Window.getMargined(win),
					Fullscreen: Window.getFullscreen(win),
					Borderless: Window.getBorderless(win),
				});
			}, 1000);
			Box.deleteAt(box, 1);
			return Window.setTitle(win, 'Wait some seconds please...');
		}
		console.log('closing', Window.getTitle(win));
		Window.close(win);
		win = null;
		App.stop();
	});

	Window.show(win);
}

createWindow();
App.start();
setInterval(() => {
	global.gc();
}, 10);
