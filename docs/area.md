## Classes

<dl>
<dt><a href="#UiArea">UiArea</a></dt>
<dd><p>An area to draw on.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

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
<a name="UiControl"></a>

## UiControl
Base class for all controls.

**Kind**: global class  

* [UiControl](#UiControl)
    * [new UiControl()](#new_UiControl_new)
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>

<a name="new_UiControl_new"></a>

### new UiControl()
Create a new UiControl object.

<a name="UiControl+enabled"></a>

### uiControl.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiControl</code>](#UiControl)  
<a name="UiControl+visible"></a>

### uiControl.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiControl</code>](#UiControl)  
<a name="UiControl+toplevel"></a>

### uiControl.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiControl</code>](#UiControl)  
