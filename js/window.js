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
 * UiWindow instance could contains only one child control. If you need
 * more than one, you have to use [Containers](containers.md).
 */
class UiWindow {
	/**
	 * Create a new UiWindow object.
	 *
	 * @param {string} title - text to show in window title bar.
	 * @param {number} width - width of window in pixels.
	 * @param {number} height -  height of window in pixels.
	 * @param {boolean} hasMenubar - specify that this window has a menu bar. See [Menu](#menubar).
	 * @return {UiWindow} new instance.
	 */
	constructor(title, width, height, hasMenubar) {
		this.handle = windowNew(title, width, height, hasMenubar);
	}

	/**
	 * Show the window.
	 *
	 * @return {undefined}
	 */
	show() {

	}

	/**
	 * Add a listener to the `closing` event. This event is emitted when the OS window close
	 * button is clicked. You are responsible to close the window in response to this event.
	 *
	 * @param  {Function} callback - callback to execute when the event is fired.
	 * @return {undefined}
	 */
	onClosing(callback) {

	}

	/**
	 * Add a listener to the `contentSizeChanged` event. This event is emitted when window
	 * content size change.
	 *
	 * @param  {Function} callback - callback to execute when the event is fired.
	 * @return {undefined}
	 */
	onContentSizeChanged(callback) {

	}

	/**
	 * Close the window.
	 *
	 * @return {undefined}
	 */
	close() {

	}

	/**
	 * Set or return the text to show in window title bar.
	 *
	 * @return {string}
	 */
	get title() {

	}

	set title(val) {

	}

	/**
	 * Set or return the size in pixel of the content area of the window.
	 * Window decoration size are excluded. This mean that if you set window
	 * size to 0,0 you still see title bar and OS window buttons.
	 *
	 * @return {{width: number, height: number}}
	 */
	get contentSize() {

	}

	set contentSize(val) {

	}

	set child(val) {

	}

	/**
	 * Set or return the control to show in this window content area.
	 * UiWindow instances can contain only one control. If you need
	 * more, you have to use [Containers](containers.md).
	 *
	 * @return {UiControl}
	 */
	get child() {

	}
}
