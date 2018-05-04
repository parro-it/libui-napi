const {Box} = require('..');
const {UiBox} = require('./box');

/**
 * A container that stacks its chidren vertically.
 * @extends UiBox
 */
class UiVerticalBox extends UiBox{
	constructor() {
		super(Box.createVertical());
	}
}

module.exports = {UiVerticalBox};
