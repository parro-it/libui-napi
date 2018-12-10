'use strict';
const libui = require('..');

const {FontAttribute} = libui;

let mainwin;
let textDrawArea;
let fontButton;
let align;
let checkbox;

const str = new libui.AttributedString(
	'\n👨🏻 Drawing strings with libui is done with the uiAttributedString and uiDrawTextLayout objects.\n' +
	'uiAttributedString lets you have a variety of attributes: ');

str.setAttribute(FontAttribute.newBackgroundColor(new libui.Color(0, 0, 1, 1)), 0,
				 Buffer.from('👨🏻').length);

str.appendAttributed('font family', FontAttribute.newFamily('Courier New'));
str.appendUnattributed(', ');

str.appendAttributed('font size', FontAttribute.newSize(18));
str.appendUnattributed(', ');

str.appendAttributed('font weight', FontAttribute.newWeight(FontAttribute.weight.bold));
str.appendUnattributed(', ');

str.forEach((str, attr, start, end) => {
	console.log({str, attr, start, end});
});

str.appendAttributed('font italicness',
					 FontAttribute.newItalic(FontAttribute.italic.italic));
str.appendUnattributed(', ');

str.appendAttributed('font stretch',
					 FontAttribute.newStretch(FontAttribute.stretch.condensed));
str.appendUnattributed(', ');

str.appendAttributed('text color',
					 FontAttribute.newColor(new libui.Color(0.75, 0.25, 0.5, 0.75)));
str.appendUnattributed(', ');

str.appendAttributed('text background color', FontAttribute.newBackgroundColor(
												  new libui.Color(0.5, 0.5, 0.25, 0.5)));
str.appendUnattributed(', ');

str.appendAttributed('underline style',
					 FontAttribute.newUnderline(FontAttribute.underline.single));
str.appendUnattributed(', ');

str.appendUnattributed('and ');
str.appendAttributed(
	'underline color', FontAttribute.newUnderline(FontAttribute.underline.double),
	FontAttribute.newUnderlineColor(FontAttribute.underlineColor.custom,
									new libui.Color(1.0, 0.0, 0.5, 1.0)));
str.appendUnattributed('. ');

str.appendUnattributed('Furthermore, there are attributes allowing for ');
str.appendAttributed(
	'special underlines for indicating spelling errors',
	FontAttribute.newUnderline(FontAttribute.underline.suggestion),
	FontAttribute.newUnderlineColor(FontAttribute.underlineColor.spelling));
str.appendUnattributed(' (and ');
str.appendAttributed(
	'other types of errors',
	FontAttribute.newUnderline(FontAttribute.underline.suggestion),
	FontAttribute.newUnderlineColor(FontAttribute.underlineColor.grammar));
str.appendUnattributed(') ');

str.appendUnattributed(
	'and control over OpenType features such as ligatures (with a suitable font - for instance, ');

const otf = new libui.OpenTypeFeatures();
otf.add('liga', 0);
str.appendAttributed('affix', FontAttribute.newOTFeatures(otf));
str.appendUnattributed(' vs. ');

otf.add('liga', 1);
str.appendAttributed('affix', FontAttribute.newOTFeatures(otf));

otf.forEach((feat, str, val) => {
	console.log({feat, str, val});
});

console.log('liga:', otf.get('liga'));

str.appendUnattributed(').\n');

str.appendUnattributed(
	'Use the controls opposite to the text to control properties of the text.\n');
str.appendAttributed('👨🏾\n',
					 FontAttribute.newBackgroundColor(new libui.Color(0, 1, 0, 1)));

str.appendAttributed('And multiple attributes at once!',
					 FontAttribute.newColor(new libui.Color(1, 1, 1, 1)),
					 FontAttribute.newBackgroundColor(new libui.Color(0, 0, 0, 1)),
					 FontAttribute.newFamily('Monaco'));

str.insertAttributed('Styled Strings\n', 0,
					 FontAttribute.newWeight(FontAttribute.weight.bold),
					 FontAttribute.newSize(24));

function handlerDraw(area, p) {
	const font = checkbox.checked ? new libui.FontDescriptor('Georgia', 12,
															 FontAttribute.weight.normal,
															 FontAttribute.italic.normal,
															 FontAttribute.stretch.normal)
								  : fontButton.getFont();

	const layout =
		new libui.DrawTextLayout(str, font, p.getAreaWidth(), align.getSelected());

	p.getContext().text(0, 0, layout);
}

function noop() {}

function redraw() {
	textDrawArea.queueRedrawAll();
}

function main() {
	mainwin = new libui.UiWindow('textDrawArea Example', 640, 480, true);
	mainwin.margined = true;
	mainwin.onClosing(() => {
		libui.stopLoop();
	});

	const hbox = new libui.UiHorizontalBox();
	hbox.padded = true;
	mainwin.setChild(hbox);

	const vbox = new libui.UiVerticalBox();
	vbox.padded = true;
	hbox.append(vbox, false);

	fontButton = new libui.UiFontButton();
	fontButton.enabled = false;
	fontButton.onChanged(redraw);
	vbox.append(fontButton, false);

	const form = new libui.UiForm();
	form.padded = true;
	vbox.append(form, false);

	checkbox = new libui.UiCheckbox();
	checkbox.checked = true;
	checkbox.text = 'Use Georgia instead of button';
	checkbox.onToggled(() => {
		fontButton.enabled = !checkbox.checked;
		redraw();
	});
	vbox.append(checkbox, false);

	align = new libui.UiCombobox();
	// Note that the items match with the value order of DrawTextLayout.align
	align.append('Left');
	align.append('Center');
	align.append('Right');
	align.setSelected(0);
	align.onSelected(redraw);
	form.append('Alignment', align, false);

	textDrawArea = new libui.UiArea(handlerDraw, noop, noop, noop, noop);
	hbox.append(textDrawArea, true);

	mainwin.show();

	libui.startLoop();
}

main();
