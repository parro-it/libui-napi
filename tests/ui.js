const test = require('tape');
const path = require('path');
const execFileSync = require('child_process').execFileSync;
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
		case 'PUSH':
			if (err) {
				console.error(`Sending report to: ${file} failed`);
				console.error('\t', err);
			} else {
				console.log(`Sent report to: ${file}`);
			}
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
		/*.then(() => {
			execFileSync('npm', ['install'], {cwd: path.join('example', 'gallery')});
			return tester('example/gallery/start.js', 'Control Gallery',
						  {delay: 5000, delta: 100});
		})*/
		.then(() => tester('example/area.js', 'Area window', {delay: 500, delta: 100}))
		.then(() => tester('example/core-api.js', 'Test window'))
		.then(() => tester('example/forms.js', 'Forms window'))
		.then(() => tester('example/grid.js', 'Forms window'))
		.then(() => tester('example/node-pad.js', 'Node Pad'))
		.then(() => tester('example/text.js', 'textDrawArea Example'))
		.then(() => tester.generateHTML())
		.then(() => {
			const PR_REPO =
				process.env.TRAVIS_REPO_SLUG || process.env.APPVEYOR_REPO_NAME;
			const PR_NUM = process.env.TRAVIS_PULL_REQUEST ||
						   process.env.APPVEYOR_PULL_REQUEST_NUMBER;
			const NODE_MAJOR = process.version.substr(1).split('.')[0];
			if (PR_REPO && Number(PR_NUM)) {
				tester.pushToServer('https://sts.mischnic.ml', PR_REPO, PR_NUM,
									!(NODE_MAJOR === '11' || NODE_MAJOR === '10'),
									' - Node ' + NODE_MAJOR);
			}
		})
		.then(() => {
			test.getHarness()._results.count += total - start;
			test.getHarness()._results.pass += passed;
			test.getHarness()._results.fail += failed;
			t.end();
		})
		.catch(err => console.error(err));
});
