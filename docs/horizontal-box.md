## Classes

<dl>
<dt><a href="#UiHorizontalBox">UiHorizontalBox</a> ⇐ <code>UiBox</code></dt>
<dd><p>A container that stacks its chidren horizontally.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiHorizontalBox"></a>

## UiHorizontalBox ⇐ <code>UiBox</code>
A container that stacks its chidren horizontally.

**Kind**: global class  
**Extends**: <code>UiBox</code>  

* [UiHorizontalBox](#UiHorizontalBox) ⇐ <code>UiBox</code>
    * [new UiHorizontalBox()](#new_UiHorizontalBox_new)
    * [.padded](#UiBox+padded) ⇒ <code>boolean</code>
    * [.append(control, stretchy)](#UiBox+append) ⇒ <code>undefined</code>
    * [.deleteAt(index)](#UiBox+deleteAt) ⇒ <code>undefined</code>

<a name="new_UiHorizontalBox_new"></a>

### new UiHorizontalBox()
Create a new UiHorizontalBox object.

<a name="UiBox+padded"></a>

### uiHorizontalBox.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  
<a name="UiBox+append"></a>

### uiHorizontalBox.append(control, stretchy) ⇒ <code>undefined</code>
Append a new child control as the last child.

**Kind**: instance method of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

| Param | Type | Description |
| --- | --- | --- |
| control | [<code>UiControl</code>](#UiControl) | the control to add as a child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |

<a name="UiBox+deleteAt"></a>

### uiHorizontalBox.deleteAt(index) ⇒ <code>undefined</code>
Remove a child control at specified position.

**Kind**: instance method of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |

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
