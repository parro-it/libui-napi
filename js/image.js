const {Image} = require('..');

/**
 * An image.
 */
class UiImage {
	/**
	 * Create a new UiImage object.
	 * @return {UiImage}
	 */
	constructor(width, height) {
		this._img = Image.create(width, height);
	}

    append(pixels, pixelWidth,	pixelHeight, byteStride) {
        Image.append(this._img, pixels, pixelWidth,	pixelHeight, byteStride);
    }

}

module.exports = {UiImage};
