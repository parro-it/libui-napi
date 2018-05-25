
<a id="uifontbutton"></a>
## UiFontButton ⇐ <code>UiControl</code>
A button that opens a popup to choose a font.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiFontButton](#UiFontButton) ⇐ <code>UiControl</code>
    * [new UiFontButton()](#new_UiFontButton_new)
    * [.font](#UiFontButton_font) ⇒ <code>FontDescriptor</code>
    * [.onChanged(callback)](#UiFontButton_onChanged) ⇒ <code>undefined</code>
    * [.enabled](#UiFontButton_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiFontButton_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiFontButton_toplevel) ⇒ <code>boolean</code>


<a id="new_uifontbutton_new"></a>
### new UiFontButton()
Create a new UiFontButton object.


<a id="uifontbutton_font"></a>
### uiFontButton.font ⇒ <code>FontDescriptor</code>
Return the FontButton font value.

**Kind**: instance property of [<code>UiFontButton</code>](#UiFontButton)  

<a id="uifontbutton_onchanged"></a>
### uiFontButton.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the user
changed the selected font.

**Kind**: instance method of [<code>UiFontButton</code>](#UiFontButton)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |


<a id="uifontbutton_enabled"></a>
### uiFontButton.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiFontButton</code>](#UiFontButton)  

<a id="uifontbutton_visible"></a>
### uiFontButton.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiFontButton</code>](#UiFontButton)  

<a id="uifontbutton_toplevel"></a>
### uiFontButton.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiFontButton</code>](#UiFontButton)  
