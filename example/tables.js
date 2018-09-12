const libui = require('..');

const win = new libui.UiWindow('Tables example', 320, 60, true);
win.margined = true;

const tb = new libui.UiTable({
	numColumns() {
		return 2;
	},
	columnType(column) {
		if (column == 2) return 2;
		if (column == 3) return 3;
		return 0;
	},
	numRows() {
		return 5;
	},
	cellValue(row, column) {
		if (column >= 2) return 0;
		const s = "val-" + row + '-' + column
		return s;
	}

});
win.setChild(tb);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
