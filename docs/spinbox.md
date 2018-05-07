<a name="UiSpinbox"></a>

## UiSpinbox
An entry control for numerical values.

**Kind**: global class  

* [UiSpinbox](#UiSpinbox)
    * [new UiSpinbox(min, max)](#new_UiSpinbox_new)
    * [.value](#UiSpinbox+value) ⇒ <code>number</code>
    * [.onChanged(callback)](#UiSpinbox+onChanged) ⇒ <code>undefined</code>

<a name="new_UiSpinbox_new"></a>

### new UiSpinbox(min, max)
Create a new UiSpinbox object.


| Param | Type | Description |
| --- | --- | --- |
| min | <code>number</code> | minimum allowed value of the spinbox. |
| max | <code>number</code> | maximum allowed value of the spinbox. |

<a name="UiSpinbox+value"></a>

### uiSpinbox.value ⇒ <code>number</code>
Set or return the the content of spinbox.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  
<a name="UiSpinbox+onChanged"></a>

### uiSpinbox.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the spinbox value changed.

**Kind**: instance method of [<code>UiSpinbox</code>](#UiSpinbox)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

