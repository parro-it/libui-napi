var tape = require('tape');
const {init} = require('./');


tape('does not crash', t => {
	init();
	t.pass('did not crash');
	t.end();
});
