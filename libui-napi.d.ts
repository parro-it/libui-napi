declare enum textWeight {
	minimum,
	thin,
	ultraLight,
	light,
	book,
	normal,
	medium,
	semiBold,
	bold,
	ultraBold,
	heavy,
	ultraHeavy,
	maximum
}

declare enum textItalic { normal, oblique, italic }

declare enum textStretch {
	ultraCondensed,
	extraCondensed,
	condensed,
	semiCondensed,
	normal,
	semiExpanded,
	expanded,
	extraExpanded,
	ultraExpanded
}

declare enum textAttributeType {
	family,
	size,
	weight,
	italic,
	stretch,
	color,
	background,
	underline,
	underlineColor,
	features
}

declare enum textUnderline { none, single, double, suggestion }

declare enum textUnderlineColor { custom, spelling, grammar, auxiliary }

/**
 * An object that contains information on a system font.
 */
export class FontDescriptor {
	/**
	 * Create a new FontDescriptor object.
	 * @param family - the name of the font, e.g. "Helvetica". `object` type is for
	 * internal use
	 * @param size - size in point of the font
	 * @param weight - weight of the font
	 * @param italic - 1 if the font is italic, otherwise 0
	 * @param stretch - horizontal stretch value for the font
	 */
	constructor(family: string|object, size: number, weight: number, italic: number,
				stretch: number);

	/**
	 * Return the name of the font, e.g. "Helvetica".
	 */
	readonly family: string;

	/**
	 * Return the size in point of the font.
	 */
	readonly size: number;

	/**
	 * Return weight of the font.
	 */
	readonly weight: textWeight;

	/**
	 * Return `1` if the font is italic, otherwise `0`.
	 */
	readonly italic: textItalic;

	/**
	 * Return horizontal stretch value for the font.
	 */
	readonly stretch: number;
}

/**
 * Stop Libui event loop
 */
export function stopLoop(): void;
/**
 * Start Libui event loop
 */
export function startLoop(): void;

export function startTimer(): void;

export function onShouldQuit(cb: () => void): void;

export class FontAttribute {
	constructor(other: FontAttribute);
	static newFamily(v: string): FontAttribute;
	static newSize(v: number): FontAttribute;
	static newWeight(v: textWeight): FontAttribute;
	static newItalic(v: textItalic): FontAttribute;
	static newStretch(v: textStretch): FontAttribute;
	static newColor(c: Color): FontAttribute;
	static newBackgroundColor(c: Color): FontAttribute;
	static newUnderline(v: textUnderline): FontAttribute;
	static newUnderlineColor(type: textUnderlineColor, color?: Color): FontAttribute;
	static newOTFeatures(otf: OpenTypeFeatures): FontAttribute;

	static getFamily(): string|null;
	static getSize(): number|null;
	static getWeight(): textWeight|null;
	static getItalic(): textItalic|null;
	static getStretch(): textStretch|null;
	static getColor(): Color|null;
	static getUnderline(): textUnderline|null;
	static getUnderlineColor(): {type: textAttributeType; color: Color | null;}|null;
	static getOTFeatures(): OpenTypeFeatures|null;

	
}

export namespace FontAttribute {
	type weight = textWeight;
	type italic = textItalic;
	type stretch = textStretch;
	type underline = textUnderline;
	type underlineColor = textUnderlineColor;
}

export class OpenTypeFeatures {
	add(tag: string, value: number): void;
	remove(tag: string): void;
	get(tag: string): number;
	forEach(cb: (feat: OpenTypeFeatures, str: string, val: number) => boolean): void;
	clone(): OpenTypeFeatures;
}

export class Color {
	r: number;
	g: number;
	b: number;
	a: number;
	constructor(r: number, g: number, b: number, a: number);
	constructor(other: Color);
}

export class Point {
	x: number;
	y: number;
	constructor(x: number, y: number);
	constructor(other: Point);
}

export class Size {
	w: number;
	h: number;
	constructor(w: number, h: number);
}

export class BrushGradientStop {
	pos: number;
	color: Color;
	constructor(pos: number, color: Color);
}

export class AttributedString {
	constructor(str: string);
	toString(): string;
	toStringLen(): number;
	appendAttributed(str: string, ...attribute: FontAttribute[]): void;
	appendUnattributed(str: string): void;
	insertAttributed(str: string, start: number, ...attribute: FontAttribute[]): void;
	insertUnattributed(str: string, at: number): void;
	deleteString(start: number, end: number): void;
	setAttribute(attr: FontAttribute, start: number, end: number): void;
	forEach(cb: (str: AttributedString, attr: FontAttribute, start: number,
				 end: number) => boolean): void;
	numGraphemes(): number;
	byteIndexToGrapheme(pos: number): number;
	graphemeToByteIndex(pos: number): number;
}

/**
 * The UiWindow class is responsible for showing and managing native windows.
 * A UiWindow instance can contain only one child. If you need
 * more than one, you have to use [Containers](containers.md).
 */
export class UiWindow {
	/**
	 * Create a new UiWindow object.
	 *
	 * @param title - text to show in window title bar.
	 * @param width - width of window in pixels.
	 * @param height -  height of window in pixels.
	 * @param hasMenubar - whether this window has a menu bar.
	 * See [Menu](#menubar).
	 */
	constructor(title: string, width: number, height: number, hasMenubar: boolean);

	/**
	 * Show the window.
	 * LibUi always returns null
	 */
	show(): void;

	/**
	 * Add a listener to the `closing` event. This event is emitted when the OS
	 * window close button is clicked. You are responsible for closing the
	 * window in response to this event.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	onClosing(callback: () => any): void;

	/**
	 * Add a listener to the `contentSizeChanged` event. This event is emitted
	 * when window content size change.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	onContentSizeChanged(callback: Function): void;

	/**
	 * Close the window.
	 */
	close(): void;

	/**
	 * Set or return the text to show in window title bar.
	 */
	title: string;

	/**
	 * Set or return the size in pixel of the content area of the window
	 * (excluding the size of the window decoration). This mean that if you set window
	 * size to 0,0 you still see title bar and OS window buttons.
	 */
	contentSize: {width: number; height: number};

	/**
	 * Set the control to show in this window content area.
	 * UiWindow instances can contain only one child. If you need
	 * more, you have to use [Containers](containers.md).
	 *
	 * @param control - the control to add as child.
	 * @param stretchy - whever the control should fill all the available space.
	 */
	setChild(control: UiControl): void;

	/**
	 * When true, an internal margin is added to the window.
	 */
	margined: boolean;

	/**
	 * When true, the window is displayed without a border.
	 */
	borderless: boolean;

	/**
	 * When true, the window is displayed in full screen mode.
	 */
	fullscreen: boolean;
}

/**
 * Base class of all controls except UiWindow
 */
export abstract class UiControl {
	/**
	 * Set or return whether the control is enabled.
	 */
	enabled: boolean;
	/**
	 * Set or return whether the control is visible.
	 */
	visible: boolean;
	/**
	 * Set or return whether the control is a top level one.
	 */
	toplevel: boolean;
	/**
	 * Create a new UiControl object.
	 */
	constructor(handle: any);
}
/**
 * An area to draw on.
 */
export class UiArea extends UiControl {
	/**
	 * Create a new scrolling UiArea object.
	 * @param draw - callback to draw onto area
	 * @param mouse - callback for mouse events
	 * @param mouseCrossed - callback for entering or leaving the area
	 * @param dragBroken - callback
	 * @param keyEvent - callback for key events
	 */
	constructor(
		// TODO params
		draw: (uiArea: UiArea, p: any) => any,
		mouse: (uiArea: UiArea, evt: UiAreaMouseEvent) => any,
		mouseCrossed: (uiArea: UiArea, evt: UiAreaMouseEvent) => any,
		dragBroken: (uiArea: UiArea) => any,
		key: (uiArea: UiArea, evt: UiAreaKeyEvent) => any);

	/**
	 * Create a new UiArea object.
	 * @param draw - callback to draw onto area
	 * @param mouse - callback for mouse events
	 * @param mouseCrossed - callback for entering or leaving the area
	 * @param dragBroken - callback
	 * @param keyEvent - callback for key events
	 * @param width Width of this UiArea
	 * @param height height of this UiArea
	 */
	constructor(
		// TODO params
		draw: (uiArea: UiArea, p: any) => any,
		mouse: (uiArea: UiArea, evt: UiAreaMouseEvent) => any,
		mouseCrossed: (uiArea: UiArea, evt: UiAreaMouseEvent) => any,
		dragBroken: (uiArea: UiArea) => any,
		key: (uiArea: UiArea, evt: UiAreaKeyEvent) => any, width: number, height: number);

	/**
	 * Force a redraw of the area (calls draw callback).
	 */
	queueRedrawAll(): void;

	/**
	 * Let the mouse move the window (only callable in the draw callback)
	 */
	beginWindowMove(): void;

	/**
	 * Let the mouse resize the window (only callable in the draw callback)
	 * @param edge - the size which is held by the mouse
	 */
	beginWindowResize(edge: number): void;

	setSize(w: number, h: number): void;

	scrollTo(x: number, y: number, w: number, h: number): void;
}

export class UiAreaMouseEvent {
	constructor(x: number, y: number, areaWidth: number, areaHeight: number,
				down: boolean, up: boolean, count: number, modifiers: any,
				held1To64: any);

	readonly x: number;
	readonly y: number;
	readonly areaWidth: number;
	readonly areaHeight: number;
	readonly down: number;
	readonly up: number;
	readonly count: number;
	readonly modifiers: number;
	readonly held1To64: number;
}

export namespace UiAreaKeyEvent {
	enum modifierKeys { ctrl, alt, shift, super }

	enum extKeys {
		escape,
		insert, // equivalent to "Help" on Apple keyboards
		delete,
		home,
		end,
		pageUp,
		pageDown,
		up,
		down,
		left,
		right,
		f1, // F1..F12 are guaranteed to be consecutive
		f2,
		f3,
		f4,
		f5,
		f6,
		f7,
		f8,
		f9,
		f10,
		f11,
		f12,
		n0, // numpad keys; independent of Num Lock state
		n1, // N0..N9 are guaranteed to be consecutive
		n2,
		n3,
		n4,
		n5,
		n6,
		n7,
		n8,
		n9,
		nDot,
		nEnter,
		nAdd,
		nSubtract,
		nMultiply,
		nDivide
	}
}

export class UiAreaKeyEvent {
	constructor(key: number, extKey: number, modifier: string, modifiers: any,
				up: boolean);

	key: string;
	extKey: UiAreaKeyEvent.extKeys;
	modifier: UiAreaKeyEvent.modifierKeys;
	modifiers: number;
	up: number;

	
}



export const UiDialogs: {
	openFile(parent: UiWindow): string|null; saveFile(parent: UiWindow): string | null;
	msgBox(parent: UiWindow, title: string, description: string): void;
	msgBoxError(parent: UiWindow, title: string, description: string): void;
};


export namespace DrawBrush {
	enum brushType { solid, linearGradient, radialGradient }
}

export namespace DrawStrokeParams {
	enum lineCap { flat, round, square }

	enum lineJoin { miter, round, bevel }
}

/**
 * A draw brush
 */
export class DrawBrush {
	constructor();

	color: Color;

	type: DrawBrush.brushType;

	/**
	 * The gradient stops
	 */
	stops: BrushGradientStop[];

	/**
	 * Set the start position of the gradient
	 * (Radial gradients: the inner circle's center)
	 * @param pos - the coordinates
	 */
	start: Point;

	/**
	 * The end position of the gradient
	 * (Radial gradients: the outer circle's center)
	 */
	end: Point;

	/**
	 * The radius of the gradient's outer circle (radial gradients only)
	 */
	outerRadius: number;
}

declare enum fillMode { winding, alternate }

export class UiDrawPath {
	constructor(mode?: fillMode);

	addRectangle(x: number, y: number, width: number, height: number): void;

	newFigure(x: number, y: number): void;

	newFigureWithArc(xCenter: number, yCenter: number, radius: number, startAngle: number,
					 sweep: number, negative: number): void;

	lineTo(x: number, y: number): void;

	arcTo(xCenter: number, yCenter: number, radius: number, startAngle: number,
		  sweep: number, negative: boolean): void;

	bezierTo(c1x: number, c1y: number, c2x: number, c2y: number, endX: number,
			 endY: number): void;

	closeFigure(): void;

	end(): void;
}

export class DrawStrokeParams {

	thickness: number;
	cap: DrawStrokeParams.lineCap;
	join: DrawStrokeParams.lineJoin;
	miterLimit: number;

	dashes: number[];
	dashPhase: number;
}

export class UiDrawMatrix {
	constructor();

	setIdentity(): void;

	scale(xCenter: number, yCenter: number, x: number, y: number): void;
	translate(x: number, y: number): void;
	rotate(x: number, y: number, amount: number): void;
	skew(x: number, y: number, xAmount: number, yAmount: number): void;
	multiply(m: number): void;
	invertible(m: number): void;

	/**
	 * returns true it it worked
	 */
	invert(m: number): boolean;

	set(i: number, j: number, v: number): void;
	get(i: number, j: number): number;

	readonly 0: [number];
	readonly 1: [number];
	readonly 2: [number];
}

declare enum textAlign { left, center, right }

export class DrawTextLayout {
	constructor(str: AttributedString, font: FontDescriptor, width: number,
				align: textAlign);

	readonly extents: Size;
}

/**
 * A static text label.
 */
export class UiLabel extends UiControl {
	constructor(label?: string);

	text: any;
}

/**
 * A container that organizes children as labeled fields.
 */
export class UiForm extends UiControl {
	/**
	 * Create a new UiForm object.
	 */
	constructor();

	/**
	 * If true, the container inserts some space between children.
	 */
	padded: boolean;

	/**
	 * Append a new child control as the last field with the specified label.
	 * @param label - the text to use as label of the field.
	 * @param control - the control to add as child.
	 * @param stretchy - whether the control should fill all the available space.
	 */
	append(label: string, control: UiControl, stretchy?: boolean): void;

	/**
	 * Remove a child control at the specified position.
	 * @param index - the index of the control to remove
	 */
	deleteAt(index: number): void;
}

/**
 * A base class for text related entries.
 */
export abstract class UiEntryBase extends UiControl {
	/**
	 * Set or return the the content of the entry.
	 */
	text: string;

	/**
	 * Whether the user is allowed to change the entry's contents.
	 */
	readOnly: boolean;
	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry contents
	 * changed.
	 * @param callback - callback to execute when the event is fired.
	 */
	onChanged(callback: () => any): void;
}

/**
 * A simple, single line text entry control.
 */
export class UiEntry extends UiEntryBase {
	constructor();
}

/**
 * A multiline text entry.
 */
export class UiMultilineEntry extends UiControl {
	/**
	 * Create a new UiMultilineEntry object.
	 * @param wrapping - whether the multiline entry wrap text. Defaults to false.
	 */
	constructor(wrapping?: boolean);

	/**
	 * Set or return the the content of the multiline entry.
	 */
	text: string;

	/**
	 * Whether the user is allowed to change the entry's contents.
	 */
	readOnly: boolean;

	/**
	 * Append the specified text to the entry's contents.
	 * @param text - the text to append.
	 */
	append(text: string): void;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry's contents
	 * changed.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	onChanged(callback: () => any): void;
}

/**
 * A single line text entry control that hides the input, useful for passwords
 * and other sensible data.
 */
export class UiPasswordEntry extends UiEntryBase {
	/**
	 * Create a new UiPasswordEntry object.
	 */
	constructor();
}

/**
 * A single line text entry control to search text.
 */
export class UiSearchEntry extends UiEntryBase {
	/**
	 * Create a new UiSearchEntry object.
	 */
	constructor();
}

/**
 * Base class for vertical and horizontal boxes
 */
export abstract class UiBox extends UiControl {
	/**
	 * If true, the container inserts some space between children.
	 */
	padded: boolean;

	/**
	 * Append a new child control as the last child.
	 * @param control - the control to add as a child.
	 * @param stretchy - whever the control should fill all the available space.
	 */
	append(control: UiControl, stretchy?: boolean): void;

	/**
	 * Remove a child control at specified position.
	 * @param index - the index of the control to remove
	 */
	deleteAt(index: number): void;
}

/**
 * A container that stacks its chidren horizontally.
 */
export class UiHorizontalBox extends UiBox {
	constructor();
}

/**
 * A container that stacks its children vertically.
 */
export class UiVerticalBox extends UiBox {
	constructor();
}

/**
 * A container for a single control that provides a caption and visually groups
 * it's child.
 */
export class UiGroup extends UiControl {
	/**
	 * Create a new UiGroup object.
	 *
	 * @param title - text to show in Group title bar. Default is `''`
	 */
	constructor(title?: string);

	/**
	 * Set or return the text to show in group caption.
	 */
	title: string;

	/**
	 * Set the control to show in this group content area.
	 * UiGroup instances can contain only one control. If you need
	 * more, you have to use [Containers](containers.md).
	 *
	 * @param control - the control to add as child.
	 */
	setChild(control: UiControl): void;

	/**
	 * When true, an internal margin is added to the group.
	 */
	margined: boolean;
}

export namespace UiGrid {
	/**
	 * Enum defining the alignment of a control
	 */
	enum GridAlign { fill, start, center, end }

	/**
	 * Enum defining the position where to insert a control into a grid
	 */
	enum GridAt { leading, top, trailing, bottom }
}

/**
 * A powerful container that allow to specify size and position of each children.
 */
export class UiGrid extends UiControl {
	/**
	 * Create a new UiGrid object.
	 */
	constructor();

	/**
	 * If true, the container inserts some space between children.
	 */
	padded: boolean;

	/**
	 * Insert a new child control before specified control.
	 * @param child - the control to insert
	 * @param before - the control will be inserted before this position
	 * @param at      [description]
	 * @param xspan - How many columns the component takes off.
	 * @param yspan - How many rows the component takes off.
	 * @param hexpand - whether the component can expand horizontally.
	 * @param halign - whether the component is aligned with the other components in the
	 * column.
	 * @param vexpand - whether the component can expand vertically.
	 * @param valign - whether the component is aligned with the other components in the
	 * row.
	 */
	insertAt(child: UiControl, before: UiControl, at: UiGrid.GridAt, xspan: number,
			 yspan: number, hexpand: number, halign: UiGrid.GridAlign, vexpan,
			 valign: UiGrid.GridAlign): void;

	/**
	 * Insert a new child control.
	 *
	 * > UIGrid expand does not work correctly when both align horizontal and align
	 * vertical are set. You must choose one so libui knows which direction to expand.
	 *
	 * @param child - the control to add as child.
	 * @param left - What column the component resides in.
	 * @param top - What row the component resides in.
	 * @param xspan - How many columns the component takes off.
	 * @param yspan - How many rows the component takes off.
	 * @param hexpand - whether the component can expand horizontally.
	 * @param halign - whether the component is aligned with the other components in the
	 * column.
	 * @param vexpand - whether the component can expand vertically.
	 * @param valign - whether the component is aligned with the other components in the
	 * row.
	 */
	append(child: UiControl, left: number, top: number, xspan: number, yspan: number,
		   hexpand: number, halign: UiGrid.GridAlign, vexpand: number, valign: UiGrid.GridAlign): void;
}

/**
 * A container that show each chidren in a separate tab.
 */
export class UiTab extends UiControl {
	constructor();

	/**
	 * Return whether an internal margin is added to a page of the tab.
	 * @param index - the index of the page to check.
	 * @return `true` - whether the page has margins
	 */
	getMargined(index: number): boolean;

	/**
	 * Add an internal margin to a page of the Tab.
	 * @param index - the index of the page to set the margin on.
	 * @param value - whether to enable or disable the margin.
	 */
	setMargined(index: number, value: boolean): void;

	/**
	 * Append a new child control as last tab page.
	 * @param label - the text to show for the new page caption.
	 * @param control - the control to add as a child.
	 */
	append(label: string, control: UiControl): void;

	/**
	 * Insert a new child control before specified position.
	 * @param label - the text to show for the new page caption.
	 * @param before - the control will be inserted before this position
	 * @param control - the control to insert
	 */
	insertAt(label: string, before: number, control: UiControl): void;

	/**
	 * Return the total number of tab pages contained in the control.
	 */
	numPages(): number;

	/**
	 * Remove the tab and control at specified position.
	 * @param index - the index of the tab to remove.
	 */
	deleteAt(index: number): void;
}

/**
 * A simple button.
 */
export class UiButton extends UiControl {
	/**
	 * Create a new UiButton object.
	 */
	constructor(label?: string);

	/**
	 * Set or return the text of the button.
	 */
	text: string;

	/**
	 * Emitted when the button is clicked
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	onClicked(callback: () => any): void;
}

/**
 * A control that represents a group of single-choise options.
 */
export class UiRadioButtons extends UiControl {
	/**
	 * Number of items in this radio buttons set
	 */
	itemsCount: number;
	/**
	 * Create a new UiRadioButtons object.
	 */
	constructor();

	/**
	 * Return or set the currently selected item by index.
	 */
	selected: string;

	/**
	 * Append a new radio option as the last item with the specified text.
	 * @param text - the text to append.
	 */
	append(text: string): void;

	/**
	 * Add a listener to the `selected` event. Emitted whenever the selected option
	 * changes.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	onSelected(callback: () => void): void;
}

/**
 * A button that opens a color palette popup.
 */
export class UiColorButton extends UiControl {
	/**
	 * Create a new UiColorButton object.
	 */
	constructor();

	/**
	 * Set or return the ColorButton color value.
	 */
	color: Color;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the user
	 * changed the selected color.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	onChanged(callback: () => void): void;
}

/**
 * A button that opens a popup to choose a font.
 */
export class UiFontButton extends UiControl {
	/**
	 * Create a new UiFontButton object.
	 */
	constructor();

	/**
	 * Return the FontButton font value.
	 */
	readonly font: FontDescriptor;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the user changed the
	 * selected font.
	 *
	 * @param  {Function} callback - callback to execute when the event is fired.
	 */
	onChanged(callback: () => void): void;
}

/**
 * Horizontal slider to set numerical values.
 */
export class UiSlider extends UiControl {
	/**
	 * Create a new UiSlider object.
	 * @param min - minimum value of the slider. default to `0`
	 * @param max - maximum value of the slider. default to `100`
	 */
	constructor(min?: number, max?: number);

	/**
	 * Set or return the the content of the slider.
	 */
	value: number;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the slider value changed.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	onChanged(callback: () => void): void;
}

/**
 * An entry control for numerical values.
 */
export class UiSpinbox extends UiControl {
	/**
	 * Create a new UiSpinbox object.
	 * @param min - minimum value of the spinbox. defaults to `0`
	 * @param max - maximum value of the spinbox. defaults to `100`
	 */
	constructor(min?: number, max?: number);

	/**
	 * Set or return the the content of spinbox.
	 */
	value: number;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the spinbox value changed.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	onChanged(callback: () => void): void;
}

/**
 * A checkbox control.
 */
export class UiCheckbox extends UiControl {
	/**
	 * Create a new UiCheckbox object.
	 */
	constructor(label?: string);

	/**
	 * Set or return the text label for the checkbox.
	 */
	text: string;

	/**
	 * Whether the control is checked.
	 */
	checked: boolean;

	/**
	 * Add a listener to the `toggled` event. Emitted whenever the control
	 * `checked` state change.
	 * @param callback - callback to execute when the event is fired.
	 */
	onToggled(callback: () => any): void;
}

/**
 * A drop down combo box that allow list selection only.
 */
export class UiCombobox extends UiControl {
	/**
	 * Create a new UiCombobox object.
	 */
	constructor();

	/**
	 * Return or set the current selected item by index.
	 */
	selected: number;

	/**
	 * Append a new text item to the drop down list.
	 * @param text - the item to append.
	 */
	append(text: string): void;

	/**
	 * Add a listener to the `selected` event. Emitted whenever the selected
	 * item changes.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	onSelected(callback: () => any): void;
}

/**
 * A drop down combo box that allows to select an item from list or to specify a custom
 * value.
 */
export class UiEditableCombobox extends UiControl {
	/**
	 * Create a new UiEditableCombobox object.
	 */
	constructor();

	/**
	 * Return or set the current text.
	 */
	text: string;

	/**
	 * Append a new text item to the drop down list.
	 * @param text - the item to append.
	 */
	append(text: string): void;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the text (or item) changes.
	 *
	 * @param callback - callback to execute when the event is
	 * fired.
	 */
	onChanged(callback: () => any): void;
}

/**
 * Base class for vertical and horizontal separator
 */
export abstract class SeparatorBase extends UiControl {}

/**
 * A vertical line to visually separate controls.
 */
export class UiVerticalSeparator extends SeparatorBase {
	/**
	 * Create a new UiVerticalSeparator object.
	 */
	constructor();
}

/**
 * A horizontal line to visually separate controls.
 */
export class UiHorizontalSeparator extends SeparatorBase {
	/**
	 * Create a new UiHorizontalSeparator object.
	 */
	constructor();
}

/**
 * A base class for date/time related entries.
 */
export abstract class DateTimePickerBase extends UiControl {
	/**
	 * Set or return the date/time represented by the control.
	 */
	time: Date;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry contents changed.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	onChanged(callback: () => any): void;
}

/**
 * A control to set a date and time.
 */
export class UiDateTimePicker extends DateTimePickerBase {
	/**
	 * Create a new UiDateTimePicker object.
	 */
	constructor();
}

/**
 * A control to set a time.
 */
export class UiTimePicker extends DateTimePickerBase {
	/**
	 * Create a new UiTimePicker object.
	 */
	constructor();
}

/**
 * A control to set a date.
 */
export class UiDatePicker extends DateTimePickerBase {
	/**
	 * Create a new UiDatePicker object.
	 */
	constructor();
}

/**
 * Progress bar control.
 */
export class UiProgressBar extends UiControl {
	/**
	 * Create a new UiProgressBar object.
	 */
	constructor();

	/**
	 * The current position of the progress bar.
	 *
	 * Can be set to `-1` to create an indeterminate progress bar.
	 */
	value: number;
}

/**
 * The top bar on a window that can have multiple items.
 * The menu must be created before the first UiWindow for it to take effect.
 * It is made up of UiMenuItem instances.
 */
export class UiMenu {
	/**
	 * Create a new UiMenu object.
	 * @param caption - The caption of the menu.
	 */
	constructor(caption: string);

	/**
	 * Append a normal menu button.
	 * @param caption - The caption of the menu item.
	 * @return the new appended UiMenuItem
	 */
	appendItem(caption: string): UiMenuItem;

	/**
	 * Append a menu button with a checkable option.
	 * @param caption - The caption of the menu item.
	 * @return the new appended UiMenuItem
	 */
	appendCheckItem(caption: string): UiMenuItem;

	/**
	 * Append an OS-provided quit button.
	 * @return the new appended UiMenuItem
	 */
	appendQuitItem(): UiMenuItem;

	/**
	 * Append a OS-provided preferences button.
	 * @return the new appended UiMenuItem
	 */
	appendPreferencesItem(): UiMenuItem;

	/**
	 * Append an OS-provided about button.
	 * @return the new appended UiMenuItem
	 */
	appendAboutItem(): UiMenuItem;

	/**
	 * Append a separator between menu items.
	 * @return the new appended UiMenuItem
	 */
	appendSeparator(): UiMenuItem;
}

/**
 * A single button contained in a menu.
 */
export class UiMenuItem {
	/**
	 * Enable this menu item.
	 */
	enable(): void;

	/**
	 * Disable this menu item
	 */
	disable(): void;

	/**
	 * Register a callback for the click event of the menu item.
	 * @param callback - the function to register as callback for the event.
	 */
	onClicked(callback: () => void): void;

	/**
	 * If the item is created using appendCheckItem, then set
	 * whether it is checked or not.
	 */
	checked: boolean;
}
