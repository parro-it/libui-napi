const {
	App,
	Window,
	MultilineEntry
} = require('.');

App.init();
App.onShouldQuit(() => {
	App.stop();
});

function createWindow() {
	const win = Window.create("Test Window", 800, 600, false);
	Window.setChild(win, MultilineEntry.create());

	Window.onContentSizeChanged(win, () => {
		const size = Window.getContentSize(win);
		console.log(`size changed to ${size.width}x${size.height}`);
	});

	Window.onClosing(win, () => {
		if (Window.getTitle(win) == "Test Window") {
			return Window.setTitle(win, "Riprova");
		}
		console.log('closing', Window.getTitle(win));
		Window.close(win);
		App.stop();
		global.gc();
	});

	return win;
}

const win = createWindow();
global.gc();
Window.show(win);
App.start();
global.gc();


