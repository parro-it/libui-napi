
<a id="uiverticalbox"></a>
## UiVerticalBox ⇐ <code>UiBox</code>
A container that stacks its children vertically.

**Kind**: global class  
**Extends**: <code>UiBox</code>  

* [UiVerticalBox](#UiVerticalBox) ⇐ <code>UiBox</code>
    * [new UiVerticalBox()](#new_UiVerticalBox_new)
    * [.padded](#UiVerticalBox_padded) ⇒ <code>boolean</code>
    * [.append(control, stretchy)](#UiVerticalBox_append)
    * [.deleteAt(index)](#UiVerticalBox_deleteAt)
    * [.enabled](#UiVerticalBox_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiVerticalBox_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiVerticalBox_toplevel) ⇒ <code>boolean</code>


<a id="new_uiverticalbox_new"></a>
### new UiVerticalBox()
Create a new UiVerticalBox object.


<a id="uiverticalbox_padded"></a>
### uiVerticalBox.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiVerticalBox</code>](#UiVerticalBox)  

<a id="uiverticalbox_append"></a>
### uiVerticalBox.append(control, stretchy)
Append a new child control as the last child.

**Kind**: instance method of [<code>UiVerticalBox</code>](#UiVerticalBox)  

| Param | Type | Description |
| --- | --- | --- |
| control | <code>UiControl</code> | the control to add as a child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |


<a id="uiverticalbox_deleteat"></a>
### uiVerticalBox.deleteAt(index)
Remove a child control at specified position.

**Kind**: instance method of [<code>UiVerticalBox</code>](#UiVerticalBox)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |


<a id="uiverticalbox_enabled"></a>
### uiVerticalBox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiVerticalBox</code>](#UiVerticalBox)  

<a id="uiverticalbox_visible"></a>
### uiVerticalBox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiVerticalBox</code>](#UiVerticalBox)  

<a id="uiverticalbox_toplevel"></a>
### uiVerticalBox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiVerticalBox</code>](#UiVerticalBox)  
