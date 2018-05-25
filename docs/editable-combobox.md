
<a id="uieditablecombobox"></a>
## UiEditableCombobox ⇐ <code>UiControl</code>
A drop down combo box that allows to select an item from list or to specify a custom
value.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiEditableCombobox](#UiEditableCombobox) ⇐ <code>UiControl</code>
    * [new UiEditableCombobox()](#new_UiEditableCombobox_new)
    * [.text](#UiEditableCombobox_text) ⇒ <code>string</code>
    * [.append(text)](#UiEditableCombobox_append)
    * [.onChanged(callback)](#UiEditableCombobox_onChanged)
    * [.enabled](#UiEditableCombobox_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiEditableCombobox_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiEditableCombobox_toplevel) ⇒ <code>boolean</code>


<a id="new_uieditablecombobox_new"></a>
### new UiEditableCombobox()
Create a new UiEditableCombobox object.


<a id="uieditablecombobox_text"></a>
### uiEditableCombobox.text ⇒ <code>string</code>
Return or set the current text.

**Kind**: instance property of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  

<a id="uieditablecombobox_append"></a>
### uiEditableCombobox.append(text)
Append a new text item to the drop down list.

**Kind**: instance method of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the item to append. |


<a id="uieditablecombobox_onchanged"></a>
### uiEditableCombobox.onChanged(callback)
Add a listener to the `changed` event. Emitted whenever the text (or item) changes.

**Kind**: instance method of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |


<a id="uieditablecombobox_enabled"></a>
### uiEditableCombobox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  

<a id="uieditablecombobox_visible"></a>
### uiEditableCombobox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  

<a id="uieditablecombobox_toplevel"></a>
### uiEditableCombobox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  
