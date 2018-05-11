<a name="UiCheckbox"></a>

## UiCheckbox
A checkbox control.

**Kind**: global class  

* [UiCheckbox](#UiCheckbox)
    * [new UiCheckbox()](#new_UiCheckbox_new)
    * [.text](#UiCheckbox+text) ⇒ <code>string</code>
    * [.checked](#UiCheckbox+checked) ⇒ <code>boolean</code>
    * [.onToggled(callback)](#UiCheckbox+onToggled) ⇒ <code>undefined</code>

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

