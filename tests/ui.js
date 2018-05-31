const test = require('tape');
const path = require('path');
const execFileSync = require('child_process').execFileSync;

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
			total++;
			failed++;
			console.log(`not ok ${total} - ${file}`);
			console.log('  ---');
			if (/_diff\.png$/.test(err)) {
				console.log(`    message: Looks different, see ${err}`);
			} else {
				console.log(`    message: ${err}`);
			}
			console.log('  ...');
			break;
		case 'PASSED':
			total++;
			passed++;
			console.log(`ok ${total} - ${file}`);
			break;
	}
}

process.chdir(path.resolve(__dirname, '..'));
const tester = require('screenshot-tester')(
	{outDir: 'tests/_snapshots', accuracy: 500, logger: tapLogger});

test('ui', t => {
	const start = test.getHarness()._results.count;
	total = start;

	tester('example/area-adv.js', 'Area Advanced', {delay: 500, delta: 100})
		.then(() => tester('example/area-scrolling.js', 'Area window',
						   {delay: 500, delta: 100}))
		.then(() => tester('example/area.js', 'Area window', {delay: 500, delta: 100}))
		.then(() => tester('example/core-api.js', 'Test window'))
		.then(() => tester('example/forms.js', 'Forms window'))
		.then(() => tester('example/grid.js', 'Forms window'))
		.then(() => tester('example/node-pad.js', 'Node Pad'))
		.then(() => tester('example/text.js', 'textDrawArea Example'))
		.then(() => {
			execFileSync('npm', ['install'], {cwd: path.join('example', 'gallery')});
			execFileSync('npm', ['run', 'build'], {cwd: path.join('example', 'gallery')});
			return tester('example/gallery/dist/index.js', 'Control Gallery');
		})
		.then(() => tester.generateHTML())
		.then(() => {
			test.getHarness()._results.count += total - start;
			test.getHarness()._results.pass += passed;
			test.getHarness()._results.fail += failed;
			t.end();
		});
});
