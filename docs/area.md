## Classes

<dl>
<dt><a href="#UiArea">UiArea</a></dt>
<dd><p>An area to draw on.</p>
</dd>
<dt><a href="#AreaDrawBrush">AreaDrawBrush</a></dt>
<dd><p>A solid draw brush</p>
</dd>
<dt><a href="#AreaDrawBrushGradient">AreaDrawBrushGradient</a></dt>
<dd><p>A gradient brush</p>
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

<a name="AreaDrawBrush"></a>

## AreaDrawBrush
A solid draw brush

**Kind**: global class  
<a name="new_AreaDrawBrush_new"></a>

### new AreaDrawBrush(r, g, b, a)

| Param | Type | Description |
| --- | --- | --- |
| r | <code>number</code> | the red component (0-1) |
| g | <code>number</code> | the blue component (0-1) |
| b | <code>number</code> | the blue component (0-1) |
| a | <code>number</code> | the alpha component (0-1) |

<a name="AreaDrawBrushGradient"></a>

## AreaDrawBrushGradient
A gradient brush

**Kind**: global class  

* [AreaDrawBrushGradient](#AreaDrawBrushGradient)
    * [new AreaDrawBrushGradient(type)](#new_AreaDrawBrushGradient_new)
    * [.stops](#AreaDrawBrushGradient+stops) ⇒ <code>string</code>
    * [.stops](#AreaDrawBrushGradient+stops) ⇒ <code>Array.&lt;AreaDrawBrushGradient.Stop&gt;</code>
    * [.start](#AreaDrawBrushGradient+start) ⇒ <code>undefined</code>
    * [.start](#AreaDrawBrushGradient+start) ⇒ <code>Object</code>
    * [.end](#AreaDrawBrushGradient+end) ⇒ <code>undefined</code>
    * [.end](#AreaDrawBrushGradient+end) ⇒ <code>Object</code>
    * [.outerRadius](#AreaDrawBrushGradient+outerRadius) ⇒ <code>undefined</code>
    * [.outerRadius](#AreaDrawBrushGradient+outerRadius) ⇒ <code>number</code>

<a name="new_AreaDrawBrushGradient_new"></a>

### new AreaDrawBrushGradient(type)

| Param | Type | Description |
| --- | --- | --- |
| type | <code>number</code> | the gradient type |

<a name="AreaDrawBrushGradient+stops"></a>

### areaDrawBrushGradient.stops ⇒ <code>string</code>
Set the gradient stops

**Kind**: instance property of [<code>AreaDrawBrushGradient</code>](#AreaDrawBrushGradient)  

| Param | Type | Description |
| --- | --- | --- |
| value | <code>Array.&lt;AreaDrawBrushGradient.Stop&gt;</code> | the gradients stops |

<a name="AreaDrawBrushGradient+stops"></a>

### areaDrawBrushGradient.stops ⇒ <code>Array.&lt;AreaDrawBrushGradient.Stop&gt;</code>
Get the gradient stops

**Kind**: instance property of [<code>AreaDrawBrushGradient</code>](#AreaDrawBrushGradient)  
<a name="AreaDrawBrushGradient+start"></a>

### areaDrawBrushGradient.start ⇒ <code>undefined</code>
Set the start position of the gradient
(Radial gradients: the inner circle's center)

**Kind**: instance property of [<code>AreaDrawBrushGradient</code>](#AreaDrawBrushGradient)  

| Param | Type | Description |
| --- | --- | --- |
| pos | <code>Object</code> | the coordinates |

<a name="AreaDrawBrushGradient+start"></a>

### areaDrawBrushGradient.start ⇒ <code>Object</code>
Get the start position of the gradient
(Radial gradients: the inner circle's center)

**Kind**: instance property of [<code>AreaDrawBrushGradient</code>](#AreaDrawBrushGradient)  
<a name="AreaDrawBrushGradient+end"></a>

### areaDrawBrushGradient.end ⇒ <code>undefined</code>
Set the end position of the gradient
(Radial gradients: the outer circle's center)

**Kind**: instance property of [<code>AreaDrawBrushGradient</code>](#AreaDrawBrushGradient)  

| Param | Type | Description |
| --- | --- | --- |
| pos | <code>Object</code> | the coordinates |

<a name="AreaDrawBrushGradient+end"></a>

### areaDrawBrushGradient.end ⇒ <code>Object</code>
Get the end position of the gradient
(Radial gradients: the outer circle's center)

**Kind**: instance property of [<code>AreaDrawBrushGradient</code>](#AreaDrawBrushGradient)  
<a name="AreaDrawBrushGradient+outerRadius"></a>

### areaDrawBrushGradient.outerRadius ⇒ <code>undefined</code>
Set the radius of the gradient's outer circle (radial gradients only)

**Kind**: instance property of [<code>AreaDrawBrushGradient</code>](#AreaDrawBrushGradient)  

| Param | Type | Description |
| --- | --- | --- |
| r | <code>number</code> | the outer radius |

<a name="AreaDrawBrushGradient+outerRadius"></a>

### areaDrawBrushGradient.outerRadius ⇒ <code>number</code>
Get the radius of the gradient's outer circle (radial gradients only)

**Kind**: instance property of [<code>AreaDrawBrushGradient</code>](#AreaDrawBrushGradient)  
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
