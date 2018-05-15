<a name="UiCheckbox"></a>

## UiCheckbox ⇐ <code>UiControl</code>
A checkbox control.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiCheckbox](#UiCheckbox) ⇐ <code>UiControl</code>
    * [new UiCheckbox()](#new_UiCheckbox_new)
    * [.text](#UiCheckbox+text) ⇒ <code>string</code>
    * [.checked](#UiCheckbox+checked) ⇒ <code>boolean</code>
    * [.onToggled(callback)](#UiCheckbox+onToggled) ⇒ <code>undefined</code>
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiCheckbox_new"></a>

### new UiCheckbox()
Create a new UiCheckbox object.

<a name="UiCheckbox+text"></a>

### uiCheckbox.text ⇒ <code>string</code>
Set or return the text label for the checkbox.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  
<a name="UiCheckbox+checked"></a>

### uiCheckbox.checked ⇒ <code>boolean</code>
Whether the control is checked.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  
<a name="UiCheckbox+onToggled"></a>

### uiCheckbox.onToggled(callback) ⇒ <code>undefined</code>
Add a listener to the `toggled` event. Emitted whenever the control
`checked` state change.

**Kind**: instance method of [<code>UiCheckbox</code>](#UiCheckbox)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name=""></a>

### uiCheckbox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  
<a name=""></a>

### uiCheckbox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  
<a name=""></a>

### uiCheckbox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  
