const test = require('tape');

process.chdir(__dirname);
const tester = require('screenshot-tester')({outDir: '_snapshots', accuracy: 500});

test('ui test', t => {
	t.plan(1);

	tester('../example/area-adv.js', 'libui textDrawArea Example',
		   {delay: 500, delta: 100})
		.then(() => tester('../example/area-scrolling.js', 'Area window',
						   {delay: 500, delta: 100}))
		.then(() => tester('../example/area.js', 'Area window', {delay: 500, delta: 100}))
		.then(() => tester('../example/core-api.js', 'Test window'))
		.then(() => tester('../example/forms.js', 'Forms window'))
		.then(() => tester('../example/grid.js', 'Forms window'))
		.then(() => tester('../example/node-pad.js', 'Node Pad'))
		.then(() => tester.generateHTML())
		.then(() => {
			t.equal(tester.result(), 0);
		});
});
