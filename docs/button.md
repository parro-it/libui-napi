## Classes

<dl>
<dt><a href="#UiButton">UiButton</a> ⇐ <code><a href="#UiControl">UiControl</a></code></dt>
<dd><p>A simple button.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiButton"></a>

## UiButton ⇐ [<code>UiControl</code>](#UiControl)
A simple button.

**Kind**: global class  
**Extends**: [<code>UiControl</code>](#UiControl)  

* [UiButton](#UiButton) ⇐ [<code>UiControl</code>](#UiControl)
    * [new UiButton()](#new_UiButton_new)
    * [.text](#UiButton+text) ⇒ <code>string</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
    * [.onClicked(callback)](#UiButton+onClicked) ⇒ <code>undefined</code>

<a name="new_UiButton_new"></a>

### new UiButton()
Create a new UiButton object.

<a name="UiButton+text"></a>

### uiButton.text ⇒ <code>string</code>
Set or return the text of the button.

**Kind**: instance property of [<code>UiButton</code>](#UiButton)  
<a name="UiControl+enabled"></a>

### uiButton.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiButton</code>](#UiButton)  
<a name="UiControl+visible"></a>

### uiButton.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiButton</code>](#UiButton)  
<a name="UiControl+toplevel"></a>

### uiButton.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiButton</code>](#UiButton)  
<a name="UiButton+onClicked"></a>

### uiButton.onClicked(callback) ⇒ <code>undefined</code>
Emitted when the button is clicked

**Kind**: instance method of [<code>UiButton</code>](#UiButton)  

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
