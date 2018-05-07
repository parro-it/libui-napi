<a name="UiCombobox"></a>

## UiCombobox
A drop down combo box that allow list selection only.

**Kind**: global class  

* [UiCombobox](#UiCombobox)
    * [new UiCombobox()](#new_UiCombobox_new)
    * [.selected](#UiCombobox+selected) ⇒ <code>string</code>
    * [.append(text)](#UiCombobox+append) ⇒ <code>undefined</code>
    * [.onSelected(callback)](#UiCombobox+onSelected) ⇒ <code>undefined</code>

<a name="new_UiCombobox_new"></a>

### new UiCombobox()
Create a new UiCombobox object.

<a name="UiCombobox+selected"></a>

### uiCombobox.selected ⇒ <code>string</code>
Return or set the current selected item by index.

**Kind**: instance property of [<code>UiCombobox</code>](#UiCombobox)  
<a name="UiCombobox+append"></a>

### uiCombobox.append(text) ⇒ <code>undefined</code>
Append a new text item to the drop down list.

**Kind**: instance method of [<code>UiCombobox</code>](#UiCombobox)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the text to append. |

<a name="UiCombobox+onSelected"></a>

### uiCombobox.onSelected(callback) ⇒ <code>undefined</code>
Add a listener to the `selected` event. Emitted whenever the selected item changes.

**Kind**: instance method of [<code>UiCombobox</code>](#UiCombobox)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

