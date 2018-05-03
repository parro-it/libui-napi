var tape = require('tape');
const {App} = require('./');


tape('does not crash', t => {
	App.init();
	t.pass('did not crash');
	t.end();
});
