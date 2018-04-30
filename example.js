const {
	start,
	init,
	onShouldQuit,
	stop,
	windowNew,
	windowShow,
	windowOnClosing,
	windowClose
} = require('./');

init();
onShouldQuit(() => {
	stop();
});
const win = windowNew("Test Window", 800, 600, false);

windowOnClosing(win, () => {
	console.log('closing');
	windowClose(win);
	stop();
});

windowShow(win, 42)
start();

