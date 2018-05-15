<a name="UiEditableCombobox"></a>

## UiEditableCombobox ⇐ <code>UiControl</code>
A drop down combo box that allows to select an item from list or to specify a custom
value.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiEditableCombobox](#UiEditableCombobox) ⇐ <code>UiControl</code>
    * [new UiEditableCombobox()](#new_UiEditableCombobox_new)
    * [.text](#UiEditableCombobox+text) ⇒ <code>string</code>
    * [.append(text)](#UiEditableCombobox+append) ⇒ <code>undefined</code>
    * [.onChanged(callback)](#UiEditableCombobox+onChanged) ⇒ <code>undefined</code>
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiEditableCombobox_new"></a>

### new UiEditableCombobox()
Create a new UiEditableCombobox object.

<a name="UiEditableCombobox+text"></a>

### uiEditableCombobox.text ⇒ <code>string</code>
Return or set the current text.

**Kind**: instance property of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  
<a name="UiEditableCombobox+append"></a>

### uiEditableCombobox.append(text) ⇒ <code>undefined</code>
Append a new text item to the drop down list.

**Kind**: instance method of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the item to append. |

<a name="UiEditableCombobox+onChanged"></a>

### uiEditableCombobox.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the text (or item) changes.

**Kind**: instance method of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name=""></a>

### uiEditableCombobox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  
<a name=""></a>

### uiEditableCombobox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  
<a name=""></a>

### uiEditableCombobox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiEditableCombobox</code>](#UiEditableCombobox)  
