<a name="UiColorButton"></a>

## UiColorButton ⇐ <code>UiControl</code>
A button that opens a color palette popup.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiColorButton](#UiColorButton) ⇐ <code>UiControl</code>
    * [new UiColorButton()](#new_UiColorButton_new)
    * [.color](#UiColorButton+color) ⇒ <code>Object</code>
    * [.onChanged(callback)](#UiColorButton+onChanged) ⇒ <code>undefined</code>
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiColorButton_new"></a>

### new UiColorButton()
Create a new UiColorButton object.

<a name="UiColorButton+color"></a>

### uiColorButton.color ⇒ <code>Object</code>
Set or return the ColorButton color value.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  
<a name="UiColorButton+onChanged"></a>

### uiColorButton.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the user
changed the selected color.

**Kind**: instance method of [<code>UiColorButton</code>](#UiColorButton)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name=""></a>

### uiColorButton.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  
<a name=""></a>

### uiColorButton.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  
<a name=""></a>

### uiColorButton.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  
