<a name="UiFontButton"></a>

## UiFontButton
A button that opens a popup to choose a font.

**Kind**: global class  

* [UiFontButton](#UiFontButton)
    * [new UiFontButton()](#new_UiFontButton_new)
    * [.font](#UiFontButton+font) ⇒ <code>FontDescriptor</code>
    * [.onChanged(callback)](#UiFontButton+onChanged) ⇒ <code>undefined</code>

<a name="new_UiFontButton_new"></a>

### new UiFontButton()
Create a new UiFontButton object.

<a name="UiFontButton+font"></a>

### uiFontButton.font ⇒ <code>FontDescriptor</code>
return the FontButton font value.

**Kind**: instance property of [<code>UiFontButton</code>](#UiFontButton)  
<a name="UiFontButton+onChanged"></a>

### uiFontButton.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the user
changed the selected font.

**Kind**: instance method of [<code>UiFontButton</code>](#UiFontButton)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

