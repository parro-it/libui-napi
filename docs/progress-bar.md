## Classes

<dl>
<dt><a href="#UiProgressBar">UiProgressBar</a> ⇐ <code><a href="#UiControl">UiControl</a></code></dt>
<dd><p>Progress bar control.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiProgressBar"></a>

## UiProgressBar ⇐ [<code>UiControl</code>](#UiControl)
Progress bar control.

**Kind**: global class  
**Extends**: [<code>UiControl</code>](#UiControl)  

* [UiProgressBar](#UiProgressBar) ⇐ [<code>UiControl</code>](#UiControl)
    * [new UiProgressBar()](#new_UiProgressBar_new)
    * [.value](#UiProgressBar+value) ⇒ <code>number</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>

<a name="new_UiProgressBar_new"></a>

### new UiProgressBar()
Create a new UiProgressBar object.

<a name="UiProgressBar+value"></a>

### uiProgressBar.value ⇒ <code>number</code>
The current position of the progress bar. Can be set to -1 to create
an indeterminate progress bar.

**Kind**: instance property of [<code>UiProgressBar</code>](#UiProgressBar)  
<a name="UiControl+enabled"></a>

### uiProgressBar.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiProgressBar</code>](#UiProgressBar)  
<a name="UiControl+visible"></a>

### uiProgressBar.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiProgressBar</code>](#UiProgressBar)  
<a name="UiControl+toplevel"></a>

### uiProgressBar.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiProgressBar</code>](#UiProgressBar)  
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
