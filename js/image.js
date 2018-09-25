const {Image} = require('..');
const {readFile} = require('fs');
const parsePng = require('parse-png');

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

	static loadFromPng(pngPath) {
		return new Promise((resolve, reject) => {
			readFile(pngPath, (err, data) => {
				if (err) {
					return reject(err);
				}

				parsePng(data)
					.then(png => {
						const img = new UiImage(png.width, png.height);
						img.append(png.data, png.width, png.height, png.width * 4);
						resolve(img);
					})
					.catch(reject);
			});
		});
	}
}

module.exports = {UiImage};
