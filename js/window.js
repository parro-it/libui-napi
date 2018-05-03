const {
	windowNew,
	windowShow,
	windowOnClosing,
	windowClose,
	windowGetTitle,
	windowSetTitle,
	windowOnContentSizeChanged,
	windowGetContentSize,
	multilineEntryNew,
	windowSetChild
} = require('..');

/**
 * The UiWindow class is responsible to show and manage native windows.
 * UiWindow instance could contains only one control.
 * If you need more, you have to use [Containers](containers.md).
 */
class UiWindow {
	/**
	 * @param {string} title - text to show in window title bar.
	 * @param {number} width - width of window in pixels.
	 * @param {number} height -  height of window in pixels.
	 * @param {boolean} hasMenubar -  specify that this window has a menu bar. See [Menu](#menubar).
	 * @return {number} result of the sum value.
	 */
	constructor(title, width, height, hasMenubar) {
		this.handle = windowNew(title, width, height, hasMenubar);
	}
}
