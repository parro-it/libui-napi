const fs = require('fs');
const path = require('path');
const mv = require('mv');
const https = require('https');
const homePath = require('home-path');
const mkdirp = require('mkdirp');

const debug = require('debug')('libui-download');

const requestHttps = url => new Promise((resolve, reject) => {
	const req = https.get(url, resolve);
	req.on('error', reject);
});

module.exports = function(project) {
	const PROJECT = project.toUpperCase();
	return {
		requestHttps,
		mkCacheDir(cache) {
			try {
				mkdirp.sync(cache);
				return cache;
			} catch (err) {
				if (err.code !== 'EACCES') {
					debug('mkCacheDir error: ', err.stack);
					throw err;
				}

				// try local folder if homedir is off limits (e.g. some linuxes return '/'
				// as homedir)
				var localCache = path.resolve('./.' + project);

				mkdirp.sync(localCache);
				return localCache;
			}
		},
		cacheDir(opts) {
			opts = opts || {};
			var homeDir = homePath();
			return opts.cache || path.join(homeDir, './.' + project);
		},
		buildUrl(opts, filename) {
			var url = process.env[`NPM_CONFIG_${PROJECT}_MIRROR`] ||
					  process.env[`${PROJECT}_MIRROR`] || opts.mirror ||
					  `https://github.com/parro-it/${project}/releases/download/`;

			url += process.env[`${PROJECT}_CUSTOM_DIR`] || opts.customDir || opts.version;
			url += '/';
			url += process.env[`${PROJECT}_CUSTOM_FILENAME`] || opts.customFilename ||
				   filename;
			return url;
		},
		doDownload(res, url, target, cachedZip) {
			if (res.statusCode !== 200) {
				throw new Error(`Https request failed for ${
					res.headers.location} with code ${res.statusCode}.`);
			}

			debug(`Https request for ${url} ok with code 200.`);

			const fileWrite = res.pipe(fs.createWriteStream(target));

			return new Promise(async (resolve, reject) => {
				const finish = () => {
					debug('end stream reached', target, cachedZip);
					mv(target, cachedZip, function(err) {
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
	};
};