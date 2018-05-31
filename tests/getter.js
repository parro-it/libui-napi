const test = require('tape');
const {DrawBrush, Point, UiAreaKeyEvent} = require('..');

test('getters and setters', t => {
	const x = new DrawBrush();
	t.equal(x.getType(), 0, 'applySetterGetter: getter works');
	x.setType(1);
	t.equal(x.getType(), 1, 'applySetterGetter: setter works and getter updates');

	const y = new Point(1, 2);
	t.equal(y.getX(), 1, 'applySetterGetterAll(true): getter works');
	y.setX(0);
	t.equal(y.getX(), 0, 'applySetterGetterAll(true): setter works and getter updates');

	const z = new UiAreaKeyEvent(74, 0, UiAreaKeyEvent.modifierKeys.alt, 0, true);
	t.equal(z.getKey(), 'J', 'applySetterGetterAll(false): getter works');
	t.equal(z.modifier, UiAreaKeyEvent.modifierKeys.alt,
			'applySetterGetterAll(false): property is correct');
	t.equal(z.getModifier(), UiAreaKeyEvent.modifierKeys.alt,
			'applySetterGetterAll(false): getter is correct');
	t.throws(() => z.setKey(40), /TypeError: z\.setKey is not a function/,
			 'applySetterGetterAll(false): setter doesn\'t exist');
	t.end();
});
