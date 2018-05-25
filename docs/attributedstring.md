# AttributedString

An AttributedString is a string which also contains information about styles such as text color, font, font size. It gets drawn in an UiArea element.

```js
var libui = require('.');

var str = new libui.AttributedString('');
str.appendAttributed('Test\n', libui.FontAttribute.newSize(24));
str.appendAttributed('Background', libui.FontAttribute.newBackgroundColor(new libui.Color(0.5, 0.5, 0.5, 1)));

function draw(area, p) {
    const font = new libui.FontDescriptor('Georgia', 14, libui.textWeight.normal, libui.FontAttribute.italic.normal, libui.FontAttribute.stretch.normal);

    console.log(p.getAreaWidth())
    const layout = new libui.DrawTextLayout(str, font, p.getAreaWidth(), libui.DrawTextLayout.align.left);

    p.getContext().text(0, 0, layout);
}
function noop(){}

var win = new libui.UiWindow('AttributedString example', 300, 300, true);
win.margined = true;

const box = new libui.UiHorizontalBox();
win.setChild(box);

var area = new libui.UiArea(draw, noop, noop, noop, noop);
box.append(area, true);

win.onClosing(function () {
    win.close();
    libui.stopLoop();
});

win.show();
libui.startLoop();
```


# Classes

---



# AttributedString

A styled string.

## Constructor

**Arguments**

* s: String

## Methods

### deleteString

Removes characters in the range `start` - `end`(exclusive).

**Arguments**

* start: Number
* end: Number

### setAttribute

Sets an attribute in the range `start` - `end`(exclusive).

**Arguments**

* attr: FontAttribute
* start: Number
* end: Number


### appendUnattributed

Appends a string without any attributes.

**Arguments***

* s: String

### insertUnattributed

Inserts a string without any attributes at `pos`.

**Arguments***

* s: String
* pos: Number


### appendAttributed

Appends a string with the specified attributes.

**Arguments***

* s: String
* a1: FontAttribute
* a2: FontAttribute (optional)
* (optionally more attributes)

### insertAttributed

Inserts a string with the specified attributes at `pos`.

**Arguments***

* s: String
* pos: Number
* a1: FontAttribute
* a2: FontAttribute (optional)
* (optionally more attributes)


### toString

Returns the text content.

### forEach

Iterates over all attributes. Return `true` in the callback to break.

**Arguments**

* cb: `function(AttributedString, FontAttribute, start: number,  end: Number)`

### numGraphemes

Returns the number of graphemes (characters from the point of view of the user).

### byteIndexToGrapheme

> The cursor of a text editor is always placed on a grapheme boundary, so you can use these features to move the cursor left or right by one "character".

Converts a byte index in the string to a grapheme index.

**Arguments**

* pos: Number

### graphemeToByteIndex

Converts a graphmeme index in the string to a byte index.

**Arguments**

* pos: Number


# FontAttribute

not every font supports every style


## Static Functions

### newFamily

Returns a new FontAttribute for the font `family`.

**Arguments**

* family: String

### newSize

Returns a new FontAttribute for the font size `size`.

**Arguments**

* size: Number

### newWeight

Returns a new FontAttribute for the font weight `weight`.

**Arguments**

* weight: Number. Possible values:
    * `libui.FontAttribute.weight.minimum`
    * `libui.FontAttribute.weight.thin`
    * `libui.FontAttribute.weight.ultraLight`
    * `libui.FontAttribute.weight.light`
    * `libui.FontAttribute.weight.book`
    * `libui.FontAttribute.weight.normal`
    * `libui.FontAttribute.weight.medium`
    * `libui.FontAttribute.weight.semiBold`
    * `libui.FontAttribute.weight.bold`
    * `libui.FontAttribute.weight.ultraBold`
    * `libui.FontAttribute.weight.heavy`
    * `libui.FontAttribute.weight.ultraHeavy`
    * `libui.FontAttribute.weight.maximum`
    * any number between `minimum` and `maximum`

### newItalic

Returns a new FontAttribute for the italic style `style`.

**Arguments**

* style:
    * `libui.FontAttribute.italic.normal`
    * `libui.FontAttribute.italic.oblique` ("slanted version of normal")
    * `libui.FontAttribute.italic.italic` ("true italics")

### newStretch

Returns a new FontAttribute for the stretch (or width) style `style`.

**Arguments**

* style:
    * `libui.FontAttribute.stretch.ultraCondensed`
    * `libui.FontAttribute.stretch.extraCondensed`
    * `libui.FontAttribute.stretch.condensed`
    * `libui.FontAttribute.stretch.semiCondensed`
    * `libui.FontAttribute.stretch.normal`
    * `libui.FontAttribute.stretch.semiExpanded`
    * `libui.FontAttribute.stretch.expanded`
    * `libui.FontAttribute.stretch.extraExpanded`
    * `libui.FontAttribute.stretch.ultraExpanded`

### newColor

Returns a new FontAttribute for the text color `color`.

**Arguments**

* color: Color

### newBackgroundColor

Returns a new FontAttribute for the background color `color`.

**Arguments**

* color: Color

### newUnderline

Returns a new FontAttribute for the underline style `style`.

**Arguments**

* style:
    * `libui.FontAttribute.underline.none`
    * `libui.FontAttribute.underline.single`
    * `libui.FontAttribute.underline.double`
    * `libui.FontAttribute.underline.suggestion`

### newUnderlineColor

Returns a new FontAttribute for the underline color.

**Arguments**

* colorAttr:
    * `libui.FontAttribute.underlineColor.custom`
    * `libui.FontAttribute.underlineColor.spelling`
    * `libui.FontAttribute.underlineColor.grammar`
    * `libui.FontAttribute.underlineColor.auxiliary`
* color: Color (required only with `textUnderlineColor.custom`)

### newOTFeatures(OpenTypeFeatures *otf);

Returns a new FontAttribute with the OpenTypeFeatures `otf`.

**Arguments**

* otf: [OpenTypeFeatures](#opentypefeatures)


## Methods

### getType

Returns the type of the attribute. Possible values:

* `libui.FontAttribute.type.family`
* `libui.FontAttribute.type.size`
* `libui.FontAttribute.type.weight`
* `libui.FontAttribute.type.italic`
* `libui.FontAttribute.type.stretch`
* `libui.FontAttribute.type.color`
* `libui.FontAttribute.type.background`
* `libui.FontAttribute.type.underline`
* `libui.FontAttribute.type.underlineColor`
* `libui.FontAttribute.type.features`

### getFamily

Returns the font family string or `null` if called on a non-family attribute.

### getSize

Returns the font size or `null` if called on a non-size attribute.

### getWeight

Returns the font weight (see [newWeight](#newweight) for values) or `null` if called on a non-weight attribute.

### getItalic

Returns the font italic style (see [newItalic](#newitalic) for values) or `null` if called on a non-italic attribute.

### getStretch

Returns the font stretch (see [newStretch](#newstretch) for values) or `null` if called on a non-stretch attribute.

### getColor

Returns the color or `null` if called on a non-color attribute.

### getUnderline

Returns the underline style (see [newUnderline](#newunderline) for values) or `null` if called on a non-underline-style attribute.

### getUnderlineColor

Returns an object describing the underline color or `null` if called on a non-underline-style attribute.

```js
{
  type: textUnderlineColor.custom,
  color: Color
}
// or
{
  type: textUnderlineColor.grammar | spelling | auxiliary,
  color: null
}
```
See [newUnderlineColor](#newunderlinecolor) for `type` values)


### getOTFeatures

Returns the [OpenTypeFeatures](#opentypefeatures) or `null` if called on a non-OpenType-features attribute.

# OpenTypeFeatures

Defines font glyph settings (ignored if not supported by the font).

See [here](https://docs.microsoft.com/de-de/typography/opentype/spec/featuretags) for more information and a list of feature tags.

All `tag` arguments in the following methods *must* be strings of length 4.

Example: Setting `liga` to `1` enables ligatures (not supported by every font):

```js
const otf = new libui.OpenTypeFeatures();
otf.add('liga', 1)

str.appendAttributed('affix', FontAttribute.newOTFeatures(otf));
```

## Methods

### clone

Returns a copy of the object.

### add

Adds/overwrites a `tag` with `value`.

**Arguments**

* tag: String
* value: Number


### remove

Remove a tag (and use the default).

**Arguments**

* tag: String

### get

Returns the value of `tag` or `null` if not set.

**Arguments**

* tag: String

### forEach

Iterates over all tags. Return `true` in the callback to break.

**Arguments**

* cb: `function(OpenTypeFeatures, tag: String, value: Number)`

# FontDescriptor

Defines a font.

## Constructor

**Arguments**

* family: String
* size: Number
* weight: see [FontAttribute.newWeight](#newweight)
* italic: see [FontAttribute.newItalic](#newitalic)
* stretch: see [FontAttribute.newStretch](#newstretch)

## Methods

### getFamily

Returns the font family.

### getSize

Returns the font size.

### getWeight

Returns the font weight.

### getItalic

Returns the italic style.

### getStretch

Returns the font stretch.

# DrawTextLayout

Defines how an attributed string should get drawn onto an area. (See [Area UiDrawContext.text](area.md#text))

## Constructor

**Arguments**

* str: [AttributedString](#attributedstring)
* defaultFont: [FontDescriptor](#fontdescriptor)
* width: Number (i.e. `drawParams.getAreaWidth()`)
* align:
    - `libui.DrawTextLayout.align.left`
    - `libui.DrawTextLayout.align.center`
    - `libui.DrawTextLayout.align.right`


## Methods

### getExtents

Returns a SizeDouble containing the actual width and height of the text.