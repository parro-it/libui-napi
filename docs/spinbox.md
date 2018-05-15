<a name="UiSpinbox"></a>

## UiSpinbox ⇐ <code>UiControl</code>
An entry control for numerical values.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiSpinbox](#UiSpinbox) ⇐ <code>UiControl</code>
    * [new UiSpinbox(min, max)](#new_UiSpinbox_new)
    * [.value](#UiSpinbox+value) ⇒ <code>number</code>
    * [.onChanged(callback)](#UiSpinbox+onChanged)
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

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
<a name="UiSpinbox+onChanged"></a>

### uiSpinbox.onChanged(callback)
Add a listener to the `changed` event. Emitted whenever the spinbox value changed.

**Kind**: instance method of [<code>UiSpinbox</code>](#UiSpinbox)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name=""></a>

### uiSpinbox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  
<a name=""></a>

### uiSpinbox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  
<a name=""></a>

### uiSpinbox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  
