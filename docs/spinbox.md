## Classes

<dl>
<dt><a href="#UiSpinbox">UiSpinbox</a> ⇐ <code><a href="#UiControl">UiControl</a></code></dt>
<dd><p>An entry control for numerical values.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiSpinbox"></a>

## UiSpinbox ⇐ [<code>UiControl</code>](#UiControl)
An entry control for numerical values.

**Kind**: global class  
**Extends**: [<code>UiControl</code>](#UiControl)  

* [UiSpinbox](#UiSpinbox) ⇐ [<code>UiControl</code>](#UiControl)
    * [new UiSpinbox(min, max)](#new_UiSpinbox_new)
    * [.value](#UiSpinbox+value) ⇒ <code>number</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
    * [.onChanged(callback)](#UiSpinbox+onChanged) ⇒ <code>undefined</code>

<a name="new_UiSpinbox_new"></a>

### new UiSpinbox(min, max)
Create a new UiSpinbox object.


| Param | Type | Description |
| --- | --- | --- |
| min | <code>number</code> | minimum value of the spinbox. |
| max | <code>number</code> | maximum value of the spinbox. |

<a name="UiSpinbox+value"></a>

### uiSpinbox.value ⇒ <code>number</code>
Set or return the the content of spinbox.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  
<a name="UiControl+enabled"></a>

### uiSpinbox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  
<a name="UiControl+visible"></a>

### uiSpinbox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  
<a name="UiControl+toplevel"></a>

### uiSpinbox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  
<a name="UiSpinbox+onChanged"></a>

### uiSpinbox.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the spinbox value changed.

**Kind**: instance method of [<code>UiSpinbox</code>](#UiSpinbox)  

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
