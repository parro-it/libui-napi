const {Area} = require('..');

/**
 * An area to draw on.
 */
class UiArea {
	/**
	 * Create a new UiArea object.
	 * @return {UiArea}
	 */
	constructor(draw, mouse, mouseCrossed, dragBroken, keyEvent) {
		this.handle = Area.create(draw || (() => {console.log('draw')}),
								  mouse || (() => {console.log('mouse')}),
								  mouseCrossed || (() => {console.log('crossed')}),
								  dragBroken || (() => {}),
								  keyEvent || (() => {console.log('key')}));
	}
}

module.exports = {UiArea};
