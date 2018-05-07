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
If true, the container insert some space between children.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  
<a name="UiBox+append"></a>

### uiHorizontalBox.append(control, stretchy) ⇒ <code>undefined</code>
Append a new child control as the last one.

**Kind**: instance method of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

| Param | Type | Description |
| --- | --- | --- |
| control | <code>UiControl</code> | the control to add as child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |

<a name="UiBox+deleteAt"></a>

### uiHorizontalBox.deleteAt(index) ⇒ <code>undefined</code>
Remove a child control at specified position.

**Kind**: instance method of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |

