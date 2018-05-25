require('..');
const test = require('tape');
const boxen = require('boxen');

test('c tests for internal files', t => {
	if (process.env.LIBUI_TARGET !== 'test') {
		console.error(
			boxen('Please run tests using `npm test`', {padding: 1, borderColor: 'red'}));
		process.exit(1);
	}

	const {check_c_tests} = require('../ui.node');
	check_c_tests.run_tests();

	t.pass('tests executed');
	t.end();
});
