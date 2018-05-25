
<a id="uihorizontalbox"></a>
## UiHorizontalBox ⇐ <code>UiBox</code>
A container that stacks its chidren horizontally.

**Kind**: global class  
**Extends**: <code>UiBox</code>  

* [UiHorizontalBox](#UiHorizontalBox) ⇐ <code>UiBox</code>
    * [new UiHorizontalBox()](#new_UiHorizontalBox_new)
    * [.padded](#UiHorizontalBox_padded) ⇒ <code>boolean</code>
    * [.append(control, stretchy)](#UiHorizontalBox_append)
    * [.deleteAt(index)](#UiHorizontalBox_deleteAt)
    * [.enabled](#UiHorizontalBox_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiHorizontalBox_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiHorizontalBox_toplevel) ⇒ <code>boolean</code>


<a id="new_uihorizontalbox_new"></a>
### new UiHorizontalBox()
Create a new UiHorizontalBox object.


<a id="uihorizontalbox_padded"></a>
### uiHorizontalBox.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

<a id="uihorizontalbox_append"></a>
### uiHorizontalBox.append(control, stretchy)
Append a new child control as the last child.

**Kind**: instance method of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

| Param | Type | Description |
| --- | --- | --- |
| control | <code>UiControl</code> | the control to add as a child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |


<a id="uihorizontalbox_deleteat"></a>
### uiHorizontalBox.deleteAt(index)
Remove a child control at specified position.

**Kind**: instance method of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |


<a id="uihorizontalbox_enabled"></a>
### uiHorizontalBox.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

<a id="uihorizontalbox_visible"></a>
### uiHorizontalBox.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  

<a id="uihorizontalbox_toplevel"></a>
### uiHorizontalBox.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiHorizontalBox</code>](#UiHorizontalBox)  
