## Classes

<dl>
<dt><a href="#UiCheckbox">UiCheckbox</a> ⇐ <code><a href="#UiControl">UiControl</a></code></dt>
<dd><p>A checkbox control.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiCheckbox"></a>

## UiCheckbox ⇐ [<code>UiControl</code>](#UiControl)
A checkbox control.

**Kind**: global class  
**Extends**: [<code>UiControl</code>](#UiControl)  

* [UiCheckbox](#UiCheckbox) ⇐ [<code>UiControl</code>](#UiControl)
    * [new UiCheckbox()](#new_UiCheckbox_new)
    * [.text](#UiCheckbox+text) ⇒ <code>string</code>
    * [.checked](#UiCheckbox+checked) ⇒ <code>boolean</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
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
<a name="UiControl+enabled"></a>

### uiCheckbox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  
<a name="UiControl+visible"></a>

### uiCheckbox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  
<a name="UiControl+toplevel"></a>

### uiCheckbox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  
<a name="UiCheckbox+onToggled"></a>

### uiCheckbox.onToggled(callback) ⇒ <code>undefined</code>
Add a listener to the `toggled` event. Emitted whenever the control
`checked` state change.

**Kind**: instance method of [<code>UiCheckbox</code>](#UiCheckbox)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name="UiControl"></a>

## UiControl
Base class for all controls.

**Kind**: global class  

* [UiControl](#UiControl)
    * [new UiControl()](#new_UiControl_new)
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>

<a name="new_UiControl_new"></a>

### new UiControl()
Create a new UiControl object.

<a name="UiControl+enabled"></a>

### uiControl.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiControl</code>](#UiControl)  
<a name="UiControl+visible"></a>

### uiControl.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiControl</code>](#UiControl)  
<a name="UiControl+toplevel"></a>

### uiControl.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiControl</code>](#UiControl)  
