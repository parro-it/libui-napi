const fs = require('fs');
const os = require('os');
const path = require('path');
const mkdirp = require('mkdirp');
const homePath = require('home-path');
const mv = require('mv');
const _debug = require('debug');
const https = require('https');
const tar = require('tar');
const utils = require('util');
const isCI = require('is-ci');

const mkdir = utils.promisify(mkdirp)
const debug = _debug('libui-napi-download');
const requestHttps = url => new Promise((resolve, reject) => {
	const req = https.get(url, resolve);
	req.on('error', reject);
});

const pathExists = utils.promisify(fs.exists);

function nodePlatformToOS(arch) {
	switch (arch) {
		case 'darwin': return 'osx';
		case 'win32': return 'win';
		case 'linux': return 'linux';
		default: throw new Error('Unknown platform ' + arch);
	}
}

function cacheDir(opts = {}) {
	var homeDir = homePath();
	return opts.cache || path.join(homeDir, './.libui-napi');
}

async function mkCacheDir(cache) {
	try {
		await mkdir(cache);
		return cache;
	} catch (err) {
		if (err.code !== 'EACCES') {
			debug('mkCacheDir error: ', err.stack);
			throw err;
		}

		// try local folder if homedir is off limits (e.g. some linuxes return '/' as homedir)
		var localCache = path.resolve('./.libui-napi');

		await mkdir(localCache);
		return localCache;
	}
}

function buildUrl(opts, filename) {
	var url = process.env.NPM_CONFIG_LIBUI_MIRROR ||
		process.env.LIBUI_MIRROR ||
		opts.mirror ||
		'https://github.com/parro-it/libui-napi/releases/download/';

	url += process.env.LIBUI_CUSTOM_DIR || opts.customDir || opts.version;
	url += '/';
	url += process.env.LIBUI_CUSTOM_FILENAME || opts.customFilename || filename;
	return url;
}

async function download(opts) {
	const platform = nodePlatformToOS(opts.platform || os.platform());
	let arch = opts.arch || os.arch();
	if (platform !== 'win' && arch === 'x64') {
		arch = 'x86_64';
	}
	opts.version = 'v' + opts.version;
	const version = opts.version;
	const symbols = opts.symbols || false;

	const filename = `${version}-${platform}-${arch}.tar.gz`;

	const url = buildUrl(opts, filename);
	const cache = cacheDir(opts.cache);
	const actualCache = await mkCacheDir(cache);

	debug('info', {cache: cache, filename: filename, url: url});

	let cachedZip = path.join(cache, filename);
	const exists = await pathExists(cachedZip);

	if (exists) {
		debug('zip exists', cachedZip);
		return cachedZip;
	}

	debug('creating cache/tmp dirs');

	// otherwise download it
	cachedZip = path.join(actualCache, filename); // in case cache dir changed

	// download to tmpdir
	var tmpdir = path.join(
		os.tmpdir(),
		'libui-napi-tmp-download-' + process.pid + '-' + Date.now()
	);

	await mkdir(tmpdir);
	debug(tmpdir + 'created');

	debug('downloading zip', url, 'to', tmpdir);

	const target = path.join(tmpdir, filename);

	const resRedirect = await requestHttps(url);
	if (resRedirect.statusCode === 404) {
		throw new Error(`Prebuilt binaries not found for your platform and architecture.`);
	}

	if (resRedirect.statusCode !== 302) {
		throw new Error(`Https request failed for ${url} with code ${resRedirect.statusCode}: resource not found.`);
	}


	const res = await requestHttps(resRedirect.headers.location);
	if (res.statusCode !== 200) {
		throw new Error(`Https request failed for ${res.headers.location} with code ${res.statusCode}.`);
	}

	debug(`Https request for ${url} ok with code 200.`);

	const fileWrite = res.pipe(fs.createWriteStream(target));

	return new Promise(async(resolve, reject) => {

		const finish = () => {
			debug('end stream reached', target, cachedZip);
			mv(target, cachedZip, function (err) {
				if (err) {
					reject(err);
				} else {
					resolve(cachedZip);
				}
			});
		};

		fileWrite.on('finish', finish);
		fileWrite.on('error', reject);
	});
}

async function main() {

	if (isCI) {
		console.log('Running on a CI server, force rebuild.');
		process.exit(1);
	}

	const zipPath = await download({version: process.env.npm_package_version});
	console.log('Downloaded zip:', zipPath);
	await tar.extract({file: zipPath});
	console.log('Libui-napi binaries extracted to:', process.cwd());
}

main().catch(err => {
	console.error(err.message);
	process.exit(1);
});
