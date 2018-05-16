const test = require('tape');
const {DrawBrush, Point, UiAreaKeyEvent} = require('..');

test('getters and setters', t => {
	t.plan(6);

	const x = new DrawBrush();
	t.ok(x.getType() === 0);
	x.setType(1);
	t.ok(x.getType() === 1);

	const y = new Point(1, 2);
	t.ok(y.getX() === 1);
	y.setX(0);
	t.ok(y.getX() === 0);

	const z = new UiAreaKeyEvent(74, 0, 0, 0, true);
	t.ok(z.getKey() == 'J');
	t.throws(() => z.setKey(40), /TypeError: z\.setKey is not a function/);
});
