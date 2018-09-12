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
	}
}

module.exports = {UiTable};
