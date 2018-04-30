const {start, init, onShouldQuit, stop} = require('./')

init();
onShouldQuit(() => {
	stop();
});
start();
