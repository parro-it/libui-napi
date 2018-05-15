<a name="UiGrid"></a>

## UiGrid ⇐ <code>UiControl</code>
A powerful container that allow to specify size and position of each children.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiGrid](#UiGrid) ⇐ <code>UiControl</code>
    * [new UiGrid()](#new_UiGrid_new)
    * [.padded](#UiGrid+padded) ⇒ <code>boolean</code>
    * [.insertAt(child, before, at, xspan, yspan, hexpand, halign, vexpand, valign)](#UiGrid+insertAt)
    * [.append(child, left, top, xspan, yspan, hexpand, halign, vexpand, valign)](#UiGrid+append)
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiGrid_new"></a>

### new UiGrid()
Create a new UiGrid object.

<a name="UiGrid+padded"></a>

### uiGrid.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiGrid</code>](#UiGrid)  
<a name="UiGrid+insertAt"></a>

### uiGrid.insertAt(child, before, at, xspan, yspan, hexpand, halign, vexpand, valign)
Insert a new child control before specified control.

**Kind**: instance method of [<code>UiGrid</code>](#UiGrid)  

| Param | Type | Description |
| --- | --- | --- |
| child | <code>UiControl</code> | the control to insert |
| before | <code>UiControl</code> | the control will be inserted before this position |
| at | <code>number</code> | [description] |
| xspan | <code>number</code> | How many columns the component takes off. |
| yspan | <code>number</code> | How many rows the component takes off. |
| hexpand | <code>number</code> | whether the component can expand horizontally. |
| halign | <code>number</code> | whether the component is aligned with the other 	 components in the column. |
| vexpand | <code>number</code> | whether the component can expand vertically. |
| valign | <code>number</code> | whether the component is aligned with the other 	 components in the row. |

<a name="UiGrid+append"></a>

### uiGrid.append(child, left, top, xspan, yspan, hexpand, halign, vexpand, valign)
Insert a new child control.

> UIGrid expand does not work correctly when both align horizontal and align
vertical are set. You must choose one so libui knows which direction to expand.

**Kind**: instance method of [<code>UiGrid</code>](#UiGrid)  

| Param | Type | Description |
| --- | --- | --- |
| child | <code>UiControl</code> | the control to add as child. |
| left | <code>number</code> | What column the component resides in. |
| top | <code>number</code> | What row the component resides in. |
| xspan | <code>number</code> | How many columns the component takes off. |
| yspan | <code>number</code> | How many rows the component takes off. |
| hexpand | <code>number</code> | whether the component can expand horizontally. |
| halign | <code>number</code> | whether the component is aligned with the other components in the column. |
| vexpand | <code>number</code> | whether the component can expand vertically. |
| valign | <code>number</code> | whether the component is aligned with the other components in the row. |

<a name=""></a>

### uiGrid.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiGrid</code>](#UiGrid)  
<a name=""></a>

### uiGrid.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiGrid</code>](#UiGrid)  
<a name=""></a>

### uiGrid.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiGrid</code>](#UiGrid)  
