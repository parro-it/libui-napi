const {
	UiDialogs,
	UiFontButton,
	UiGrid,
	UiSpinbox,
	UiSlider,
	UiProgressBar,
	UiCombobox,
	UiRadioButtons,
	UiEditableCombobox,
	UiCheckbox,
	UiWindow,
	UiHorizontalBox,
	UiMultilineEntry,
	UiVerticalBox,
	UiForm,
	UiGroup,
	UiEntry,
	UiSearchEntry,
	UiPasswordEntry,
	UiButton,
	UiTab,
	startLoop,
	stopLoop,
	onShouldQuit,
	UiLabel,
	UiHorizontalSeparator,
	UiVerticalSeparator,
	UiDatePicker,
	UiTimePicker,
	UiDateTimePicker,
	UiColorButton
} = require('..');

function* forEachChildren(children, parent) {
	for (const ctrl of children) {
		if (ctrl === null) {
			continue;
		}
		ctrl._parent = parent;

		let currentParent = parent;
		while (currentParent) {
			if (!currentParent.ids) {
				currentParent.ids = {};
			}
			if (ctrl.ids) {
				Object.assign(currentParent.ids, ctrl.ids);
			}
			if (ctrl.id) {
				currentParent.ids[ctrl.id] = ctrl;
			}
			currentParent = parent._parent;
		}

		yield ctrl;
	}
}

const appendAll =
	(children, parent) => {
		const allChild = forEachChildren(children, parent);
		for (const child of allChild) {
			const stretch =
				child.stretchy === undefined ? false : Boolean(child.stretchy);
			parent.append(child, stretch);
		}
	}

const appendTab =
	(children, parent, defaultLabel = '<empty label>') => {
		const allChild = forEachChildren(children, parent);
		for (const child of allChild) {
			child.label = child.label || defaultLabel;
			parent.append(child.label, child);
			parent.setMargined(parent.numPages() - 1, child.margined);
		}
	}

function wrapChildren(children) {
	const childs = Array.from(children);

	if (childs.length === 1) {
		return childs[0];
	}

	const box = new UiVerticalBox();
	box.padded = true;
	appendAll(childs, box);
	return box;
}

const EventHandler = Symbol('EventHandler');

function mkControl(Class, defaults, customConstructor) {
	const contructor = (props, children) => {
		if (!props) {
			props = {};
		}
		const ctrl = customConstructor ? customConstructor(props, children) : new Class();
		ctrl.props = props;
		if (props.id) {
			ctrl.id = props.id;
		}
		const handleChildren = defaults.handleChildren;
		for (const propName of Object.keys(defaults)) {
			if (propName === 'handleChildren' || propName === 'afterConstruction') {
				continue;
			}
			const defaultValue = defaults[propName];
			if (defaultValue === EventHandler) {
				if (props[propName]) {
					ctrl[propName](props[propName]);
				}
			} else if (props[propName] !== undefined) {
				ctrl[propName] = props[propName];
			} else {
				ctrl[propName] = defaults[propName];
			}
		}

		if (children && handleChildren) {
			handleChildren(ctrl, children);
		}

		if (defaults.afterConstruction) {
			defaults.afterConstruction(ctrl, props);
		}
		return ctrl;
	};

	return contructor;
}

const propsWithCommon = props => Object.assign(props, {
	left: 0,
	top: 0,
	xspan: 1,
	yspan: 1,
	hexpand: false,
	halign: UiGrid.align.fill,
	vexpand: false,
	valign: UiGrid.align.fill,
	enabled: true,
	visible: true,
	label: '',
	stretchy: false,
	margined: false
});

const tags = {
	window({
		title = '',
		width = 800,
		height = 600,
		margined = true,
		hasMenubar = false,
		fullscreen = false,
		borderless = false,
		onClosing = null
	},

		   children) {
		const win = new UiWindow(title, width, height, hasMenubar);
		win.margined = margined;
		win.fullscreen = fullscreen;
		win.borderless = borderless;

		if (onClosing) {
			win.onClosing(onClosing);
		}
		const child = wrapChildren(children);
		win.setChild(child);
		if (child.ids) {
			Object.assign(win, child.ids);
		}
		return win;
	},

	textarea:
		mkControl(UiMultilineEntry, propsWithCommon({
					  readOnly: false,
					  text: '',
					  onChanged: EventHandler,
					  handleChildren(ctrl, children) {
						  for (const child of children) {
							  ctrl.append(child);
						  }
					  }
				  }),
				  (props, children) => new UiMultilineEntry(props.wrapped || false)),

	hbox: mkControl(UiHorizontalBox, propsWithCommon({
						padded: false,
						handleChildren(ctrl, children) {
							appendAll(children, ctrl);
						}
					})),

	br() {
		return '\n';
	},

	vbox: mkControl(UiVerticalBox, propsWithCommon({
						padded: false,
						handleChildren(ctrl, children) {
							appendAll(children, ctrl, true);
						}
					})),

	tab: mkControl(UiTab, propsWithCommon({
					   margined: true,
					   handleChildren(ctrl, children) {
						   appendTab(children, ctrl);
					   }
				   })),

	group: mkControl(UiGroup, propsWithCommon({
						 title: '',
						 margined: true,
						 handleChildren(ctrl, children) {
							 const allChild = forEachChildren(children, ctrl);
							 ctrl.setChild(wrapChildren(allChild));
						 }
					 })),

	checkbox: mkControl(
		UiCheckbox, propsWithCommon({text: '', checked: false, onToggled: EventHandler})),

	form: mkControl(UiForm, propsWithCommon({
						padded: true,
						handleChildren(ctrl, children) {
							const allChild = forEachChildren(children, ctrl);
							for (const child of allChild) {
								const label = typeof child.label === undefined
												  ? defaultLabel
												  : String(child.label);
								const stretchy = typeof child.stretchy === undefined
													 ? false
													 : Boolean(child.stretchy);
								child.label = label;
								child.stretchy = stretchy;
								ctrl.append(label, child, stretchy);
							}
						}
					})),

	grid: mkControl(
		UiGrid, propsWithCommon({
			padded: true,
			handleChildren(ctrl, children) {
				const allChild = forEachChildren(children, ctrl);
				for (const child of [...allChild].filter(c => typeof c !== 'string')) {
					ctrl.append(child, child.left, child.top, child.xspan, child.yspan,
								child.hexpand, child.halign, child.vexpand, child.valign);
				}
			}
		})),

	button: mkControl(UiButton, propsWithCommon({text: '', onClicked: EventHandler})),

	entry: mkControl(
		UiEntry, propsWithCommon({readOnly: false, text: '', onChanged: EventHandler})),

	search:
		mkControl(UiSearchEntry,
				  propsWithCommon({readOnly: false, text: '', onChanged: EventHandler})),

	password:
		mkControl(UiPasswordEntry,
				  propsWithCommon({readOnly: false, text: '', onChanged: EventHandler})),

	label: mkControl(UiLabel, propsWithCommon({
						 text: '',
						 handleChildren(ctrl, children) {
							 ctrl.text = children.join('');
						 }
					 })),

	hseparator: mkControl(UiHorizontalSeparator, propsWithCommon({})),

	vseparator: mkControl(UiVerticalSeparator, propsWithCommon({})),

	date: mkControl(UiDatePicker,
					propsWithCommon({time: new Date(), onChanged: EventHandler})),

	time: mkControl(UiTimePicker,
					propsWithCommon({time: new Date(), onChanged: EventHandler})),

	datetime: mkControl(UiDateTimePicker,
						propsWithCommon({time: new Date(), onChanged: EventHandler})),

	spinbox: mkControl(UiSpinbox, propsWithCommon({value: 0, onChanged: EventHandler})),

	slider: mkControl(
		UiSlider, propsWithCommon({value: 0, min: 0, max: 100, onChanged: EventHandler})),

	progressbar: mkControl(UiProgressBar, propsWithCommon({value: 0, min: 0, max: 100})),

	combobox: mkControl(UiCombobox, propsWithCommon({
							items: [],
							selected: 0,
							onSelected: EventHandler,
							afterConstruction(ctrl, {items}) {
								for (const item of items) {
									ctrl.append(item);
								}
							}
						})),

	radio: mkControl(UiRadioButtons, propsWithCommon({
						 items: [],
						 selected: 0,
						 onSelected: EventHandler,
						 afterConstruction(ctrl, {items}) {
							 for (const item of items) {
								 ctrl.append(item);
							 }
						 }
					 })),

	editcombo: mkControl(UiEditableCombobox, propsWithCommon({
							 items: [],
							 text: '',
							 onChanged: EventHandler,
							 afterConstruction(ctrl, {items}) {
								 for (const item of items) {
									 ctrl.append(item);
								 }
							 }
						 })),

	colorpicker: mkControl(UiColorButton, propsWithCommon({
							   color: {r: 0, g: 0, b: 0, a: 1}

						   })),

	fontpicker: mkControl(UiFontButton, propsWithCommon({font: {}})),

};
/*
colorButton: mkControl(UiColorButton, {enabled: true, visible: true});

*/
exports.ui = function ui(tag, props, ...children) {
	if (typeof tags[tag] !== 'function') {
		throw new Error(`Unknown tag ${tag}.`);
	}
	return tags[tag](props, children);
};

exports.start = async function(win) {
	await startLoop();
	if (typeof win === 'function') {
		win = win();
	}
	const close = async () => {
		try {
			win.close();
			await stopLoop();
		} catch (err) {
			console.error(err);
		}
	};

	onShouldQuit(close);
	win.onClosing(close);
	win.show();
};
Object.assign(exports.ui, UiDialogs);

exports.ui.grid = {
	align: UiGrid.align,
	at: UiGrid.at
}
