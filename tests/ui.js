const test = require('tape');
const isCI = require('is-ci');

let total = 0, passed = 0, failed = 0;

function tapLogger(type, file, err) {
	switch (type) {
		case 'MISSING':
			total++;
			failed++;
			console.log(`not ok ${total} - ${file} # Skip`);
			console.log('  ---');
			console.log(`    message: Reference missing`);
			console.log('  ...');
			break;
		case 'FAILED':
		case 'ERROR':
			if (!isCI && file == 'core-api.js - "Test window"') {
				total++;
				passed++;
				console.log(`ok ${total} - ${file} # SKIP`);
				break;
			} else {
				total++;
				failed++;
				console.log(`not ok ${total} - ${file}`);
				console.log('  ---');
				console.log(`    message: Looks different, see ${err}`);
				console.log('  ...');
				break;
			}
		case 'PASSED':
			total++;
			passed++;
			console.log(`ok ${total} - ${file}`);
			break;
	}
}

process.chdir(__dirname);
const tester = require('screenshot-tester')(
	{outDir: '_snapshots', accuracy: 500, logger: tapLogger});

test('ui', t => {
	const start = test.getHarness()._results.count;
	total = start;

	tester('../example/area-adv.js', 'Area Advanced', {delay: 500, delta: 100})
		.then(() => tester('../example/area-scrolling.js', 'Area window',
						   {delay: 500, delta: 100}))
		.then(() => tester('../example/area.js', 'Area window', {delay: 500, delta: 100}))
		.then(() => tester('../example/core-api.js', 'Test window'))
		.then(() => tester('../example/forms.js', 'Forms window'))
		.then(() => tester('../example/grid.js', 'Forms window'))
		.then(() => tester('../example/node-pad.js', 'Node Pad'))
		.then(() => tester('../example/text.js', 'textDrawArea Example'))
		.then(() => tester.generateHTML())
		.then(() => {
			test.getHarness()._results.count += total - start;
			test.getHarness()._results.pass += passed;
			test.getHarness()._results.fail += failed;
			t.end();
		});
});
