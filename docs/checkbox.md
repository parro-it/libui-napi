
<a id="uicheckbox"></a>
## UiCheckbox ⇐ <code>UiControl</code>
A checkbox control.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiCheckbox](#UiCheckbox) ⇐ <code>UiControl</code>
    * [new UiCheckbox()](#new_UiCheckbox_new)
    * [.text](#UiCheckbox_text) ⇒ <code>string</code>
    * [.checked](#UiCheckbox_checked) ⇒ <code>boolean</code>
    * [.onToggled(callback)](#UiCheckbox_onToggled)
    * [.enabled](#UiCheckbox_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiCheckbox_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiCheckbox_toplevel) ⇒ <code>boolean</code>


<a id="new_uicheckbox_new"></a>
### new UiCheckbox()
Create a new UiCheckbox object.


<a id="uicheckbox_text"></a>
### uiCheckbox.text ⇒ <code>string</code>
Set or return the text label for the checkbox.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  

<a id="uicheckbox_checked"></a>
### uiCheckbox.checked ⇒ <code>boolean</code>
Whether the control is checked.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  

<a id="uicheckbox_ontoggled"></a>
### uiCheckbox.onToggled(callback)
Add a listener to the `toggled` event. Emitted whenever the control
`checked` state change.

**Kind**: instance method of [<code>UiCheckbox</code>](#UiCheckbox)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |


<a id="uicheckbox_enabled"></a>
### uiCheckbox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  

<a id="uicheckbox_visible"></a>
### uiCheckbox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  

<a id="uicheckbox_toplevel"></a>
### uiCheckbox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiCheckbox</code>](#UiCheckbox)  
