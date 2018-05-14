## Classes

<dl>
<dt><a href="#UiArea">UiArea</a></dt>
<dd><p>An area to draw on.</p>
</dd>
<dt><a href="#DrawBrush">DrawBrush</a></dt>
<dd><p>A draw brush</p>
</dd>
</dl>

<a name="UiArea"></a>

## UiArea
An area to draw on.

**Kind**: global class  

* [UiArea](#UiArea)
    * [new UiArea(draw, mouse, mouseCrossed, dragBroken, keyEvent)](#new_UiArea_new)
    * [.queueRedrawAll()](#UiArea+queueRedrawAll) ⇒ <code>undefined</code>
    * [.beginWindowMove()](#UiArea+beginWindowMove) ⇒ <code>undefined</code>
    * [.beginWindowResize(edge)](#UiArea+beginWindowResize) ⇒ <code>undefined</code>

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
<a name="UiArea+beginWindowMove"></a>

### uiArea.beginWindowMove() ⇒ <code>undefined</code>
Let the mouse move the window (only callable in the draw callback)

**Kind**: instance method of [<code>UiArea</code>](#UiArea)  
<a name="UiArea+beginWindowResize"></a>

### uiArea.beginWindowResize(edge) ⇒ <code>undefined</code>
Let the mouse resize the window (only callable in the draw callback)

**Kind**: instance method of [<code>UiArea</code>](#UiArea)  

| Param | Type | Description |
| --- | --- | --- |
| edge | <code>number</code> | the size which is held by the mouse |

<a name="DrawBrush"></a>

## DrawBrush
A draw brush

**Kind**: global class  

* [DrawBrush](#DrawBrush)
    * [.stops](#DrawBrush+stops) ⇒ <code>string</code>
    * [.stops](#DrawBrush+stops) ⇒ <code>Array.&lt;BrushGradientStop&gt;</code>
    * [.start](#DrawBrush+start) ⇒ <code>undefined</code>
    * [.start](#DrawBrush+start) ⇒ <code>Object</code>
    * [.end](#DrawBrush+end) ⇒ <code>undefined</code>
    * [.end](#DrawBrush+end) ⇒ <code>Object</code>
    * [.outerRadius](#DrawBrush+outerRadius) ⇒ <code>undefined</code>
    * [.outerRadius](#DrawBrush+outerRadius) ⇒ <code>number</code>

<a name="DrawBrush+stops"></a>

### drawBrush.stops ⇒ <code>string</code>
Set the gradient stops

**Kind**: instance property of [<code>DrawBrush</code>](#DrawBrush)  

| Param | Type | Description |
| --- | --- | --- |
| value | <code>Array.&lt;BrushGradientStop&gt;</code> | the gradients stops |

<a name="DrawBrush+stops"></a>

### drawBrush.stops ⇒ <code>Array.&lt;BrushGradientStop&gt;</code>
Get the gradient stops

**Kind**: instance property of [<code>DrawBrush</code>](#DrawBrush)  
<a name="DrawBrush+start"></a>

### drawBrush.start ⇒ <code>undefined</code>
Set the start position of the gradient
(Radial gradients: the inner circle's center)

**Kind**: instance property of [<code>DrawBrush</code>](#DrawBrush)  

| Param | Type | Description |
| --- | --- | --- |
| pos | <code>Object</code> | the coordinates |

<a name="DrawBrush+start"></a>

### drawBrush.start ⇒ <code>Object</code>
Get the start position of the gradient
(Radial gradients: the inner circle's center)

**Kind**: instance property of [<code>DrawBrush</code>](#DrawBrush)  
<a name="DrawBrush+end"></a>

### drawBrush.end ⇒ <code>undefined</code>
Set the end position of the gradient
(Radial gradients: the outer circle's center)

**Kind**: instance property of [<code>DrawBrush</code>](#DrawBrush)  

| Param | Type | Description |
| --- | --- | --- |
| pos | <code>Object</code> | the coordinates |

<a name="DrawBrush+end"></a>

### drawBrush.end ⇒ <code>Object</code>
Get the end position of the gradient
(Radial gradients: the outer circle's center)

**Kind**: instance property of [<code>DrawBrush</code>](#DrawBrush)  
<a name="DrawBrush+outerRadius"></a>

### drawBrush.outerRadius ⇒ <code>undefined</code>
Set the radius of the gradient's outer circle (radial gradients only)

**Kind**: instance property of [<code>DrawBrush</code>](#DrawBrush)  

| Param | Type | Description |
| --- | --- | --- |
| r | <code>number</code> | the outer radius |

<a name="DrawBrush+outerRadius"></a>

### drawBrush.outerRadius ⇒ <code>number</code>
Get the radius of the gradient's outer circle (radial gradients only)

**Kind**: instance property of [<code>DrawBrush</code>](#DrawBrush)  
