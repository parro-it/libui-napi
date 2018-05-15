<a name="UiArea"></a>

## UiArea ⇐ <code>UiControl</code>
An area to draw on.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiArea](#UiArea) ⇐ <code>UiControl</code>
    * [new UiArea(draw, mouse, mouseCrossed, dragBroken, keyEvent)](#new_UiArea_new)
    * [.queueRedrawAll()](#UiArea+queueRedrawAll)
    * [.beginWindowMove()](#UiArea+beginWindowMove)
    * [.beginWindowResize(edge)](#UiArea+beginWindowResize)
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiArea_new"></a>

### new UiArea(draw, mouse, mouseCrossed, dragBroken, keyEvent)
Create a new UiArea object.


| Param | Type | Description |
| --- | --- | --- |
| draw | <code>function</code> | callback to draw onto area |
| mouse | <code>function</code> | callback for mouse events |
| mouseCrossed | <code>function</code> | callback for entering or leaving the area |
| dragBroken | <code>function</code> | callback |
| keyEvent | <code>function</code> | callback for key events |

<a name="UiArea+queueRedrawAll"></a>

### uiArea.queueRedrawAll()
Force a redraw of the area (calls draw callback).

**Kind**: instance method of [<code>UiArea</code>](#UiArea)  
<a name="UiArea+beginWindowMove"></a>

### uiArea.beginWindowMove()
Let the mouse move the window (only callable in the draw callback)

**Kind**: instance method of [<code>UiArea</code>](#UiArea)  
<a name="UiArea+beginWindowResize"></a>

### uiArea.beginWindowResize(edge)
Let the mouse resize the window (only callable in the draw callback)

**Kind**: instance method of [<code>UiArea</code>](#UiArea)  

| Param | Type | Description |
| --- | --- | --- |
| edge | <code>number</code> | the size which is held by the mouse |

<a name=""></a>

### uiArea.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiArea</code>](#UiArea)  
<a name=""></a>

### uiArea.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiArea</code>](#UiArea)  
<a name=""></a>

### uiArea.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiArea</code>](#UiArea)  
