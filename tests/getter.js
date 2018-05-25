const test = require('tape');
const {DrawBrush, Point, UiAreaKeyEvent} = require('..');

test('getters and setters', t => {
	const x = new DrawBrush();
	t.equal(x.getType(), 0);
	x.setType(1);
	t.equal(x.getType(), 1);

	const y = new Point(1, 2);
	t.equal(y.getX(), 1);
	y.setX(0);
	t.equal(y.getX(), 0);

	const z = new UiAreaKeyEvent(74, 0, UiAreaKeyEvent.modifierKeys.alt, 0, true);
	t.equal(z.getKey(), 'J');
	t.equal(z.modifier, UiAreaKeyEvent.modifierKeys.alt);
	t.equal(z.getModifier(), UiAreaKeyEvent.modifierKeys.alt);
	t.throws(() => z.setKey(40), /TypeError: z\.setKey is not a function/);
	t.end();
});
