<a name="UiTimePicker"></a>

## UiTimePicker ⇐ <code>DateTimePickerBase</code>
A control to set a time.

**Kind**: global class  
**Extends**: <code>DateTimePickerBase</code>  

* [UiTimePicker](#UiTimePicker) ⇐ <code>DateTimePickerBase</code>
    * [new UiTimePicker()](#new_UiTimePicker_new)
    * [.time](#) ⇒ <code>Date</code>
    * [.onChanged(callback)](#)
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiTimePicker_new"></a>

### new UiTimePicker()
Create a new UiTimePicker object.

<a name=""></a>

### uiTimePicker.time ⇒ <code>Date</code>
Set or return the date/time represented by the control.

**Kind**: instance property of [<code>UiTimePicker</code>](#UiTimePicker)  
<a name=""></a>

### uiTimePicker.onChanged(callback)
Add a listener to the `changed` event. Emitted whenever the entry contents
changed.

**Kind**: instance method of [<code>UiTimePicker</code>](#UiTimePicker)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name=""></a>

### uiTimePicker.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiTimePicker</code>](#UiTimePicker)  
<a name=""></a>

### uiTimePicker.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiTimePicker</code>](#UiTimePicker)  
<a name=""></a>

### uiTimePicker.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiTimePicker</code>](#UiTimePicker)  
