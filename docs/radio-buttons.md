## Classes

<dl>
<dt><a href="#UiRadioButtons">UiRadioButtons</a></dt>
<dd><p>A control that represents a group of single-choise options.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiRadioButtons"></a>

## UiRadioButtons
A control that represents a group of single-choise options.

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
Return or set the currently selected item by index.

**Kind**: instance property of [<code>UiRadioButtons</code>](#UiRadioButtons)  
<a name="UiRadioButtons+append"></a>

### uiRadioButtons.append(text) ⇒ <code>undefined</code>
Append a new radio option as the last item with the specified text.

**Kind**: instance method of [<code>UiRadioButtons</code>](#UiRadioButtons)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the text to append. |

<a name="UiRadioButtons+onSelected"></a>

### uiRadioButtons.onSelected(callback) ⇒ <code>undefined</code>
Add a listener to the `selected` event. Emitted whenever the selected
option changes.

**Kind**: instance method of [<code>UiRadioButtons</code>](#UiRadioButtons)  

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
