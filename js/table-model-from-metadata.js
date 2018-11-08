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

const Text = {
	getter: ({key}) => (data, row) => data[row][key],
	setter: ({key}) => (data, row, value) => (data[row][key] = value),
	cellType: () => ValueTypes.String,
	adder: column => tb =>
		tb.appendTextColumn(column.header, column.idx, column.idx + 1, null)
};

const Image = {
	getter: ({value}) => {
		if (value instanceof UiImage) {
			return always(column.value);
		}

		if (typeof value === 'function') {
			return value;
		}

		return (data, row) => data[row][key];
	},
	setter: () => noop,
	cellType: () => ValueTypes.Image,
	adder: column => tb => tb.appendImageColumn(column.header, column.idx)
};

const Checkbox = {
	getter: ({key}) => (data, row) => Number(data[row][key]),
	setter: ({key}) => (data, row, value) => (data[row][key] = Boolean(value)),
	cellType: () => ValueTypes.Int,
	adder: column => tb =>
		tb.appendCheckboxColumn(column.header, column.idx, column.idx + 1)
};

const LabeledCheckbox = {
	getter: ({key}) => (data, row) => Number(data[row][key]),
	setter: ({key}) => (data, row, value) => (data[row][key] = Boolean(value)),
	cellType: () => ValueTypes.Int,
	adder: column => tb => {
		const textModelColumn = -1;
		const textEditableModelColumn = -1;

		tb.appendCheckboxTextColumn(column.header, column.idx, column.idx + 1,
									textModelColumn, textEditableModelColumn, null);
	}
};

const LabeledImage = {
	getter: ({value}) => {
		if (value instanceof UiImage) {
			return always(column.value);
		}

		if (typeof value === 'function') {
			return value;
		}

		return (data, row) => data[row][key];
	},
	setter: ({key}) => () => 0,
	cellType: () => ValueTypes.Image,
	adder: column => tb => {
		const textModelColumn = -1;
		const textEditableModelColumn = -1;

		tb.appendImageTextColumn(column.header, column.idx, column.idx + 1,
								 textModelColumn, textEditableModelColumn, null);
	}
};

const ProgressBar = {
	getter: ({key}) => (data, row) => Number(data[row][key]),
	setter: ({key}) => (data, row, value) => (data[row][key] = Number(value)),
	cellType: () => ValueTypes.Int,
	adder: column => tb => tb.appendProgressBarColumn(column.header, column.idx)
};

const Button = {
	getter: ({label}) => () => String(label),
	setter: ({key, click}) => (data, row) => click(data[row]),
	cellType: () => ValueTypes.String,
	adder: column => tb =>
		tb.appendButtonColumn(column.header, column.idx, column.idx + 1)
};

function fromMetadata(model) {
	const numColumns = Object.keys(model).length;
	const columnTypes = [];
	const cellGetters = [];
	const cellSetters = [];

	for (const [key, column] of Object.entries(model)) {
		const idx = columnTypes.length;
		column.key = key;
		column.idx = idx;

		columnTypes[idx] = column.type.cellType(column);
		cellGetters[idx] = column.type.getter(column);
		cellSetters[idx] = column.type.setter(column);
		column.adder = column.type.adder(column);

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
				debugger;
				this.fields[columnName].adder(tb);
			}
		},
		bind(data) {
			return new UiTableModel({
				numColumns: () => numColumns,
				columnType: column => columnTypes[column],
				numRows: () => data.length,
				cellValue: (row, column) => {
					console.log({row, column});
					const value = cellGetters[column](data, row);
					console.log(value);
					return value;
				},
				setCellValue: (row, column, value) =>
					cellSetters[column](data, row, value)
			});
		}
	};
}

fromMetadata.ValueTypes = ValueTypes;
fromMetadata.Fields = {
	Text,
	Image,
	Checkbox,
	ProgressBar,
	LabeledCheckbox,
	Button
};

module.exports = fromMetadata;
