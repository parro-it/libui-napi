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

	const results = check_c_tests.run_tests(test.getHarness()._results.count + 1);

	test.getHarness()._results.count += results.count;
	test.getHarness()._results.fail += results.fail;
	test.getHarness()._results.pass += results.pass;

	t.pass('tests executed');
	t.end();
});
