<a name="UiWindow"></a>

## UiWindow
The UiWindow class is responsible to show and manage native windows.
UiWindow instance could contains only one child control. If you need
more than one, you have to use [Containers](containers.md).

**Kind**: global class  

* [UiWindow](#UiWindow)
    * [new UiWindow(title, width, height, hasMenubar)](#new_UiWindow_new)
    * [.title](#UiWindow+title) ⇒ <code>string</code>
    * [.contentSize](#UiWindow+contentSize) ⇒ <code>Object</code>
    * [.child](#UiWindow+child) ⇒ <code>UiControl</code>
    * [.show()](#UiWindow+show) ⇒ <code>undefined</code>
    * [.onClosing(callback)](#UiWindow+onClosing) ⇒ <code>undefined</code>
    * [.onContentSizeChanged(callback)](#UiWindow+onContentSizeChanged) ⇒ <code>undefined</code>
    * [.close()](#UiWindow+close) ⇒ <code>undefined</code>

<a name="new_UiWindow_new"></a>

### new UiWindow(title, width, height, hasMenubar)
Create a new UiWindow object.


| Param | Type | Description |
| --- | --- | --- |
| title | <code>string</code> | text to show in window title bar. |
| width | <code>number</code> | width of window in pixels. |
| height | <code>number</code> | height of window in pixels. |
| hasMenubar | <code>boolean</code> | specify that this window has a menu bar. See [Menu](#menubar). |

<a name="UiWindow+title"></a>

### uiWindow.title ⇒ <code>string</code>
Set or return the text to show in window title bar.

**Kind**: instance property of [<code>UiWindow</code>](#UiWindow)  
<a name="UiWindow+contentSize"></a>

### uiWindow.contentSize ⇒ <code>Object</code>
Set or return the size in pixel of the content area of the window.
Window decoration size are excluded. This mean that if you set window
size to 0,0 you still see title bar and OS window buttons.

**Kind**: instance property of [<code>UiWindow</code>](#UiWindow)  
<a name="UiWindow+child"></a>

### uiWindow.child ⇒ <code>UiControl</code>
Set or return the control to show in this window content area.
UiWindow instances can contain only one control. If you need
more, you have to use [Containers](containers.md).

**Kind**: instance property of [<code>UiWindow</code>](#UiWindow)  
<a name="UiWindow+show"></a>

### uiWindow.show() ⇒ <code>undefined</code>
Show the window.

**Kind**: instance method of [<code>UiWindow</code>](#UiWindow)  
<a name="UiWindow+onClosing"></a>

### uiWindow.onClosing(callback) ⇒ <code>undefined</code>
Add a listener to the `closing` event. This event is emitted when the OS window close
button is clicked. You are responsible to close the window in response to this event.

**Kind**: instance method of [<code>UiWindow</code>](#UiWindow)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name="UiWindow+onContentSizeChanged"></a>

### uiWindow.onContentSizeChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `contentSizeChanged` event. This event is emitted when window
content size change.

**Kind**: instance method of [<code>UiWindow</code>](#UiWindow)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name="UiWindow+close"></a>

### uiWindow.close() ⇒ <code>undefined</code>
Close the window.

**Kind**: instance method of [<code>UiWindow</code>](#UiWindow)  
