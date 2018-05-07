<a name="UiVerticalBox"></a>

## UiVerticalBox ⇐ <code>UiBox</code>
A container that stacks its chidren vertically.

**Kind**: global class  
**Extends**: <code>UiBox</code>  

* [UiVerticalBox](#UiVerticalBox) ⇐ <code>UiBox</code>
    * [new UiVerticalBox()](#new_UiVerticalBox_new)
    * [.getPadded()](#UiBox+getPadded) ⇒ <code>boolean</code>
    * [.append(control, stretchy)](#UiBox+append) ⇒ <code>undefined</code>
    * [.deleteAt(index)](#UiBox+deleteAt) ⇒ <code>undefined</code>

<a name="new_UiVerticalBox_new"></a>

### new UiVerticalBox()
Create a new UiVerticalBox object.

<a name="UiBox+getPadded"></a>

### uiVerticalBox.getPadded() ⇒ <code>boolean</code>
If true, the container insert some space between children.

**Kind**: instance method of [<code>UiVerticalBox</code>](#UiVerticalBox)  
<a name="UiBox+append"></a>

### uiVerticalBox.append(control, stretchy) ⇒ <code>undefined</code>
Append a new child control as the last one.

**Kind**: instance method of [<code>UiVerticalBox</code>](#UiVerticalBox)  

| Param | Type | Description |
| --- | --- | --- |
| control | <code>UiControl</code> | the control to add as child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |

<a name="UiBox+deleteAt"></a>

### uiVerticalBox.deleteAt(index) ⇒ <code>undefined</code>
Remove a child control at specified position.

**Kind**: instance method of [<code>UiVerticalBox</code>](#UiVerticalBox)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |

