const {Window} = require('..');

/**
 * The UiWindow class is responsible for showing and managing native windows.
 * A UiWindow instance can contain only one child. If you need
 * more than one, you have to use [Containers](containers.md).
 */
class UiWindow {
	/**
	 * Create a new UiWindow object.
	 *
	 * @param {string} title - text to show in window title bar.
	 * @param {number} width - width of window in pixels.
	 * @param {number} height -  height of window in pixels.
	 * @param {boolean} hasMenubar - whether this window has a menu bar.
	 * See [Menu](#menubar).
	 * @return {UiWindow} new instance.
	 */
	constructor(title, width, height, hasMenubar) {
		this.handle = Window.create(String(title), width, height, Boolean(hasMenubar));
	}

	/**
	 * Show the window.
	 *
	 */
	show() {
		return Window.show(this.handle);
	}

	/**
	 * Add a listener to the `closing` event. This event is emitted when the OS
	 * window close button is clicked. You are responsible for closing the
	 * window in response to this event.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onClosing(callback) {
		Window.onClosing(this.handle, callback);
	}

	/**
	 * Add a listener to the `contentSizeChanged` event. This event is emitted
	 * when window content size change.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onContentSizeChanged(callback) {
		Window.onContentSizeChanged(this.handle, callback);
	}

	/**
	 * Close the window.
	 *
	 */
	close() {
		Window.close(this.handle);
	}

	/**
	 * Set or return the text to show in window title bar.
	 *
	 * @return {string}
	 */
	get title() {
		return Window.getTitle(this.handle);
	}

	set title(value) {
		Window.setTitle(this.handle, String(value));
	}

	/**
	 * Set or return the size in pixel of the content area of the window
	 * (excluding the size of the window decoration). This mean that if you set window
	 * size to 0,0 you still see title bar and OS window buttons.
	 *
	 * @return {{width: number, height: number}}
	 */
	get contentSize() {
		return Window.getContentSize(this.handle);
	}

	set contentSize({width, height}) {
		Window.setContentSize(this.handle, width, height);
	}

	/**
	 * Set the control to show in this window content area.
	 * UiWindow instances can contain only one child. If you need
	 * more, you have to use [Containers](containers.md).
	 *
	 * @param {UiControl} control - the control to add as child.
	 * @param {boolean} stretchy - whever the control should fill all the
	 * available space.
	 */
	setChild(control, stretchy) {
		Window.setChild(this.handle, control.handle, Boolean(stretchy));
	}

	/**
	 * When true, an internal margin is added to the window.
	 *
	 * @return {boolean}
	 */
	get margined() {
		return Window.getMargined(this.handle);
	}

	set margined(value) {
		Window.setMargined(this.handle, Boolean(value));
	}

	/**
	 * When true, the window is displayed without a border.
	 *
	 * @return {boolean}
	 */
	get borderless() {
		return Window.getBorderless(this.handle);
	}

	set borderless(value) {
		Window.setBorderless(this.handle, Boolean(value));
	}

	/**
	 * When true, the window is displayed in full screen mode.
	 *
	 * @return {boolean}
	 */
	get fullscreen() {
		return Window.getFullscreen(this.handle);
	}

	set fullscreen(value) {
		Window.setFullscreen(this.handle, Boolean(value));
	}
}

module.exports = {UiWindow};
