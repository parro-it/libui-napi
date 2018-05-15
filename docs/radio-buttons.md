<a name="UiRadioButtons"></a>

## UiRadioButtons ⇐ <code>UiControl</code>
A control that represents a group of single-choise options.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiRadioButtons](#UiRadioButtons) ⇐ <code>UiControl</code>
    * [new UiRadioButtons()](#new_UiRadioButtons_new)
    * [.selected](#UiRadioButtons+selected) ⇒ <code>string</code>
    * [.append(text)](#UiRadioButtons+append)
    * [.onSelected(callback)](#UiRadioButtons+onSelected)
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiRadioButtons_new"></a>

### new UiRadioButtons()
Create a new UiRadioButtons object.

<a name="UiRadioButtons+selected"></a>

### uiRadioButtons.selected ⇒ <code>string</code>
Return or set the currently selected item by index.

**Kind**: instance property of [<code>UiRadioButtons</code>](#UiRadioButtons)  
<a name="UiRadioButtons+append"></a>

### uiRadioButtons.append(text)
Append a new radio option as the last item with the specified text.

**Kind**: instance method of [<code>UiRadioButtons</code>](#UiRadioButtons)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the text to append. |

<a name="UiRadioButtons+onSelected"></a>

### uiRadioButtons.onSelected(callback)
Add a listener to the `selected` event. Emitted whenever the selected
option changes.

**Kind**: instance method of [<code>UiRadioButtons</code>](#UiRadioButtons)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name=""></a>

### uiRadioButtons.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiRadioButtons</code>](#UiRadioButtons)  
<a name=""></a>

### uiRadioButtons.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiRadioButtons</code>](#UiRadioButtons)  
<a name=""></a>

### uiRadioButtons.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiRadioButtons</code>](#UiRadioButtons)  
