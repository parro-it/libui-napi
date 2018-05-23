// MODIFIED FROM
// https://github.com/jsdoc2md/dmd/blob/f45cb5c9abc609412afe0d539899700fd19fe617/helpers/ddata.js

var util = require('util');
var arrayify = require('array-back');
var where = require('test-value').where;

function _identifiers(options) {
	var query = {}

	for (var prop in options.hash) {
		if (/^-/.test(prop)) {
			query[prop.replace(/^-/, '!')] = options.hash[prop];
		} else if (/^_/.test(prop)) {
			query[prop.replace(/^_/, '')] = new RegExp(options.hash[prop]);
		} else {
			query[prop] = options.hash[prop];
		}
	}
	return arrayify(options.data.root).filter(where(query)).filter(function(doclet) {
		return !doclet.ignore &&
			   (state.options.private ? true : doclet.access !== 'private');
	})
}

module.exports.toLowerCase = function(str) {
	return str ? str.toLowerCase() : '';
};

module.exports.anchorName = function(options) {
	if (!this.id) {
		throw new Error('[anchorName helper] cannot create a link without a id: ' +
						JSON.stringify(this));
	}
	if (this.inherited) {
		options.hash.id = this.inherits;
		var inherits = _identifiers(options)[0];
		if (inherits) {
			return anchorName.call(inherits, options);
		} else {
			// return '';
		}
	}
	return util.format('%s%s%s', this.isExported ? 'exp_' : '',
					   this.kind === 'constructor' ? 'new_' : '',
					   this.id.replace(/:/g, '_')
						   .replace(/~/g, '..')
						   .replace(/\(\)/g, '_new')
						   .replace(/#/g, '_'));
}