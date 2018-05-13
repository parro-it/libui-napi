<a name="UiGrid"></a>

## UiGrid
A powerful container that allow to specify size and position of each children.

**Kind**: global class  

* [UiGrid](#UiGrid)
    * [new UiGrid()](#new_UiGrid_new)
    * [.padded](#UiGrid+padded) ⇒ <code>boolean</code>
    * [.insertAt(child, before, at, xspan, yspan, hexpand, halign, vexpand, valign)](#UiGrid+insertAt) ⇒ <code>undefined</code>
    * [.append(child, left, top, xspan, yspan, hexpand, halign, vexpand, valign)](#UiGrid+append) ⇒ <code>undefined</code>

<a name="new_UiGrid_new"></a>

### new UiGrid()
Create a new UiGrid object.

<a name="UiGrid+padded"></a>

### uiGrid.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiGrid</code>](#UiGrid)  
<a name="UiGrid+insertAt"></a>

### uiGrid.insertAt(child, before, at, xspan, yspan, hexpand, halign, vexpand, valign) ⇒ <code>undefined</code>
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

### uiGrid.append(child, left, top, xspan, yspan, hexpand, halign, vexpand, valign) ⇒ <code>undefined</code>
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

