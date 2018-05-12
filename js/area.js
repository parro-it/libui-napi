const {Area} = require('..');

function logMouse(area, areaEvent) {
	console.log(area, {
		x: areaEvent.getX(),
		y: areaEvent.getY(),
		areaWidth: areaEvent.getAreaWidth(),
		areaHeight: areaEvent.getAreaHeight(),
		down: areaEvent.getDown(),
		up: areaEvent.getUp(),
		count: areaEvent.getCount(),
		modifiers: areaEvent.getModifiers(),
		held1To64: areaEvent.getHeld1To64()
	});
}

/**
 * An area to draw on.
 */
class UiArea {
	/**
	 * Create a new UiArea object.
	 * @return {UiArea}
	 */
	constructor(draw, mouse, mouseCrossed, dragBroken, keyEvent) {
		this.handle = Area.create(
			draw || (() => {console.log('draw')}), mouse || logMouse,
			mouseCrossed || (() => {console.log('crossed')}), dragBroken || (() => {}),
			keyEvent || (() => {console.log('key')}));
	}
}

module.exports = {UiArea};
