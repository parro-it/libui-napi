<a name="UiGrid"></a>

## UiGrid
A container that organizes children as labeled fields.

**Kind**: global class  

* [UiGrid](#UiGrid)
    * [new UiGrid()](#new_UiGrid_new)
    * [.padded](#UiGrid+padded) ⇒ <code>boolean</code>
    * [.insertAt(child, before, at, xspan, yspan, hexpand, halign, vexpan, valign)](#UiGrid+insertAt) ⇒ <code>undefined</code>
    * [.append(child, left, top, xspan, yspan, hexpand, halign, vexpand, valign)](#UiGrid+append) ⇒ <code>undefined</code>

<a name="new_UiGrid_new"></a>

### new UiGrid()
Create a new UiGrid object.

<a name="UiGrid+padded"></a>

### uiGrid.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiGrid</code>](#UiGrid)  
<a name="UiGrid+insertAt"></a>

### uiGrid.insertAt(child, before, at, xspan, yspan, hexpand, halign, vexpan, valign) ⇒ <code>undefined</code>
Insert a new child control before specified control.

**Kind**: instance method of [<code>UiGrid</code>](#UiGrid)  

| Param | Type | Description |
| --- | --- | --- |
| child | <code>UiControl</code> | the control to insert |
| before | <code>UiControl</code> | the control will be inserted before this position |
| at | <code>number</code> | [description] |
| xspan | <code>number</code> | [description] |
| yspan | <code>number</code> | [description] |
| hexpand | <code>number</code> | [description] |
| halign | <code>number</code> | [description] |
| vexpan | <code>number</code> | [description] |
| valign | <code>number</code> | [description] |

<a name="UiGrid+append"></a>

### uiGrid.append(child, left, top, xspan, yspan, hexpand, halign, vexpand, valign) ⇒ <code>undefined</code>
Insert a new child control.

**Kind**: instance method of [<code>UiGrid</code>](#UiGrid)  

| Param | Type | Description |
| --- | --- | --- |
| child | <code>UiControl</code> | the control to add as child. |
| left | <code>number</code> | [description] |
| top | <code>number</code> | [description] |
| xspan | <code>number</code> | [description] |
| yspan | <code>number</code> | [description] |
| hexpand | <code>number</code> | [description] |
| halign | <code>number</code> | [description] |
| vexpand | <code>number</code> | [description] |
| valign | <code>number</code> | [description] |

