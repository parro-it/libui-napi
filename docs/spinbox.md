
<a id="uispinbox"></a>
## UiSpinbox ⇐ <code>UiControl</code>
An entry control for numerical values.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiSpinbox](#UiSpinbox) ⇐ <code>UiControl</code>
    * [new UiSpinbox(min, max)](#new_UiSpinbox_new)
    * [.value](#UiSpinbox_value) ⇒ <code>number</code>
    * [.onChanged(callback)](#UiSpinbox_onChanged)
    * [.enabled](#UiSpinbox_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiSpinbox_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiSpinbox_toplevel) ⇒ <code>boolean</code>


<a id="new_uispinbox_new"></a>
### new UiSpinbox(min, max)
Create a new UiSpinbox object.


| Param | Type | Default | Description |
| --- | --- | --- | --- |
| min | <code>number</code> | <code>0</code> | minimum value of the spinbox. defaults to 0 |
| max | <code>number</code> | <code>100</code> | maximum value of the spinbox. defaults to 100 |


<a id="uispinbox_value"></a>
### uiSpinbox.value ⇒ <code>number</code>
Set or return the the content of spinbox.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  

<a id="uispinbox_onchanged"></a>
### uiSpinbox.onChanged(callback)
Add a listener to the `changed` event. Emitted whenever the spinbox value changed.

**Kind**: instance method of [<code>UiSpinbox</code>](#UiSpinbox)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |


<a id="uispinbox_enabled"></a>
### uiSpinbox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  

<a id="uispinbox_visible"></a>
### uiSpinbox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  

<a id="uispinbox_toplevel"></a>
### uiSpinbox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiSpinbox</code>](#UiSpinbox)  
