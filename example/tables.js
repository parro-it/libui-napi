const libui = require('..');

const win = new libui.UiWindow('Tables example', 320, 60, true);
win.margined = true;

const tb = new libui.UiTable({
	numColumns() {
		return 2;
	}
});
win.setChild(tb);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
