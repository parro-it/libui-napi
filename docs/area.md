<a name="UiArea"></a>

## UiArea
An area to draw on.

**Kind**: global class  

* [UiArea](#UiArea)
    * [new UiArea(draw, mouse, mouseCrossed, dragBroken, keyEvent)](#new_UiArea_new)
    * [.queueRedrawAll()](#UiArea+queueRedrawAll) ⇒ <code>undefined</code>

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

### uiArea.queueRedrawAll() ⇒ <code>undefined</code>
Force a redraw of the area (calls draw callback).

**Kind**: instance method of [<code>UiArea</code>](#UiArea)  
