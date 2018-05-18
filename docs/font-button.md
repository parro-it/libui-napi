<a name="UiFontButton"></a>

## UiFontButton ⇐ <code>UiControl</code>
A button that opens a popup to choose a font.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiFontButton](#UiFontButton) ⇐ <code>UiControl</code>
    * [new UiFontButton()](#new_UiFontButton_new)
    * [.font](#UiFontButton+font) ⇒ <code>FontDescriptor</code>
    * [.onChanged(callback)](#UiFontButton+onChanged) ⇒ <code>undefined</code>
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiFontButton_new"></a>

### new UiFontButton()
Create a new UiFontButton object.

<a name="UiFontButton+font"></a>

### uiFontButton.font ⇒ <code>FontDescriptor</code>
Return the FontButton font value.

**Kind**: instance property of [<code>UiFontButton</code>](#UiFontButton)  
<a name="UiFontButton+onChanged"></a>

### uiFontButton.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the user
changed the selected font.

**Kind**: instance method of [<code>UiFontButton</code>](#UiFontButton)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name=""></a>

### uiFontButton.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiFontButton</code>](#UiFontButton)  
<a name=""></a>

### uiFontButton.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiFontButton</code>](#UiFontButton)  
<a name=""></a>

### uiFontButton.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiFontButton</code>](#UiFontButton)  
