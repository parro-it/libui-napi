const {readdirSync} = require('fs');
const {platform} = require('os')

function listDir(dir) {
	readdirSync(dir)
		.filter(f => f.endsWith('.c') || f.endsWith('.m'))
		.forEach(f => console.log(`${dir}/${f}`));
}

listDir('src');
listDir(`src/arch/${platform()}`);
if (process.env.LIBUI_TARGET === 'test') {
	listDir('tests/internals');
} else {
	console.log('tools/test_main_stub.c');
}
