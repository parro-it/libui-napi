const {TableModel} = require('..');

class UiTableModel {
	/**
	 * Create a new UiTableModel object.
	 * @param  {object} modelHanlder - handler for the new table model
	 * @return {UiTable}
	 */
	constructor(modelHanlder) {
		this.model = TableModel.create(modelHanlder.numColumns, modelHanlder.numRows,
									   modelHanlder.columnType, modelHanlder.cellValue,
									   modelHanlder.setCellValue);
	}

	rowInserted(index) {
		return TableModel.rowInserted(this.model, index);
	}

	rowChanged(index) {
		return TableModel.rowChanged(this.model, index);
	}

	rowDeleted(index) {
		return TableModel.rowDeleted(this.model, index);
	}
}



module.exports = {UiTableModel};
