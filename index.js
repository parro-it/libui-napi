const libui = require(`${__dirname}/node_libui.node`);
const async_hooks = require('async_hooks');
const EventLoop = libui.EventLoop;
delete libui.EventLoop;

let wakingup = false;
let asyncHook = null;

module.exports = libui;
const {UiButton} = require('./js/button');
const {UiWindow} = require('./js/window');
const {UiSlider} = require('./js/slider');
const {UiForm} = require('./js/form');
const {UiLabel} = require('./js/label');
const {UiVerticalBox} = require('./js/vertical-box');
const {UiHorizontalBox} = require('./js/horizontal-box');
const {UiMultilineEntry} = require('./js/multiline-entry');
Object.assign(libui, {UiWindow, UiButton, UiLabel, UiForm, UiSlider, UiMultilineEntry, UiHorizontalBox, UiVerticalBox});

libui.App.init();

libui.startLoop = () => {
	asyncHook = async_hooks.createHook({init: initAsyncResource});

	// Allow callbacks of this AsyncHook instance to call. This is not an implicit
	// action after running the constructor, and must be explicitly run to begin
	// executing callbacks.
	asyncHook.enable();

	EventLoop.start();
};

libui.stopLoop = () => {
	// Allow callbacks of this AsyncHook instance to call. This is not an implicit
	// action after running the constructor, and must be explicitly run to begin
	// executing callbacks.
	asyncHook.disable();
	asyncHook = null;

	EventLoop.stop();
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
