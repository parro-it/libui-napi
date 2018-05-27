const {
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
		if (ctrl.id) {

			let currentParent = parent;
			while (currentParent) {
				if (!currentParent.ids) {
					currentParent.ids = {};
				}
				if (ctrl.ids) {
					Object.assign(currentParent.ids, ctrl.ids);
				}
				currentParent.ids[ctrl.id] = ctrl;
				currentParent = parent._parent;
			}
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
			const label =
				typeof child.label === undefined ? defaultLabel : String(child.label);
			child.label = label;
			if (typeof child.margined === 'boolean') {
				ctrl.setMargined(ctrl.numPages() - 1, child.margined);
			}
			parent.append(label, child);
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

function mkControl(Class, defaults) {
	const contructor = (props, children) => {
		const ctrl = new Class();
		if (!props) {
			props = {};
		}
		ctrl.props = props;
		if (props.id) {
			ctrl.id = props.id;
		}
		const handleChildren = defaults.handleChildren;
		for (const propName of Object.keys(defaults)) {
			if (propName === 'handleChildren') {
				continue;
			}
			const defaultValue = defaults[propName];
			if (defaultValue === EventHandler) {
				if (props[propName]) {
					ctrl[propName](props[propName]);
				}
			} else if (props[propName] !== undefined) {
				ctrl[propName] = props[propName];
			}
		}
		if (props.stretchy !== undefined) {
			ctrl.stretchy = props.stretchy;
		}
		if (children && handleChildren)
			 {
				handleChildren(ctrl, children);
			}
		if (defaults.afterConstruction) {
			defaults.afterConstruction(ctrl, props);
		}
		return ctrl;
	};

	return contructor;
}

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

	textarea: mkControl(UiMultilineEntry, {
		readOnly: false,
		enabled: true,
		text: '',
		visible: true,
		label: '',
		stretchy: false,
		onChanged: EventHandler,
		handleChildren(ctrl, children) {
			for (const child of children) {
				ctrl.append(child);
			}
		}
	}),

	hbox: mkControl(UiHorizontalBox, {
		padded: false,
		enabled: true,
		visible: true,
		label: '',
		stretchy: false,
		handleChildren(ctrl, children) {
			appendAll(children, ctrl);
		}
	}),

	br() {
		return '\n';
	},

	vbox: mkControl(UiVerticalBox, {
		padded: false,
		enabled: true,
		visible: true,
		label: '',
		stretchy: false,
		handleChildren(ctrl, children) {
			appendAll(children, ctrl, true);
		}
	}),

	tab: mkControl(UiTab, {
		enabled: true,
		visible: true,
		margined: true,
		label: '',
		stretchy: false,
		handleChildren(ctrl, children) {
			appendTab(children, ctrl);
		}
	}),

	group: mkControl(UiGroup, {
		title: '',
		margined: true,
		enabled: true,
		visible: true,
		label: '',
		stretchy: false,
		handleChildren(ctrl, children) {
			const allChild = forEachChildren(children, ctrl);
			ctrl.setChild(wrapChildren(allChild));
		}
	}),

	checkbox: mkControl(UiCheckbox, {
		label: '',
		stretchy: false,
		enabled: true,
		visible: true,
		text: '',
		checked: false,
		onToggled: EventHandler
	}),

	form: mkControl(UiForm, {
		label: '',
		stretchy: false,
		padded: true,
		enabled: true,
		visible: true,
		handleChildren(ctrl, children) {
			const allChild = forEachChildren(children, ctrl);
			for (const child of allChild) {
				const label =
					typeof child.label === undefined ? defaultLabel : String(child.label);
				const stretchy =
					typeof child.stretchy === undefined ? false : Boolean(child.stretchy);
				child.label = label;
				child.stretchy = stretchy;
				ctrl.append(label, child, stretchy);
			}
		}
	}),

	button: mkControl(UiButton, {
		label: '',
		stretchy: false,
		enabled: true,
		visible: true,
		text: '',
		onClicked: EventHandler
	}),

	entry: mkControl(UiEntry, {
		label: '',
		stretchy: false,
		readOnly: false,
		enabled: true,
		text: '',
		visible: true,
		onChanged: EventHandler
	}),

	search: mkControl(UiSearchEntry, {
		label: '',
		stretchy: false,
		readOnly: false,
		enabled: true,
		text: '',
		visible: true,
		onChanged: EventHandler
	}),

	password: mkControl(UiPasswordEntry, {
		label: '',
		stretchy: false,
		readOnly: false,
		enabled: true,
		text: '',
		visible: true,
		onChanged: EventHandler
	}),

	textarea: mkControl(UiMultilineEntry, {
		label: '',
		stretchy: false,
		readOnly: false,
		enabled: true,
		text: '',
		visible: true,
		onChanged: EventHandler
	}),

	label: mkControl(UiLabel, {
		label: '',
		stretchy: false,
		enabled: true,
		text: '',
		visible: true,
		handleChildren(ctrl, children) {
			ctrl.text = children.join('');
		}
	}),

	hseparator: mkControl(UiHorizontalSeparator,
						  {label: '', stretchy: false, enabled: true, visible: true}),

	vseparator: mkControl(UiVerticalSeparator,
						  {label: '', stretchy: false, enabled: true, visible: true}),

	datePicker: mkControl(UiDatePicker, {
		label: '',
		stretchy: false,
		enabled: true,
		visible: true,
		time: new Date(),
		onChanged: EventHandler
	}),

	timePicker: mkControl(UiTimePicker, {
		label: '',
		stretchy: false,
		enabled: true,
		visible: true,
		time: new Date(),
		onChanged: EventHandler
	}),

	dateTimePicker: mkControl(UiDateTimePicker, {
		label: '',
		stretchy: false,
		enabled: true,
		visible: true,
		time: new Date(),
		onChanged: EventHandler
	}),

	spinbox: mkControl(UiSpinbox, {
		label: '',
		stretchy: false,
		enabled: true,
		visible: true,
		value: 0,
		onChanged: EventHandler
	}),

	slider: mkControl(UiSlider, {
		label: '',
		stretchy: false,
		enabled: true,
		visible: true,
		value: 0,
		min: 0,
		max: 100,
		onChanged: EventHandler
	}),

	progressbar: mkControl(UiProgressBar, {
		label: '',
		stretchy: false,
		enabled: true,
		visible: true,
		value: 0,
		min: 0,
		max: 100
	}),

	combobox: mkControl(UiCombobox, {
		label: '',
		stretchy: false,
		items: [],
		enabled: true,
		visible: true,
		selected: 0,
		onSelected: EventHandler,
		afterConstruction(ctrl, {items}) {
			for (const item of items) {
				ctrl.append(item);
			}
		}
	}),

	radio: mkControl(UiRadioButtons, {
		label: '',
		stretchy: false,
		items: [],
		enabled: true,
		visible: true,
		selected: 0,
		onSelected: EventHandler,
		afterConstruction(ctrl, {items}) {
			for (const item of items) {
				ctrl.append(item);
			}
		}
	}),

	editcombo: mkControl(UiEditableCombobox, {
		label: '',
		stretchy: false,
		items: [],
		enabled: true,
		visible: true,
		text: '',
		onChanged: EventHandler,
		afterConstruction(ctrl, {items}) {
			for (const item of items) {
				ctrl.append(item);
			}
		}
	})
};
/*
colorButton: mkControl(UiColorButton, {enabled: true, visible: true});

const editableCombobox = (props, ...children) => {
	const ctrl = mkControl(
		libui.UiEditableCombobox,
		{enabled: true, visible: true, text: '', onChanged: EventHandler})(props);

	for (const child of children) {
		ctrl.append(child);
	}

	return ctrl;
};

}
;
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