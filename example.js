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
	windowOnContentSizeChanged
} = require('.');

init();
onShouldQuit(() => {
	stop();
});
const win = windowNew("Test Window", 800, 600, false);

windowOnContentSizeChanged(win, () => {
	console.log("windowOnContentSizeChanged");
});

windowOnClosing(win, () => {
	if (windowGetTitle(win) == "Test Window") {
		return windowSetTitle(win, "Riprova");
	}
	console.log('closing', windowGetTitle(win));
	windowClose(win);
	stop();
});

windowShow(win, 42)
start();

