const {
	start,
	init,
	onShouldQuit,
	stop,
	windowNew,
	windowShow,
	windowOnClosing,
	windowClose,
	windowGetTitle,
	windowSetTitle,
	windowOnContentSizeChanged,
	windowGetContentSize,
	multilineEntryNew,
	windowSetChild
} = require('.');

init();
onShouldQuit(() => {
	stop();
});

function createWindow() {
	const win = windowNew("Test Window", 800, 600, false);
	windowSetChild(win, multilineEntryNew());

	windowOnContentSizeChanged(win, () => {
		const size = windowGetContentSize(win);
		console.log(`size changed to ${size.width}x${size.height}`);
	});

	windowOnClosing(win, () => {
		if (windowGetTitle(win) == "Test Window") {
			return windowSetTitle(win, "Riprova");
		}
		console.log('closing', windowGetTitle(win));
		windowClose(win);
		stop();
	});

	return win;
}

const win = createWindow();
global.gc();
windowShow(win);
start();

