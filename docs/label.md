## Classes

<dl>
<dt><a href="#UiLabel">UiLabel</a></dt>
<dd><p>A static text label.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiLabel"></a>

## UiLabel
A static text label.

**Kind**: global class  

* [UiLabel](#UiLabel)
    * [new UiLabel(text)](#new_UiLabel_new)
    * [.text](#UiLabel+text) ⇒ <code>string</code>

<a name="new_UiLabel_new"></a>

### new UiLabel(text)
Create a new UiLabel object.


| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | initial content of the label |

<a name="UiLabel+text"></a>

### uiLabel.text ⇒ <code>string</code>
Set or return the the content of the label.

**Kind**: instance property of [<code>UiLabel</code>](#UiLabel)  
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
