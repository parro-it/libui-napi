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
	maximum,
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
	ultraExpanded,
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
	features,
}

declare enum textUnderline { none, single, double, suggestion }

declare enum textUnderlineColor { custom, spelling, grammar, auxiliary }

/**
 * An object that contains information on a system font.
 */
export class FontDescriptor {

	/**
	 * Return the name of the font, e.g. "Helvetica".
	 */
	public readonly family: string;

	/**
	 * Return the size in point of the font.
	 */
	public readonly size: number;

	/**
	 * Return weight of the font.
	 */
	public readonly weight: textWeight;

	/**
	 * Return `1` if the font is italic, otherwise `0`.
	 */
	public readonly italic: textItalic;

	/**
	 * Return horizontal stretch value for the font.
	 */
	public readonly stretch: number;
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

	/* getter/setters for public properties */
	public getFamily(): string;
	public getSize(): number;
	public getWeight(): textWeight;
	public getItalic(): textItalic;
	public getStretch(): number;
}

/**
 * Stop Libui event loop
 */
export function stopLoop(): void;

/**
 * Start Libui event loop
 */
export function startLoop(): void;

export function startTimer(timeoutMs: number, callback: () => number): void;

export function onShouldQuit(cb: () => void): void;

type UnderlineColor = {
	type: textAttributeType; color: Color | null;
}|null;

export class FontAttribute {
	public static newFamily(v: string): FontAttribute;
	public static newSize(v: number): FontAttribute;
	public static newWeight(v: textWeight): FontAttribute;
	public static newItalic(v: textItalic): FontAttribute;
	public static newStretch(v: textStretch): FontAttribute;
	public static newColor(c: Color): FontAttribute;
	public static newBackgroundColor(c: Color): FontAttribute;
	public static newUnderline(v: textUnderline): FontAttribute;
	public static newUnderlineColor(type: textUnderlineColor,
									color?: Color): FontAttribute;
	public static newOTFeatures(otf: OpenTypeFeatures): FontAttribute;

	public static getFamily(): string|null;
	public static getSize(): number|null;
	public static getWeight(): textWeight|null;
	public static getItalic(): textItalic|null;
	public static getStretch(): textStretch|null;
	public static getColor(): Color|null;
	public static getUnderline(): textUnderline|null;
	public static getUnderlineColor(): UnderlineColor;
	public static getOTFeatures(): OpenTypeFeatures|null;
	constructor(other: FontAttribute);
}

export namespace FontAttribute {
type weight = textWeight;
type italic = textItalic;
type stretch = textStretch;
type underline = textUnderline;
type underlineColor = textUnderlineColor;
}

export class OpenTypeFeatures {
	public add(tag: string, value: number): void;
	public remove(tag: string): void;
	public get(tag: string): number;
	public forEach(cb: (feat: OpenTypeFeatures, str: string, val: number) => boolean):
		void;
	public clone(): OpenTypeFeatures;
}

export class Color {
	public r: number;
	public g: number;
	public b: number;
	public a: number;
	constructor(r: number, g: number, b: number, a: number);
	constructor(other: Color);

	/* getter/setters for public properties */
	public getR(): number;
	public setR(value: number): void;
	public getG(): number;
	public setG(value: number): void;
	public getB(): number;
	public setB(value: number): void;
	public getA(): number;
	public setA(value: number): void;
}

export class Point {
	public x: number;
	public y: number;
	constructor(x: number, y: number);
	constructor(other: Point);

	/* getter/setters for public properties */
	public getX(): number;
	public setX(value: number): void;
	public getY(): number;
	public setY(value: number): void;
}

export class Size {
	public w: number;
	public h: number;
	constructor(w: number, h: number);

	/* getter/setters for public properties */
	public getW(): number;
	public setW(value: number): void;
	public getH(): number;
	public setH(value: number): void;
}

export class BrushGradientStop {
	public pos: number;
	public color: Color;
	constructor(pos: number, color: Color);

	/* getter/setters for public properties */
	public getPos(): number;
	public setPos(value: number): void;
	public getColor(): Color;
	public setColor(value: Color): void;
}

export class AttributedString {
	constructor(str: string);
	public toString(): string;
	public toStringLen(): number;
	public appendAttributed(str: string, ...attribute: FontAttribute[]): void;
	public appendUnattributed(str: string): void;
	public insertAttributed(str: string, start: number,
							...attribute: FontAttribute[]): void;
	public insertUnattributed(str: string, at: number): void;
	public deleteString(start: number, end: number): void;
	public setAttribute(attr: FontAttribute, start: number, end: number): void;
	public forEach(cb: (str: AttributedString, attr: FontAttribute, start: number,
						end: number) => boolean): void;
	public numGraphemes(): number;
	public byteIndexToGrapheme(pos: number): number;
	public graphemeToByteIndex(pos: number): number;
}

/**
 * The UiWindow class is responsible for showing and managing native windows.
 * A UiWindow instance can contain only one child. If you need
 * more than one, you have to use [Containers](containers.md).
 */
export class UiWindow {

	/**
	 * Set or return the text to show in window title bar.
	 */
	public title: string;

	/**
	 * Set or return the size in pixel of the content area of the window
	 * (excluding the size of the window decoration). This mean that if you set window
	 * size to 0,0 you still see title bar and OS window buttons.
	 */
	public contentSize: {width: number; height: number};

	/**
	 * When true, an internal margin is added to the window.
	 */
	public margined: boolean;

	/**
	 * When true, the window is displayed without a border.
	 */
	public borderless: boolean;

	/**
	 * When true, the window is displayed in full screen mode.
	 */
	public fullscreen: boolean;
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

	/* getter/setters for public properties */
	public getTitle(): string;
	public setTitle(value: string): void;
	public getContentSize(): {width: number; height: number};
	public setContentSize(value: {width: number; height: number}): void;
	public getMargined(): boolean;
	public setMargined(value: boolean): void;
	public getBorderless(): boolean;
	public setBorderless(value: boolean): void;
	public getFullscreen(): boolean;
	public setFullscreen(value: boolean): void;

	/**
	 * Show the window.
	 * LibUi always returns null
	 */
	public show(): void;

	/**
	 * Add a listener to the `closing` event. This event is emitted when the OS
	 * window close button is clicked. You are responsible for closing the
	 * window in response to this event.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	public onClosing(callback: () => void): void;

	/**
	 * Add a listener to the `contentSizeChanged` event. This event is emitted
	 * when window content size change.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	public onContentSizeChanged(callback: () => void): void;

	/**
	 * Close the window.
	 */
	public close(): void;

	/**
	 * Set the control to show in this window content area.
	 * UiWindow instances can contain only one child. If you need
	 * more, you have to use [Containers](containers.md).
	 *
	 * @param control - the control to add as child.
	 * @param stretchy - whever the control should fill all the available space.
	 */
	public setChild(control: UiControl): void;
}

/**
 * Base class of all controls except UiWindow
 */
export abstract class UiControl {
	/**
	 * Set or return whether the control is enabled.
	 */
	public enabled: boolean;
	/**
	 * Set or return whether the control is visible.
	 */
	public visible: boolean;
	/**
	 * Set or return whether the control is a top level one.
	 */
	public toplevel: boolean;
	/**
	 * Create a new UiControl object.
	 */
	constructor(handle: any);

	/* getter/setters for public properties */
	public getEnabled(): boolean;
	public setEnabled(value: boolean): void;
	public getVisible(): boolean;
	public setVisible(value: boolean): void;
	public getToplevel(): boolean;
	public setToplevel(value: boolean): void;
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
	public queueRedrawAll(): void;

	/**
	 * Let the mouse move the window (only callable in the draw callback)
	 */
	public beginWindowMove(): void;

	/**
	 * Let the mouse resize the window (only callable in the draw callback)
	 * @param edge - the size which is held by the mouse
	 */
	public beginWindowResize(edge: number): void;

	public setSize(w: number, h: number): void;

	public scrollTo(x: number, y: number, w: number, h: number): void;
}

export class UiAreaMouseEvent {

	public readonly x: number;
	public readonly y: number;
	public readonly areaWidth: number;
	public readonly areaHeight: number;
	public readonly down: number;
	public readonly up: number;
	public readonly count: number;
	public readonly modifiers: number;
	public readonly held1To64: number;
	constructor(x: number, y: number, areaWidth: number, areaHeight: number,
				down: boolean, up: boolean, count: number, modifiers: any,
				held1To64: any);

	/* getter/setters for public properties */
	public getX(): number;
	public getY(): number;
	public getAreaWidth(): number;
	public getAreaHeight(): number;
	public getDown(): number;
	public getUp(): number;
	public getCount(): number;
	public getModifiers(): number;
	public getHeld1To64(): number;
}

export namespace UiAreaKeyEvent {
enum modifierKeys {
	ctrl,
	alt,
	shift,
	super,
}

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
	nDivide,
}
}

export class UiAreaKeyEvent {

	public key: string;
	public extKey: UiAreaKeyEvent.extKeys;
	public modifier: UiAreaKeyEvent.modifierKeys;
	public modifiers: number;
	public up: number;
	constructor(key: number, extKey: number, modifier: string, modifiers: any,
				up: boolean);

	/* getter/setters for public properties */
	public getKey(): string;
	public setKey(value: string): void;
	public getExtKey(): UiAreaKeyEvent.extKeys;
	public setExtKey(value: UiAreaKeyEvent.extKeys): void;
	public getModifier(): UiAreaKeyEvent.modifierKeys;
	public setModifier(value: UiAreaKeyEvent.modifierKeys): void;
	public getModifiers(): number;
	public setModifiers(value: number): void;
	public getUp(): number;
	public setUp(value: number): void;
}

export const UiDialogs: {
	openFile(parent: UiWindow): string|null; saveFile(parent: UiWindow): string | null;
	msgBox(parent: UiWindow, title: string, description: string): void;
	msgBoxError(parent: UiWindow, title: string, description: string): void;
};

export namespace DrawBrush {
enum brushType {
	solid,
	linearGradient,
	radialGradient,
}
}

export namespace DrawStrokeParams {
enum lineCap {
	flat,
	round,
	square,
}

enum lineJoin {
	miter,
	round,
	bevel,
}
}

/**
 * A draw brush
 */
export class DrawBrush {

	public color: Color;

	public type: DrawBrush.brushType;

	/**
	 * The gradient stops
	 */
	public stops: BrushGradientStop[];

	/**
	 * Set the start position of the gradient
	 * (Radial gradients: the inner circle's center)
	 * @param pos - the coordinates
	 */
	public start: Point;

	/**
	 * The end position of the gradient
	 * (Radial gradients: the outer circle's center)
	 */
	public end: Point;

	/**
	 * The radius of the gradient's outer circle (radial gradients only)
	 */
	public outerRadius: number;
	constructor();

	/* getter/setters for public properties */
	public getColor(): Color;
	public setColor(value: Color): void;
	public getType(): DrawBrush.brushType;
	public setType(value: DrawBrush.brushType): void;
	public getStops(): BrushGradientStop[];
	public setStops(value: BrushGradientStop[]): void;
	public getStart(): Point;
	public setStart(value: Point): void;
	public getEnd(): Point;
	public setEnd(value: Point): void;
	public getOuterRadius(): number;
	public setOuterRadius(value: number): void;
}

declare enum fillMode { winding, alternate }

export class UiDrawPath {
	constructor(mode?: fillMode);

	public addRectangle(x: number, y: number, width: number, height: number): void;

	public newFigure(x: number, y: number): void;

	public newFigureWithArc(xCenter: number, yCenter: number, radius: number,
							startAngle: number, sweep: number, negative: number): void;

	public lineTo(x: number, y: number): void;

	public arcTo(
		xCenter: number,
		yCenter: number,
		radius: number,
		startAngle: number,
		sweep: number,
		negative: boolean,
		): void;

	public bezierTo(c1x: number, c1y: number, c2x: number, c2y: number, endX: number,
					endY: number): void;

	public closeFigure(): void;

	public end(): void;
}

export class DrawStrokeParams {

	public thickness: number;
	public cap: DrawStrokeParams.lineCap;
	public join: DrawStrokeParams.lineJoin;
	public miterLimit: number;

	public dashes: number[];
	public dashPhase: number;

	/* getter/setters for public properties */
	public getThickness(): number;
	public setThickness(value: number): void;
	public getCap(): DrawStrokeParams.lineCap;
	public setCap(value: DrawStrokeParams.lineCap): void;
	public getJoin(): DrawStrokeParams.lineJoin;
	public setJoin(value: DrawStrokeParams.lineJoin): void;
	public getMiterLimit(): number;
	public setMiterLimit(value: number): void;
	public getDashes(): number[];
	public setDashes(value: number[]): void;
	public getDashPhase(): number;
	public setDashPhase(value: number): void;
}

export class UiDrawMatrix {

	public readonly 0: number;
	public readonly 1: number;
	public readonly 2: number;
	constructor();
	public get0(): number;
	public get1(): number;
	public get2(): number;

	public setIdentity(): void;

	public scale(xCenter: number, yCenter: number, x: number, y: number): void;
	public translate(x: number, y: number): void;
	public rotate(x: number, y: number, amount: number): void;
	public skew(x: number, y: number, xAmount: number, yAmount: number): void;
	public multiply(m: number): void;
	public invertible(m: number): void;

	/**
	 * returns true it it worked
	 */
	public invert(m: number): boolean;

	public set(i: number, j: number, v: number): void;
	public get(i: number, j: number): number;
}

declare enum textAlign { left, center, right }

export class DrawTextLayout {

	public readonly extents: Size;
	constructor(str: AttributedString, font: FontDescriptor, width: number,
				align: textAlign);
	public getExtents(): Size;
}

/**
 * A static text label.
 */
export class UiLabel extends UiControl {

	public text: string;
	constructor(label?: string);

	/* getter/setters for public properties */
	public getText(): string;
	public setText(value: string): void;
}

/**
 * A container that organizes children as labeled fields.
 */
export class UiForm extends UiControl {

	/**
	 * If true, the container inserts some space between children.
	 */
	public padded: boolean;
	/**
	 * Create a new UiForm object.
	 */
	constructor();

	/* getter/setters for public properties */
	public getPadded(): boolean;
	public setPadded(value: boolean): void;

	/**
	 * Append a new child control as the last field with the specified label.
	 * @param label - the text to use as label of the field.
	 * @param control - the control to add as child.
	 * @param stretchy - whether the control should fill all the available space.
	 */
	public append(label: string, control: UiControl, stretchy?: boolean): void;

	/**
	 * Remove a child control at the specified position.
	 * @param index - the index of the control to remove
	 */
	public deleteAt(index: number): void;
}

/**
 * A base class for text related entries.
 */
export abstract class UiEntryBase extends UiControl {
	/**
	 * Set or return the the content of the entry.
	 */
	public text: string;

	/**
	 * Whether the user is allowed to change the entry's contents.
	 */
	public readOnly: boolean;

	/* getter/setters for public properties */
	public getText(): string;
	public setText(value: string): void;
	public getReadOnly(): boolean;
	public setReadOnly(value: boolean): void;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry contents
	 * changed.
	 * @param callback - callback to execute when the event is fired.
	 */
	public onChanged(callback: () => any): void;
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
	 * Set or return the the content of the multiline entry.
	 */
	public text: string;

	/**
	 * Whether the user is allowed to change the entry's contents.
	 */
	public readOnly: boolean;
	/**
	 * Create a new UiMultilineEntry object.
	 * @param wrapping - whether the multiline entry wrap text. Defaults to false.
	 */
	constructor(wrapping?: boolean);

	/* getter/setters for public properties */
	public getText(): string;
	public setText(value: string): void;
	public getReadOnly(): boolean;
	public setReadOnly(value: boolean): void;

	/**
	 * Append the specified text to the entry's contents.
	 * @param text - the text to append.
	 */
	public append(text: string): void;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry's contents
	 * changed.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	public onChanged(callback: () => any): void;
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
	public padded: boolean;

	/* getter/setters for public properties */
	public getPadded(): boolean;
	public setPadded(value: boolean): void;

	/**
	 * Append a new child control as the last child.
	 * @param control - the control to add as a child.
	 * @param stretchy - whever the control should fill all the available space.
	 */
	public append(control: UiControl, stretchy?: boolean): void;

	/**
	 * Remove a child control at specified position.
	 * @param index - the index of the control to remove
	 */
	public deleteAt(index: number): void;
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
	 * Set or return the text to show in group caption.
	 */
	public title: string;

	/**
	 * When true, an internal margin is added to the group.
	 */
	public margined: boolean;
	/**
	 * Create a new UiGroup object.
	 *
	 * @param title - text to show in Group title bar. Default is `''`
	 */
	constructor(title?: string);

	/* getter/setters for public properties */
	public getTitle(): string;
	public setTitle(value: string): void;
	public getMargined(): boolean;
	public setMargined(value: boolean): void;

	/**
	 * Set the control to show in this group content area.
	 * UiGroup instances can contain only one control. If you need
	 * more, you have to use [Containers](containers.md).
	 *
	 * @param control - the control to add as child.
	 */
	public setChild(control: UiControl): void;
}

export namespace UiGrid {
/**
 * Enum defining the alignment of a control
 */
enum GridAlign {
	fill,
	start,
	center,
	end,
}

/**
 * Enum defining the position where to insert a control into a grid
 */
enum GridAt {
	leading,
	top,
	trailing,
	bottom,
}
}

/**
 * A powerful container that allow to specify size and position of each children.
 */
export class UiGrid extends UiControl {

	/**
	 * If true, the container inserts some space between children.
	 */
	public padded: boolean;

	/**
	 * Create a new UiGrid object.
	 */
	constructor();

	/* getter/setters for public properties */
	public getPadded(): boolean;
	public setPadded(value: boolean): void;

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
	public insertAt(child: UiControl, before: UiControl, at: UiGrid.GridAt, xspan: number,
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
	public append(
		child: UiControl,
		left: number,
		top: number,
		xspan: number,
		yspan: number,
		hexpand: number,
		halign: UiGrid.GridAlign,
		vexpand: number,
		valign: UiGrid.GridAlign,
		): void;
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
	public getMargined(index: number): boolean;

	/**
	 * Add an internal margin to a page of the Tab.
	 * @param index - the index of the page to set the margin on.
	 * @param value - whether to enable or disable the margin.
	 */
	public setMargined(index: number, value: boolean): void;

	/**
	 * Append a new child control as last tab page.
	 * @param label - the text to show for the new page caption.
	 * @param control - the control to add as a child.
	 */
	public append(label: string, control: UiControl): void;

	/**
	 * Insert a new child control before specified position.
	 * @param label - the text to show for the new page caption.
	 * @param before - the control will be inserted before this position
	 * @param control - the control to insert
	 */
	public insertAt(label: string, before: number, control: UiControl): void;

	/**
	 * Return the total number of tab pages contained in the control.
	 */
	public numPages(): number;

	/**
	 * Remove the tab and control at specified position.
	 * @param index - the index of the tab to remove.
	 */
	public deleteAt(index: number): void;
}

/**
 * A simple button.
 */
export class UiButton extends UiControl {

	/**
	 * Set or return the text of the button.
	 */
	public text: string;
	/**
	 * Create a new UiButton object.
	 */
	constructor(label?: string);

	/* getter/setters for public properties */
	public getText(): string;
	public setText(value: string): void;

	/**
	 * Emitted when the button is clicked
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	public onClicked(callback: () => any): void;
}

/**
 * A control that represents a group of single-choise options.
 */
export class UiRadioButtons extends UiControl {
	/**
	 * Number of items in this radio buttons set
	 */
	public itemsCount: number;

	/**
	 * Return or set the currently selected item by index.
	 */
	public selected: number;

	/**
	 * Create a new UiRadioButtons object.
	 */
	constructor();

	/* getter/setters for public properties */
	public getItemsCount(): number;
	public setItemsCount(value: number): void;
	public getSelected(): number;
	public setSelected(value: number): void;

	/**
	 * Append a new radio option as the last item with the specified text.
	 * @param text - the text to append.
	 */
	public append(text: string): void;

	/**
	 * Add a listener to the `selected` event. Emitted whenever the selected option
	 * changes.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	public onSelected(callback: () => void): void;
}

/**
 * A button that opens a color palette popup.
 */
export class UiColorButton extends UiControl {

	/**
	 * Set or return the ColorButton color value.
	 */
	public color: Color;
	/**
	 * Create a new UiColorButton object.
	 */
	constructor();

	/* getter/setters for public properties */
	public getColor(): Color;
	public setColor(value: Color): void;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the user
	 * changed the selected color.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	public onChanged(callback: () => void): void;
}

/**
 * A button that opens a popup to choose a font.
 */
export class UiFontButton extends UiControl {

	/**
	 * Return the FontButton font value.
	 */
	public readonly font: FontDescriptor;
	/**
	 * Create a new UiFontButton object.
	 */
	constructor();

	/* getter/setters for public properties */
	public getFont(): FontDescriptor;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the user changed the
	 * selected font.
	 *
	 * @param  {Function} callback - callback to execute when the event is fired.
	 */
	public onChanged(callback: () => void): void;
}

/**
 * Horizontal slider to set numerical values.
 */
export class UiSlider extends UiControl {

	/**
	 * Set or return the the content of the slider.
	 */
	public value: number;
	/**
	 * Create a new UiSlider object.
	 * @param min - minimum value of the slider. default to `0`
	 * @param max - maximum value of the slider. default to `100`
	 */
	constructor(min?: number, max?: number);

	/* getter/setters for public properties */
	public getValue(): number;
	public setValue(value: number): void;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the slider value changed.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	public onChanged(callback: () => void): void;
}

/**
 * An entry control for numerical values.
 */
export class UiSpinbox extends UiControl {

	/**
	 * Set or return the the content of spinbox.
	 */
	public value: number;

	/**
	 * Create a new UiSpinbox object.
	 * @param min - minimum value of the spinbox. defaults to `0`
	 * @param max - maximum value of the spinbox. defaults to `100`
	 */
	constructor(min?: number, max?: number);

	/* getter/setters for public properties */
	public getValue(): number;
	public setValue(value: number): void;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the spinbox value changed.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	public onChanged(callback: () => void): void;
}

/**
 * A checkbox control.
 */
export class UiCheckbox extends UiControl {

	/**
	 * Set or return the text label for the checkbox.
	 */
	public text: string;

	/**
	 * Whether the control is checked.
	 */
	public checked: boolean;
	/**
	 * Create a new UiCheckbox object.
	 */
	constructor(label?: string);

	/* getter/setters for public properties */
	public getText(): string;
	public setText(value: string): void;
	public getChecked(): boolean;
	public setChecked(value: boolean): void;

	/**
	 * Add a listener to the `toggled` event. Emitted whenever the control
	 * `checked` state change.
	 * @param callback - callback to execute when the event is fired.
	 */
	public onToggled(callback: () => any): void;
}

/**
 * A drop down combo box that allow list selection only.
 */
export class UiCombobox extends UiControl {

	/**
	 * Return or set the current selected item by index.
	 */
	public selected: number;
	/**
	 * Create a new UiCombobox object.
	 */
	constructor();

	/* getter/setters for public properties */
	public getSelected(): number;
	public setSelected(value: number): void;

	/**
	 * Append a new text item to the drop down list.
	 * @param text - the item to append.
	 */
	public append(text: string): void;

	/**
	 * Add a listener to the `selected` event. Emitted whenever the selected
	 * item changes.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	public onSelected(callback: () => void): void;
}

/**
 * A drop down combo box that allows to select an item from list or to specify a custom
 * value.
 */
export class UiEditableCombobox extends UiControl {

	/**
	 * Return or set the current text.
	 */
	public text: string;
	/**
	 * Create a new UiEditableCombobox object.
	 */
	constructor();

	/* getter/setters for public properties */
	public getText(): string;
	public setText(value: string): void;

	/**
	 * Append a new text item to the drop down list.
	 * @param text - the item to append.
	 */
	public append(text: string): void;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the text (or item) changes.
	 *
	 * @param callback - callback to execute when the event is
	 * fired.
	 */
	public onChanged(callback: () => void): void;
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
	public time: Date;

	/* getter/setters for public properties */
	public getTime(): Date;
	public setTime(value: Date): void;

	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry contents changed.
	 *
	 * @param callback - callback to execute when the event is fired.
	 */
	public onChanged(callback: () => void): void;
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
	 * The current position of the progress bar.
	 *
	 * Can be set to `-1` to create an indeterminate progress bar.
	 */
	public value: number;
	/**
	 * Create a new UiProgressBar object.
	 */
	constructor();

	/* getter/setters for public properties */
	public getValue(): number;
	public setValue(value: number): void;
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
	public appendItem(caption: string): UiMenuItem;

	/**
	 * Append a menu button with a checkable option.
	 * @param caption - The caption of the menu item.
	 * @return the new appended UiMenuItem
	 */
	public appendCheckItem(caption: string): UiMenuItem;

	/**
	 * Append an OS-provided quit button.
	 * @return the new appended UiMenuItem
	 */
	public appendQuitItem(): UiMenuItem;

	/**
	 * Append a OS-provided preferences button.
	 * @return the new appended UiMenuItem
	 */
	public appendPreferencesItem(): UiMenuItem;

	/**
	 * Append an OS-provided about button.
	 * @return the new appended UiMenuItem
	 */
	public appendAboutItem(): UiMenuItem;

	/**
	 * Append a separator between menu items.
	 * @return the new appended UiMenuItem
	 */
	public appendSeparator(): UiMenuItem;
}

/**
 * A single button contained in a menu.
 */
export class UiMenuItem {
	/**
	 * If the item is created using appendCheckItem, then set
	 * whether it is checked or not.
	 */
	public checked: boolean;

	/* getter/setters for public properties */
	public getChecked(): boolean;
	public setChecked(value: boolean): void;

	/**
	 * Enable this menu item.
	 */
	public enable(): void;

	/**
	 * Disable this menu item
	 */
	public disable(): void;

	/**
	 * Register a callback for the click event of the menu item.
	 * @param callback - the function to register as callback for the event.
	 */
	public onClicked(callback: () => void): void;
}
