<a name="UiVerticalBox"></a>

## UiVerticalBox ⇐ <code>UiBox</code>
A container that stacks its children vertically.

**Kind**: global class  
**Extends**: <code>UiBox</code>  

* [UiVerticalBox](#UiVerticalBox) ⇐ <code>UiBox</code>
    * [new UiVerticalBox()](#new_UiVerticalBox_new)
    * [.padded](#) ⇒ <code>boolean</code>
    * [.append(control, stretchy)](#)
    * [.deleteAt(index)](#)
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiVerticalBox_new"></a>

### new UiVerticalBox()
Create a new UiVerticalBox object.

<a name=""></a>

### uiVerticalBox.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiVerticalBox</code>](#UiVerticalBox)  
<a name=""></a>

### uiVerticalBox.append(control, stretchy)
Append a new child control as the last child.

**Kind**: instance method of [<code>UiVerticalBox</code>](#UiVerticalBox)  

| Param | Type | Description |
| --- | --- | --- |
| control | <code>UiControl</code> | the control to add as a child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |

<a name=""></a>

### uiVerticalBox.deleteAt(index)
Remove a child control at specified position.

**Kind**: instance method of [<code>UiVerticalBox</code>](#UiVerticalBox)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |

<a name=""></a>

### uiVerticalBox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiVerticalBox</code>](#UiVerticalBox)  
<a name=""></a>

### uiVerticalBox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiVerticalBox</code>](#UiVerticalBox)  
<a name=""></a>

### uiVerticalBox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiVerticalBox</code>](#UiVerticalBox)  
