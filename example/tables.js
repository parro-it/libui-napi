const libui = require('..');
const wd = require('@raydeck/walk-dependencies');

const dependencies = [];
const addTo = (path, {name, version, author}) => {
	dependencies.push({name, version, author: author.name || author});
};
wd(process.cwd(), false, addTo);


const win = new libui.UiWindow('Tables example', 800, 600, true);
win.margined = true;
const {ValueTypes} = libui.UiTableModel;


const always = val => () => val;
const noop = () => undefined;

function objectsTableModel(model) {
	const numColumns = Object.keys(model).length;
	const columnTypes = [];
	const cellGetters = [];
	const cellSetters = [];

	for (const [key, column] of Object.entries(model)) {
		const idx = columnTypes.length;
		
		if (column.type === String) {
			columnTypes[idx] = ValueTypes.String;
			cellGetters[idx] = (data, row) => {
				debugger
				return data[row][key]
			};
			cellSetters[idx] = (data, row, value) => {
				debugger
				data[row][key] = value
			};
			column.adder = tb => tb.appendTextColumn(column.header, idx, idx + 1, null);

		} else if (column.type === 'Image') {
			columnTypes[idx] = ValueTypes.Image;
			debugger
			if (column.value instanceof libui.UiImage) {
				cellGetters[idx] = () => {
					debugger
					return column.value;
				};
			} else if (typeof column.value === 'function') {
				cellGetters[idx] = column.value;
			} else {
				cellGetters[idx] = (data, row) => data[row][key];
			}
			column.adder = tb => tb.appendImageColumn(column.header, idx);

			cellSetters[idx] = noop;
		} 
		
		if (typeof column.editable === 'function') {
			columnTypes[idx + 1] = ValueTypes.Int;
			cellGetters[idx + 1] = (data, row) => column.editable(data[row]);
			
		} else {
			columnTypes[idx + 1] = ValueTypes.Int;
			cellGetters[idx + 1] = always(Number(Boolean(column.editable)));
		}
		cellSetters[idx + 1] = noop;
		
		if (column.header === undefined) {
			column.header = key;
		}


	}

	return {
		fields: model,
		addColumns(tb, ...columnNames) {
			for (const columnName of columnNames) {
				debugger
				this.fields[columnName].adder(tb);
			}
		},
		bind(data) {
			return new libui.UiTableModel({
				numColumns: () => numColumns,
				columnType: column => columnTypes[column],
				numRows: () => data.length,
				cellValue: (row, column) => {
					console.log({row, column})
					const value = cellGetters[column](data, row)
					console.log(value)
					return value;
				},
				setCellValue: (row, column, value) => cellSetters[column](data, row, value)
			});
		}
	};
	
}

const model = objectsTableModel({
	name: {
		type: String,
		editable: true,
		header: 'Name'
	},
	surname: {
		type: String
	},
	picture: {
		type: 'Image',
		value: () => {
			debugger
			return img
		}
	}
});
const data = [{
	name: 'Andrea',
	surname: 'Parodi'
}, {
	name: 'Giorgio',
	surname: 'Parodi'
}];


const tb = new libui.UiTable(model.bind(data));
model.addColumns(tb, 'name', 'surname', 'picture');
/*
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
*/
const vbox = new libui.UiVerticalBox();
vbox.append(tb, true);
win.setChild(vbox);

win.onClosing(() => {
	win.close();
	libui.stopLoop();
});

let img = null;
async function run() {
	img = await libui.UiImage.loadFromPng(__dirname + '/lightning-orb.png');
	win.show();	
	libui.startLoop();
}


run().catch(err => console.error(err));

