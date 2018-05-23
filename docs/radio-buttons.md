
<a id="uiradiobuttons"></a>
## UiRadioButtons ⇐ <code>UiControl</code>
A control that represents a group of single-choise options.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiRadioButtons](#UiRadioButtons) ⇐ <code>UiControl</code>
    * [new UiRadioButtons()](#new_UiRadioButtons_new)
    * [.selected](#UiRadioButtons_selected) ⇒ <code>string</code>
    * [.append(text)](#UiRadioButtons_append)
    * [.onSelected(callback)](#UiRadioButtons_onSelected)
    * [.enabled](#UiRadioButtons_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiRadioButtons_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiRadioButtons_toplevel) ⇒ <code>boolean</code>


<a id="new_uiradiobuttons_new"></a>
### new UiRadioButtons()
Create a new UiRadioButtons object.


<a id="uiradiobuttons_selected"></a>
### uiRadioButtons.selected ⇒ <code>string</code>
Return or set the currently selected item by index.

**Kind**: instance property of [<code>UiRadioButtons</code>](#UiRadioButtons)  

<a id="uiradiobuttons_append"></a>
### uiRadioButtons.append(text)
Append a new radio option as the last item with the specified text.

**Kind**: instance method of [<code>UiRadioButtons</code>](#UiRadioButtons)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the text to append. |


<a id="uiradiobuttons_onselected"></a>
### uiRadioButtons.onSelected(callback)
Add a listener to the `selected` event. Emitted whenever the selected
option changes.

**Kind**: instance method of [<code>UiRadioButtons</code>](#UiRadioButtons)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |


<a id="uiradiobuttons_enabled"></a>
### uiRadioButtons.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiRadioButtons</code>](#UiRadioButtons)  

<a id="uiradiobuttons_visible"></a>
### uiRadioButtons.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiRadioButtons</code>](#UiRadioButtons)  

<a id="uiradiobuttons_toplevel"></a>
### uiRadioButtons.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiRadioButtons</code>](#UiRadioButtons)  
