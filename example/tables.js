const libui = require('..');
const wd = require('@raydeck/walk-dependencies');

const dependencies = [];
const addTo = (path, {name, version, author}) => {
	dependencies.push({name, version, author: author.name || author});
};
wd(process.cwd(), false, addTo);

// console.log(JSON.stringify(dependencies, null, 4));

const win = new libui.UiWindow('Tables example', 800, 600, true);
win.margined = true;
const {ValueTypes} = libui.UiTableModel;

console.log(ValueTypes.String)
console.log(ValueTypes.Int)
const img = new libui.UiImage(200, 216);
const buffer = Buffer.alloc(200 * 216 * 4);
img.append(buffer, 200, 216, 200 * 4);

const tb = new libui.UiTable(new libui.UiTableModel({
	numColumns() {
		return 3;
	},
	columnType(column) {
		if (column == 3 || column == 4 || column == 41 || column == 6)
			return ValueTypes.Int;
		if (column == 7)
			return ValueTypes.Image;
		return ValueTypes.String;
	},
	numRows() {
		return dependencies.length;
	},
	cellValue(row, column) {
		console.log('cellValue', (row, column))
		switch (column) {
			case 0: {
				return dependencies[row].name;
			}
			case 1: {
				return dependencies[row].version;
			}
			case 2: {
				return dependencies[row].author;
			}
			case 3: {
				return 0;
			}
			case 4: {
				return Number(!dependencies[row].version.startsWith('0'));
			}
			case 41: {
				return 1;
			}
			case 5: {
				return 'show details';
			}
			case 6: {
				return 1;
			}
			case 7: {
				return img;
			}
		}
	},
	setCellValue(row, column, value) {
		console.log(row, column, value)
		switch (column) {
			case 0: {
				dependencies[row].name = value;
				break;
			}
			case 1: {
				dependencies[row].version = value;
				break;
			}
			case 2: {
				dependencies[row].author = value;
				break;
			}
			case 4: {
				if (value) {
					dependencies[row].version = '1' + dependencies[row].version.slice(1);
				} else {
					dependencies[row].version = '0' + dependencies[row].version.slice(1);
				}
				break;
			}
			case 5: {
				libui.UiDialogs.msgBox(win, 'Row details',
									   JSON.stringify(dependencies[row], null, 4));
				break;
			}
		}
	}
}));

tb.appendTextColumn('name', 0, 3, null);
tb.appendTextColumn('version', 1, 3, null);
tb.appendTextColumn('author', 2, 41, null);
tb.appendCheckboxColumn('semver', 4, 41);
tb.appendCheckboxTextColumn('version+semver', 4, 41, 1, 3, null);
tb.appendButtonColumn('details', 5, 6);
tb.appendImageColumn('img', 7);

const vbox = new libui.UiVerticalBox();
vbox.append(tb, true);
win.setChild(vbox);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
