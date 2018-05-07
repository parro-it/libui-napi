<a name="UiRadioButtons"></a>

## UiRadioButtons
A widget that represent a group of radio options.

**Kind**: global class  

* [UiRadioButtons](#UiRadioButtons)
    * [new UiRadioButtons()](#new_UiRadioButtons_new)
    * [.selected](#UiRadioButtons+selected) ⇒ <code>string</code>
    * [.append(text)](#UiRadioButtons+append) ⇒ <code>undefined</code>
    * [.onSelected(callback)](#UiRadioButtons+onSelected) ⇒ <code>undefined</code>

<a name="new_UiRadioButtons_new"></a>

### new UiRadioButtons()
Create a new UiRadioButtons object.

<a name="UiRadioButtons+selected"></a>

### uiRadioButtons.selected ⇒ <code>string</code>
Return or set the current selected item by index.

**Kind**: instance property of [<code>UiRadioButtons</code>](#UiRadioButtons)  
<a name="UiRadioButtons+append"></a>

### uiRadioButtons.append(text) ⇒ <code>undefined</code>
Append a new radio option as last one with specified text.

**Kind**: instance method of [<code>UiRadioButtons</code>](#UiRadioButtons)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the text to append. |

<a name="UiRadioButtons+onSelected"></a>

### uiRadioButtons.onSelected(callback) ⇒ <code>undefined</code>
Add a listener to the `selected` event. Emitted whenever the selected option changes.

**Kind**: instance method of [<code>UiRadioButtons</code>](#UiRadioButtons)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

