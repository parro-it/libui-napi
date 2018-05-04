const {
	App,
	Window,
	MultilineEntry
} = require('.');

App.init();
App.onShouldQuit(() => {
	App.stop();
	global.gc();
});

function createWindow() {
	let win = Window.create("Test Window", 800, 600, false);

	const entry = MultilineEntry.create();
	Window.setChild(win, entry);

	Window.onContentSizeChanged(win, () => {
		const size = Window.getContentSize(win);
		console.log(`size changed to ${size.width}x${size.height}`);
	});

	Window.onClosing(win, () => {
		if (Window.getTitle(win) == "Test Window") {
			setTimeout(() => {
				Window.setContentSize(win, 400, 300);
				global.gc();
			}, 3000);
			return Window.setTitle(win, "Riprova");
		}
		console.log('closing', Window.getTitle(win));
		Window.close(win);
		win = null;
		App.stop();
		global.gc();
	});

	Window.show(win);


}

createWindow();
App.start();
global.gc();


