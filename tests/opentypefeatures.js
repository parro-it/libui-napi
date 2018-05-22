const test = require('tape');
const {OpenTypeFeatures, FontAttribute} = require('..');

test('OpenTypeFeatures', t => {
	t.plan(10);

	const otf = new OpenTypeFeatures();
	t.equal(otf.get('abcd'), null, 'is empty on creation: get');
	otf.forEach((feat, str, val) => {t.fail('isn\'t empty on creation: forEach')});

	t.throws(() => otf.add('a'), /The 'tag' argument has to be a 4 character string/,
			 'only 4 character strings: add');
	t.throws(() => otf.get('a'), /The 'tag' argument has to be a 4 character string/,
			 'only 4 character strings: get');
	t.throws(() => otf.remove('a'), /The 'tag' argument has to be a 4 character string/,
			 'only 4 character strings: remove');

	otf.add('liga', 1);
	t.equal(otf.get('liga'), 1, 'get works');
	otf.forEach((feat, str, val) => {
		t.deepEqual({feat, str, val}, {feat: otf, str: 'liga', val: 1}, 'forEach works');
	});

	const otf2 = otf.clone();

	t.equal(otf2.get('liga'), 1, 'cloned: get works');
	otf2.forEach((feat, str, val) => {
		t.deepEqual({feat, str, val}, {feat: otf2, str: 'liga', val: 1},
					'cloned: forEach works');
	});

	const otf3 = FontAttribute.newOTFeatures(otf).OTFeatures;

	t.equal(otf3.get('liga'), 1, 'attribute otf: get works');
	otf3.forEach((feat, str, val) => {
		t.deepEqual({feat, str, val}, {feat: otf3, str: 'liga', val: 1},
					'attribute otf: forEach works');
	});
});
