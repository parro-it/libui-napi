const {Table} = require('..');
const {TableModel} = require('..');
const {UiControl} = require('./ui-control');

const noop = () => 0;

function mkTable(model) {
	const tableModel = TableModel.create(
		model.numColumns || noop,
		model.numRows || noop,
		model.columnType || noop,
		model.cellValue || noop,
		model.setCellValue || noop
	);

	return Table.create(tableModel)
}

/**
 * A data table.
 * @extends UiControl
 */
class UiTable extends UiControl {
	/**
	 * Create a new UiTable object.
	 * @param  {object} model - data model for the new table
	 * @return {UiTable}
	 */
	constructor(model) {
		super(mkTable(model));
		this.model = model;
	}

	appendTextColumn(name, textModelColumn, textEditableModelColumn) {
		return Table.appendTextColumn(name, textModelColumn, textEditableModelColumn);			
	}

	appendImageColumn(name, imageModelColumn) {
		return Table.appendImageColumn(name, imageModelColumn);			
	}

	appendImageTextColumn(name, imageModelColumn, textModelColumn, textEditableModelColumn, colorModelColumn) {
		return Table.appendImageTextColumn(name, imageModelColumn, textModelColumn, textEditableModelColumn, colorModelColumn);			
	}

	appendCheckboxColumn(name, checkboxModelColumn, checkboxEditableModelColumn) {
		return Table.appendCheckboxColumn(name, checkboxModelColumn, checkboxEditableModelColumn);			
	}

	appendCheckboxTextColumn(name, checkboxModelColumn, checkboxEditableModelColumn, textModelColumn, textEditableModelColumn, colorModelColumn) {
		return Table.appendCheckboxTextColumn(name, checkboxModelColumn, checkboxEditableModelColumn, textModelColumn, textEditableModelColumn, colorModelColumn);			
	}

	appendProgressBarColumn(name, progressModelColumn) {
		return Table.appendProgressBarColumn(name, progressModelColumn);			
	}

	appendButtonColumn(name, buttonModelColumn, buttonClickableModelColumn) {
		return Table.appendButtonColumn(name, buttonModelColumn, buttonClickableModelColumn);		
	}
}

module.exports = {UiTable};
