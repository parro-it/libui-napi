const {Entries} = require('..');
const {UiEntryBase} = require('./entry-base');

/**
 * A single line text entry widget that mask the input, useful to edit passwords or other sensible data.
 * @extends UiEntryBase
 */
class UiPasswordEntry extends UiEntryBase {
	/**
	 * Create a new UiPasswordEntry object.
	 * @return {UiPasswordEntry}
	 */
	constructor() {
		super(Entries.createPassword());
	}
}

module.exports = {UiPasswordEntry};
