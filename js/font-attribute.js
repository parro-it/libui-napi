const {FontAttribute: FontAttributeC} = require('..');

class FontAttribute {
	constructor(handle) {
		this.handle = handle;
	}

	get type() {
		return FontAttributeC.getType(this.handle);
	}

	get family() {
		return FontAttributeC.getFamily(this.handle);
	}

	get size() {
		return FontAttributeC.getSize(this.handle);
	}

	get weight() {
		return FontAttributeC.getWeight(this.handle);
	}

	get italic() {
		return FontAttributeC.getItalic(this.handle);
	}

	get stretch() {
		return FontAttributeC.getStretch(this.handle);
	}

	static newFamily(v) {
		return new FontAttribute(FontAttributeC.createFamily(v));
	}

	static newSize(v) {
		return new FontAttribute(FontAttributeC.createSize(v));
	}

	static newWeight(v) {
		return new FontAttribute(FontAttributeC.createWeight(v));
	}

	static newItalic(v) {
		return new FontAttribute(FontAttributeC.createItalic(v));
	}

	static newStretch(v) {
		return new FontAttribute(FontAttributeC.createStretch(v));
	}

	static newColor(c) {
		return new FontAttribute(FontAttributeC.createColor(v.r, v.g, v.b, b.a));
	}

	static newBackgroundColor(c) {
		return new FontAttribute(
			FontAttributeC.createBackgroundColor(v.r, v.g, v.b, b.a));
	}

	static newUnderline(v) {
		return new FontAttribute(FontAttributeC.createUnderline(v));
	}

	static newUnderlineColor(type, c) {
		return new FontAttribute(
			FontAttributeC.createUnderlineColor(type, v.r, v.g, v.b, b.a));
	}

	// static newOTFeatures(otf){

	// }
}

FontAttribute.weight = {
	minimum: 0,
	thin: 100,
	ultraLight: 200,
	light: 300,
	book: 350,
	normal: 400,
	medium: 500,
	semiBold: 600,
	bold: 700,
	ultraBold: 800,
	heavy: 900,
	ultraHeavy: 950,
	maximum: 1000
};

FontAttribute.italic = {
	normal: 0,
	oblique: 1,
	italic: 2
};

FontAttribute.stretch = {
	ultraCondensed: 0,
	extraCondensed: 1,
	condensed: 2,
	semiCondensed: 3,
	normal: 4,
	semiExpanded: 5,
	expanded: 6,
	extraExpanded: 7,
	ultraExpanded: 8
};

FontAttribute.attributeType = {
	family: 0,
	size: 1,
	weight: 2,
	italic: 3,
	stretch: 4,
	color: 5,
	background: 6,
	underline: 7,
	underlineColor: 8,
	features: 9
};

FontAttribute.underline = {
	none: 0,
	single: 1,
	double: 2,
	suggestion: 3
};

FontAttribute.underlineColor = {
	custom: 0,
	spelling: 1,
	grammar: 2,
	auxiliary: 3
};

module.exports = {FontAttribute};
