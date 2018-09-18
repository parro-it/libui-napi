const {Table} = require('..');
const {TableModel} = require('..');
const {UiControl} = require('./ui-control');

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
		super(Table.create(model.model));
		this.model = model.model;
	}

	appendTextColumn(name, textModelColumn, textEditableModelColumn, colorModelColumn) {
		return Table.appendTextColumn(this.handle, name, textModelColumn, textEditableModelColumn, colorModelColumn);			
	}

	appendImageColumn(name, imageModelColumn) {
		return Table.appendImageColumn(this.handle, name, imageModelColumn);			
	}

	appendImageTextColumn(name, imageModelColumn, textModelColumn, textEditableModelColumn, colorModelColumn) {
		return Table.appendImageTextColumn(this.handle, name, imageModelColumn, textModelColumn, textEditableModelColumn, colorModelColumn);			
	}

	appendCheckboxColumn(name, checkboxModelColumn, checkboxEditableModelColumn) {
		return Table.appendCheckboxColumn(this.handle, name, checkboxModelColumn, checkboxEditableModelColumn);			
	}

	appendCheckboxTextColumn(name, checkboxModelColumn, checkboxEditableModelColumn, textModelColumn, textEditableModelColumn, colorModelColumn) {
		return Table.appendCheckboxTextColumn(this.handle, name, checkboxModelColumn, checkboxEditableModelColumn, textModelColumn, textEditableModelColumn, colorModelColumn);			
	}

	appendProgressBarColumn(name, progressModelColumn) {
		return Table.appendProgressBarColumn(this.handle, name, progressModelColumn);			
	}

	appendButtonColumn(name, buttonModelColumn, buttonClickableModelColumn) {
		return Table.appendButtonColumn(this.handle, name, buttonModelColumn, buttonClickableModelColumn);		
	}
}

module.exports = {UiTable};
