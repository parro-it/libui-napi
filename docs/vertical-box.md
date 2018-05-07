<a name="UiVerticalBox"></a>

## UiVerticalBox ⇐ <code>UiBox</code>
A container that stacks its children vertically.

**Kind**: global class  
**Extends**: <code>UiBox</code>  

* [UiVerticalBox](#UiVerticalBox) ⇐ <code>UiBox</code>
    * [new UiVerticalBox()](#new_UiVerticalBox_new)
    * [.padded](#UiBox+padded) ⇒ <code>boolean</code>
    * [.append(control, stretchy)](#UiBox+append) ⇒ <code>undefined</code>
    * [.deleteAt(index)](#UiBox+deleteAt) ⇒ <code>undefined</code>

<a name="new_UiVerticalBox_new"></a>

### new UiVerticalBox()
Create a new UiVerticalBox object.

<a name="UiBox+padded"></a>

### uiVerticalBox.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiVerticalBox</code>](#UiVerticalBox)  
<a name="UiBox+append"></a>

### uiVerticalBox.append(control, stretchy) ⇒ <code>undefined</code>
Append a new child control as the last child.

**Kind**: instance method of [<code>UiVerticalBox</code>](#UiVerticalBox)  

| Param | Type | Description |
| --- | --- | --- |
| control | <code>UiControl</code> | the control to add as a child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |

<a name="UiBox+deleteAt"></a>

### uiVerticalBox.deleteAt(index) ⇒ <code>undefined</code>
Remove a child control at specified position.

**Kind**: instance method of [<code>UiVerticalBox</code>](#UiVerticalBox)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |

