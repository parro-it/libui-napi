
<a id="uicolorbutton"></a>
## UiColorButton ⇐ <code>UiControl</code>
A button that opens a color palette popup.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiColorButton](#UiColorButton) ⇐ <code>UiControl</code>
    * [new UiColorButton()](#new_UiColorButton_new)
    * [.color](#UiColorButton_color) ⇒ <code>Color</code>
    * [.onChanged(callback)](#UiColorButton_onChanged)
    * [.enabled](#UiColorButton_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiColorButton_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiColorButton_toplevel) ⇒ <code>boolean</code>


<a id="new_uicolorbutton_new"></a>
### new UiColorButton()
Create a new UiColorButton object.


<a id="uicolorbutton_color"></a>
### uiColorButton.color ⇒ <code>Color</code>
Set or return the ColorButton color value.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  

<a id="uicolorbutton_onchanged"></a>
### uiColorButton.onChanged(callback)
Add a listener to the `changed` event. Emitted whenever the user
changed the selected color.

**Kind**: instance method of [<code>UiColorButton</code>](#UiColorButton)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |


<a id="uicolorbutton_enabled"></a>
### uiColorButton.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  

<a id="uicolorbutton_visible"></a>
### uiColorButton.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  

<a id="uicolorbutton_toplevel"></a>
### uiColorButton.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  
