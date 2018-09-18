const libui = require('..');

const win = new libui.UiWindow('Tables example', 320, 60, true);
win.margined = true;
const tb = new libui.UiTable(new libui.UiTableModel({
	numColumns() {
		return 2;
	},
	columnType(column) {
		if (column == 2) return 2;
		if (column == 3) return 3;
		return 0;
	},
	numRows() {
		return 50;
	},
	cellValue(row, column) {
		if (column == 2 || column == 3) return 0;
		const s = "val-" + row + '-' + column
		return s;
	},
	setCellValue(row, column, value) {
	}
}));

tb.appendTextColumn("Nome", 0, 2, null);
tb.appendTextColumn("Cognome", 1, 2, null);
tb.appendTextColumn("Robe", 4, 2, null);

win.setChild(tb);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
