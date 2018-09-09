const test = require('tape');
const {TableModel} = require('..');

test('TableModel has a create fn', t => {
	t.equal(typeof TableModel.create, 'function');
	t.end();
});

test('TableModel create fn require 5 fn args', t => {
	const fn = test;
	t.throws(() => TableModel.create(42), /Too few arguments/);
	t.throws(() => TableModel.create({}, {}, {}, {}, {}),
			 /Argument numColumns: a function was expected/);
	t.throws(() => TableModel.create(fn, {}, {}, {}, {}),
			 /Argument numRows: a function was expected/);
	t.throws(() => TableModel.create(fn, fn, {}, {}, {}),
			 /Argument columnType: a function was expected/);
	t.throws(() => TableModel.create(fn, fn, fn, {}, {}),
			 /Argument cellValue: a function was expected/);
	t.throws(() => TableModel.create(fn, fn, fn, fn, {}),
			 /Argument setCellValue: a function was expected/);
	TableModel.create(fn, fn, fn, fn, fn);
	t.end();
});
