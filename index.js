const libui = require(`${__dirname}/ui.node`);
const async_hooks = require('@creditkarma/async-hooks');
const EventLoop = libui.EventLoop;
delete libui.EventLoop;

let wakingup = false;
let asyncHook = null;

class Point {
	constructor(x, y) {
		this.x = x;
		this.y = y;
	}
}

class Color {
	constructor(r, g, b, a) {
		this.r = r;
		this.g = g;
		this.b = b;
		this.a = a;
	}
}

class Size {
	constructor(width, height) {
		this.width = width;
		this.height = height;
	}
}

module.exports = libui;
const {UiCheckbox} = require('./js/checkbox');
const {
	UiArea,
	UiAreaMouseEvent,
	UiAreaKeyEvent,
	AreaDrawParams,
	AreaDrawContext,
	DrawBrush,
	UiDrawPath,
	DrawStrokeParams,
	UiDrawMatrix,
	AreaDrawBrushGradient,
	BrushGradientStop,
	DrawTextLayout
} = require('./js/area');
const {UiBox} = require('./js/box');
const {SeparatorBase} = require('./js/separator-base');
const {UiControl} = require('./js/ui-control');
const {UiTable} = require('./js/table');
const {UiButton} = require('./js/button');
const {UiWindow} = require('./js/window');
const {UiSlider} = require('./js/slider');
const {UiForm} = require('./js/form');
const {UiLabel} = require('./js/label');
const {UiVerticalBox} = require('./js/vertical-box');
const {UiHorizontalBox} = require('./js/horizontal-box');
const {UiMultilineEntry} = require('./js/multiline-entry');
const {UiColorButton} = require('./js/color-button');
const {UiCombobox} = require('./js/combobox');
const {UiEditableCombobox} = require('./js/editable-combobox');
const {UiTimePicker} = require('./js/time-picker');
const {UiDatePicker} = require('./js/date-picker');
const {UiEntry} = require('./js/entry');
const {UiSearchEntry} = require('./js/search-entry');
const {UiPasswordEntry} = require('./js/password-entry');
const {UiDateTimePicker} = require('./js/date-time-picker');
const {UiGroup} = require('./js/group');
const {UiSpinbox} = require('./js/spinbox');
const {UiProgressBar} = require('./js/progress-bar');
const {UiRadioButtons} = require('./js/radio-buttons');
const {UiHorizontalSeparator} = require('./js/horizontal-separator');
const {UiVerticalSeparator} = require('./js/vertical-separator');
const {UiTab} = require('./js/tab');
const {UiGrid} = require('./js/grid');
const {UiEntryBase} = require('./js/entry-base');
const {UiMenu, UiMenuItem} = require('./js/menu');
const {UiFontButton} = require('./js/font-button');
const {FontDescriptor} = require('./js/font-descriptor');
const {FontAttribute} = require('./js/font-attribute');
const {AttributedString} = require('./js/font-string');
const {OpenTypeFeatures} = require('./js/font-opentype');
const {UiTableModel} = require('./js/table-model');
const {UiImage} = require('./js/image');
const fromMetadata = require('./js/table-model-from-metadata');

UiTableModel.fromMetadata = fromMetadata;
UiTableModel.ValueTypes = fromMetadata.ValueTypes;
UiTableModel.Fields = fromMetadata.Fields;

function applySetterGetter(...classConstructors) {
	for (const classConstructor of classConstructors) {
		const proto = classConstructor.prototype;
		const ownProperties = Object.getOwnPropertyNames(proto);
		for (const name of ownProperties) {
			const property = Object.getOwnPropertyDescriptor(proto, name);
			if (typeof property.get === 'function') {
				const getterName = 'get' + name[0].toUpperCase() + name.slice(1);
				Object.defineProperty(proto, getterName, {
					value: property.get,
					writable: true,
					enumerable: false,
					configurable: true
				});
				// console.log(`Defined ${getterName} on ${classConstructor.name}`);
			}

			if (typeof property.set === 'function') {
				const setterName = 'set' + name[0].toUpperCase() + name.slice(1);
				Object.defineProperty(proto, setterName, {
					value: property.set,
					writable: true,
					enumerable: false,
					configurable: true
				});
				// console.log(`Defined ${setterName} on ${classConstructor.name}`);
			}
		}
	}
}

function applySetterGetterAll(doSetter, ...classConstructors) {
	for (const classConstructor of classConstructors) {
		const proto = classConstructor.prototype;
		const ownProperties = Object.getOwnPropertyNames(new classConstructor());
		for (const name of ownProperties) {
			const getterName = 'get' + name[0].toUpperCase() + name.slice(1);
			Object.defineProperty(proto, getterName, {
				value: function() {
					return this[name];
				},
				writable: true,
				enumerable: false,
				configurable: true
			});
			// console.log(`Defined ${getterName} on ${classConstructor.name}`);

			if (doSetter) {
				const setterName = 'set' + name[0].toUpperCase() + name.slice(1);
				Object.defineProperty(proto, setterName, {
					value: function(v) {
						this[name] = v;
					},
					writable: true,
					enumerable: false,
					configurable: true
				});
				// console.log(`Defined ${setterName} on ${classConstructor.name}`);
			}
		}
	}
}

// Takes about 3.5ms:
applySetterGetter(
	UiImage, UiTableModel, UiTable, UiEntryBase, UiBox, SeparatorBase, UiControl, UiGrid,
	UiMenuItem, UiMenu, UiSpinbox, UiHorizontalSeparator, UiVerticalSeparator,
	UiRadioButtons, UiProgressBar, UiGroup, UiEntry, UiPasswordEntry, UiSearchEntry,
	UiEditableCombobox, UiTimePicker, UiDatePicker, UiDateTimePicker, UiCombobox,
	UiColorButton, UiCheckbox, UiWindow, UiButton, UiLabel, UiForm, UiSlider,
	UiMultilineEntry, UiHorizontalBox, UiVerticalBox, UiTab, UiArea, DrawBrush,
	BrushGradientStop, UiDrawPath, DrawStrokeParams, UiDrawMatrix, UiAreaKeyEvent,
	UiAreaMouseEvent, UiFontButton, FontDescriptor, FontAttribute, DrawTextLayout);
applySetterGetterAll(true, Point, Color, Size);
applySetterGetterAll(false, AreaDrawParams, UiAreaMouseEvent, UiAreaKeyEvent);

Object.assign(libui, {
	UiImage,
	UiTableModel,
	UiTable,
	UiFontButton,
	FontDescriptor,
	FontAttribute,
	AttributedString,
	OpenTypeFeatures,
	UiGrid,
	UiMenuItem,
	UiMenu,
	UiSpinbox,
	UiHorizontalSeparator,
	UiVerticalSeparator,
	UiRadioButtons,
	UiProgressBar,
	UiGroup,
	UiEntry,
	UiPasswordEntry,
	UiSearchEntry,
	UiEditableCombobox,
	UiTimePicker,
	UiDatePicker,
	UiDateTimePicker,
	UiCombobox,
	UiColorButton,
	UiCheckbox,
	UiWindow,
	UiButton,
	UiLabel,
	UiForm,
	UiSlider,
	UiMultilineEntry,
	UiHorizontalBox,
	UiVerticalBox,
	UiTab,
	UiArea,
	DrawBrush,
	BrushGradientStop,
	UiDrawPath,
	DrawStrokeParams,
	UiDrawMatrix,
	Point,
	Color,
	Size,
	UiAreaKeyEvent,
	UiAreaMouseEvent,
	DrawTextLayout,
	fillMode: UiDrawPath.fillMode,
	brushType: DrawBrush.type,
	modifierKeys: UiAreaKeyEvent.modifierKeys,
	extKeys: UiAreaKeyEvent.extKeys,
	lineCap: DrawStrokeParams.lineCap,
	lineJoin: DrawStrokeParams.lineJoin,
	textWeight: FontAttribute.weight,
	textItalic: FontAttribute.italic,
	textStretch: FontAttribute.stretch,
	textAttributeType: FontAttribute.type,
	textUnderline: FontAttribute.underline,
	textUnderlineColor: FontAttribute.underlineColor,
	textAlign: DrawTextLayout.align,
	UiDialogs: {
		openFile(parent) {
			return libui.Dialogs.openFile(parent.handle);
		},
		saveFile(parent) {
			return libui.Dialogs.saveFile(parent.handle);
		},
		msgBox(parent, title, description) {
			return libui.Dialogs.msgBox(parent.handle, title, description);
		},
		msgBoxError(parent, title, description) {
			return libui.Dialogs.msgBoxError(parent.handle, title, description);
		}
	}
});
libui.App.init();

libui.Area.init(UiAreaMouseEvent, UiAreaKeyEvent, AreaDrawParams, AreaDrawContext,
				BrushGradientStop, Color, Point, Size);

const onShouldQuit = libui.onShouldQuit = libui.App.onShouldQuit;
libui.Ui = {onShouldQuit};
libui.startTimer = libui.App.startTimer;
libui.startLoop = () => {
	asyncHook = async_hooks.createHook({init: initAsyncResource});

	// Allow callbacks of this AsyncHook instance to call. This is not an
	// implicit action after running the constructor, and must be explicitly run
	// to begin executing callbacks.
	asyncHook.enable();

	return new Promise((resolve, reject) => EventLoop.start(resolve));
};

libui.stopLoop = () => {
	// Allow callbacks of this AsyncHook instance to call. This is not an
	// implicit action after running the constructor, and must be explicitly run
	// to begin executing callbacks.
	asyncHook.disable();
	asyncHook = null;

	return new Promise((resolve, reject) => EventLoop.stop(resolve));
};

// This is called when a new async handle
// is created. It's used to signal the background
// thread to stop awaiting calls and upgrade it's list of handles
// it's awaiting for.
function initAsyncResource(asyncId, type, triggerAsyncId, resource) {
	if (wakingup) {
		return;
	}
	wakingup = true;
	setImmediate(() => {
		EventLoop.wakeupBackgroundThread();
		wakingup = false;
	});
}
