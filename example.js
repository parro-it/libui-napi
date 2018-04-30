const {start, init, onShouldQuit, stop, newWindow, windowShow} = require('./')

init();
onShouldQuit(() => {
	stop();
});
const win = newWindow("Test Window", 800, 600, false);
windowShow(win)
start();

