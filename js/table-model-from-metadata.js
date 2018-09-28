const {UiImage} = require('./image');
const {UiTableModel} = require('./table-model');

const always = val => () => val;
const noop = () => undefined;

const ValueTypes = {
	String: 0,
	Image: 1,
	Int: 2,
	Color: 3
};

function fromMetadata(model) {
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
			if (column.value instanceof UiImage) {
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
			return new UiTableModel({
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

fromMetadata.ValueTypes = ValueTypes;
module.exports = fromMetadata;