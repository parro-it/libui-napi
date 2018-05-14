## Classes

<dl>
<dt><a href="#UiColorButton">UiColorButton</a> ⇐ <code><a href="#UiControl">UiControl</a></code></dt>
<dd><p>A button that opens a color palette popup.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiColorButton"></a>

## UiColorButton ⇐ [<code>UiControl</code>](#UiControl)
A button that opens a color palette popup.

**Kind**: global class  
**Extends**: [<code>UiControl</code>](#UiControl)  

* [UiColorButton](#UiColorButton) ⇐ [<code>UiControl</code>](#UiControl)
    * [new UiColorButton()](#new_UiColorButton_new)
    * [.color](#UiColorButton+color) ⇒ <code>Object</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
    * [.onChanged(callback)](#UiColorButton+onChanged) ⇒ <code>undefined</code>

<a name="new_UiColorButton_new"></a>

### new UiColorButton()
Create a new UiColorButton object.

<a name="UiColorButton+color"></a>

### uiColorButton.color ⇒ <code>Object</code>
Set or return the ColorButton color value.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  
<a name="UiControl+enabled"></a>

### uiColorButton.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  
<a name="UiControl+visible"></a>

### uiColorButton.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  
<a name="UiControl+toplevel"></a>

### uiColorButton.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiColorButton</code>](#UiColorButton)  
<a name="UiColorButton+onChanged"></a>

### uiColorButton.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the user
changed the selected color.

**Kind**: instance method of [<code>UiColorButton</code>](#UiColorButton)  

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
