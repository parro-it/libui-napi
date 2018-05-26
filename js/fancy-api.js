const {
	UiWindow,
	UiHorizontalBox,
	UiMultilineEntry,
	UiVerticalBox,
	UiGroup,
	startLoop,
	stopLoop,
	onShouldQuit
} = require('..');

function appendAll(children, parent, stretchy = false) {
	for (const ctrl of children) {
		const stretch = ctrl.stretchy === undefined ? stretchy : Boolean(ctrl.stretchy);
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
		parent.append(ctrl, stretch);
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
			} else if (props[propName] !== undefined &&
					   props[propName] !== defaultValue) {
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
	['text-area']: mkControl(UiMultilineEntry, {
		readOnly: false,
		enabled: true,
		text: '',
		visible: true,
		onChanged: EventHandler,
		handleChildren(ctrl, children) {
			for (const child of children) {
				ctrl.append(child);
			}
		}
	}),
	['h-box']: mkControl(UiHorizontalBox, {
		padded: false,
		enabled: true,
		visible: true,
		handleChildren(ctrl, children) {
			appendAll(children, ctrl, true);
		}
	}),
	br() {
		return '\n';
	},
	['v-box']: mkControl(UiVerticalBox, {
		padded: false,
		enabled: true,
		visible: true,
		handleChildren(ctrl, children) {
			appendAll(children, ctrl, true);
		}
	}),

	group: mkControl(UiGroup, {
		title: '',
		margined: true,
		enabled: true,
		visible: true,
		handleChildren(ctrl, children) {
			ctrl.setChild(wrapChildren(children));
		}
	})
};
/*
const entry = mkControl(
	libui.UiEntry,
	{readOnly: false, enabled: true, text: '', visible: true, onChanged: EventHandler});

const searchEntry = mkControl(
	libui.UiSearchEntry,
	{readOnly: false, enabled: true, text: '', visible: true, onChanged: EventHandler});

const passwordEntry = mkControl(
	libui.UiPasswordEntry,
	{readOnly: false, enabled: true, text: '', visible: true, onChanged: EventHandler});

const multilineEntry = mkControl(
	libui.UiMultilineEntry,
	{readOnly: false, enabled: true, text: '', visible: true, onChanged: EventHandler});

const label = mkControl(libui.UiLabel, {enabled: true, text: '', visible: true});

const separator = mkControl(libui.UiHorizontalSeparator, {enabled: true, visible: true});

const datePicker = mkControl(libui.UiDatePicker, {enabled: true, visible: true});

const timePicker = mkControl(libui.UiTimePicker, {enabled: true, visible: true});

const dateTimePicker = mkControl(libui.UiDateTimePicker, {enabled: true, visible: true});

const button = mkControl(
	libui.UiButton, {enabled: true, visible: true, text: '', onClicked: EventHandler});

const colorButton = mkControl(libui.UiColorButton, {enabled: true, visible: true});

const checkBox = mkControl(
	libui.UiCheckbox,
	{enabled: true, visible: true, text: '', checked: false, onToggled: EventHandler});

const spinbox = mkControl(
	libui.UiSpinbox, {enabled: true, visible: true, value: 0, onChanged: EventHandler});

const slider = mkControl(
	libui.UiSlider, {enabled: true, visible: true, value: 0, onChanged: EventHandler});

const progressBar =
	mkControl(libui.UiProgressBar, {enabled: true, visible: true, value: 0});

const combobox = (props, ...children) => {
	const ctrl = mkControl(
		libui.UiCombobox,
		{enabled: true, visible: true, selected: 0, onSelected: EventHandler})(props);

	for (const child of children) {
		ctrl.append(child);
	}

	return ctrl;
};

const radioButtons = (props, ...children) => {
	const ctrl = mkControl(
		libui.UiRadioButtons,
		{enabled: true, visible: true, selected: 0, onSelected: EventHandler})(props);

	for (const child of children) {
		ctrl.append(child);
	}

	return ctrl;
};

const editableCombobox = (props, ...children) => {
	const ctrl = mkControl(
		libui.UiEditableCombobox,
		{enabled: true, visible: true, text: '', onChanged: EventHandler})(props);

	for (const child of children) {
		ctrl.append(child);
	}

	return ctrl;
};

const tab = (props, ...children) => {
	const ctrl =
		mkControl(libui.UiTab, {enabled: true, visible: true, margined: true})(props);

	for (const child of children) {
		const title = child.props.tabTitle || '';
		ctrl.append(title, child);
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
			console.log('app closed...');
		} catch (err) {
			console.error(err);
		}
	};

	onShouldQuit(close);
	win.onClosing(close);
	win.show();
};