## Classes

<dl>
<dt><a href="#UiCombobox">UiCombobox</a> ⇐ <code><a href="#UiControl">UiControl</a></code></dt>
<dd><p>A drop down combo box that allow list selection only.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiCombobox"></a>

## UiCombobox ⇐ [<code>UiControl</code>](#UiControl)
A drop down combo box that allow list selection only.

**Kind**: global class  
**Extends**: [<code>UiControl</code>](#UiControl)  

* [UiCombobox](#UiCombobox) ⇐ [<code>UiControl</code>](#UiControl)
    * [new UiCombobox()](#new_UiCombobox_new)
    * [.selected](#UiCombobox+selected) ⇒ <code>string</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
    * [.append(text)](#UiCombobox+append) ⇒ <code>undefined</code>
    * [.onSelected(callback)](#UiCombobox+onSelected) ⇒ <code>undefined</code>

<a name="new_UiCombobox_new"></a>

### new UiCombobox()
Create a new UiCombobox object.

<a name="UiCombobox+selected"></a>

### uiCombobox.selected ⇒ <code>string</code>
Return or set the current selected item by index.

**Kind**: instance property of [<code>UiCombobox</code>](#UiCombobox)  
<a name="UiControl+enabled"></a>

### uiCombobox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiCombobox</code>](#UiCombobox)  
<a name="UiControl+visible"></a>

### uiCombobox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiCombobox</code>](#UiCombobox)  
<a name="UiControl+toplevel"></a>

### uiCombobox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiCombobox</code>](#UiCombobox)  
<a name="UiCombobox+append"></a>

### uiCombobox.append(text) ⇒ <code>undefined</code>
Append a new text item to the drop down list.

**Kind**: instance method of [<code>UiCombobox</code>](#UiCombobox)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the item to append. |

<a name="UiCombobox+onSelected"></a>

### uiCombobox.onSelected(callback) ⇒ <code>undefined</code>
Add a listener to the `selected` event. Emitted whenever the selected
item changes.

**Kind**: instance method of [<code>UiCombobox</code>](#UiCombobox)  

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
