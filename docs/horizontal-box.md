<a name="UiHorizontalBox"></a>

## UiHorizontalBox ⇐ <code>UiBox</code>
A container that stacks its chidren horizontally.

**Kind**: global class  
**Extends**: <code>UiBox</code>  

* [UiHorizontalBox](#UiHorizontalBox) ⇐ <code>UiBox</code>
    * [new UiHorizontalBox()](#new_UiHorizontalBox_new)
    * [.padded](#) ⇒ <code>boolean</code>
    * [.append(control, stretchy)](#) ⇒ <code>undefined</code>
    * [.deleteAt(index)](#) ⇒ <code>undefined</code>
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiHorizontalBox_new"></a>

### new UiHorizontalBox()
Create a new UiHorizontalBox object.

<a name=""></a>

### uiHorizontalBox.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  
<a name=""></a>

### uiHorizontalBox.append(control, stretchy) ⇒ <code>undefined</code>
Append a new child control as the last child.

**Kind**: instance method of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

| Param | Type | Description |
| --- | --- | --- |
| control | <code>UiControl</code> | the control to add as a child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |

<a name=""></a>

### uiHorizontalBox.deleteAt(index) ⇒ <code>undefined</code>
Remove a child control at specified position.

**Kind**: instance method of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |

<a name=""></a>

### uiHorizontalBox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  
<a name=""></a>

### uiHorizontalBox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  
<a name=""></a>

### uiHorizontalBox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  
