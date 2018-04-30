const {readdirSync} = require('fs');
const {platform} = require('os')

function listDir(dir) {
	readdirSync(dir)
		.filter(f => f.endsWith('.c'))
		.forEach(f => console.log(`${dir}/${f}`));
}

listDir('src');
listDir(`src/arch/${platform()}`);
