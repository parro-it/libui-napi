const {Box} = require('..');
const {UiBox} = require('./box');

/**
 * A container that stacks its chidren vertically.
 * @extends UiBox
 */
class UiVerticalBox extends UiBox {
	/**
	 * Create a new UiVerticalBox object.
	 * @return {UiVerticalBox}
	 */
	constructor() {
		super(Box.createVertical());
	}
}

module.exports = {UiVerticalBox};
