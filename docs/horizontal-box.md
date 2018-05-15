## Classes

<dl>
<dt><a href="#UiBox">UiBox</a> ⇐ <code><a href="#UiControl">UiControl</a></code></dt>
<dd><p>Base class for vertical and horizontal boxes</p>
</dd>
<dt><a href="#UiHorizontalBox">UiHorizontalBox</a> ⇐ <code><a href="#UiBox">UiBox</a></code></dt>
<dd><p>A container that stacks its chidren horizontally.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiBox"></a>

## UiBox ⇐ [<code>UiControl</code>](#UiControl)
Base class for vertical and horizontal boxes

**Kind**: global class  
**Extends**: [<code>UiControl</code>](#UiControl)  

* [UiBox](#UiBox) ⇐ [<code>UiControl</code>](#UiControl)
    * [.padded](#UiBox+padded) ⇒ <code>boolean</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
    * [.append(control, stretchy)](#UiBox+append) ⇒ <code>undefined</code>
    * [.deleteAt(index)](#UiBox+deleteAt) ⇒ <code>undefined</code>

<a name="UiBox+padded"></a>

### uiBox.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiBox</code>](#UiBox)  
<a name="UiControl+enabled"></a>

### uiBox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiBox</code>](#UiBox)  
<a name="UiControl+visible"></a>

### uiBox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiBox</code>](#UiBox)  
<a name="UiControl+toplevel"></a>

### uiBox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiBox</code>](#UiBox)  
<a name="UiBox+append"></a>

### uiBox.append(control, stretchy) ⇒ <code>undefined</code>
Append a new child control as the last child.

**Kind**: instance method of [<code>UiBox</code>](#UiBox)  

| Param | Type | Description |
| --- | --- | --- |
| control | [<code>UiControl</code>](#UiControl) | the control to add as a child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |

<a name="UiBox+deleteAt"></a>

### uiBox.deleteAt(index) ⇒ <code>undefined</code>
Remove a child control at specified position.

**Kind**: instance method of [<code>UiBox</code>](#UiBox)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |

<a name="UiHorizontalBox"></a>

## UiHorizontalBox ⇐ [<code>UiBox</code>](#UiBox)
A container that stacks its chidren horizontally.

**Kind**: global class  
**Extends**: [<code>UiBox</code>](#UiBox)  

* [UiHorizontalBox](#UiHorizontalBox) ⇐ [<code>UiBox</code>](#UiBox)
    * [new UiHorizontalBox()](#new_UiHorizontalBox_new)
    * [.padded](#UiBox+padded) ⇒ <code>boolean</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
    * [.append(control, stretchy)](#UiBox+append) ⇒ <code>undefined</code>
    * [.deleteAt(index)](#UiBox+deleteAt) ⇒ <code>undefined</code>

<a name="new_UiHorizontalBox_new"></a>

### new UiHorizontalBox()
Create a new UiHorizontalBox object.

<a name="UiBox+padded"></a>

### uiHorizontalBox.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  
<a name="UiControl+enabled"></a>

### uiHorizontalBox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  
<a name="UiControl+visible"></a>

### uiHorizontalBox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  
<a name="UiControl+toplevel"></a>

### uiHorizontalBox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

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
