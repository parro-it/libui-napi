## Classes

<dl>
<dt><a href="#UiSlider">UiSlider</a></dt>
<dd><p>Horizontal slider to set numerical values.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiSlider"></a>

## UiSlider
Horizontal slider to set numerical values.

**Kind**: global class  

* [UiSlider](#UiSlider)
    * [new UiSlider(min, max)](#new_UiSlider_new)
    * [.value](#UiSlider+value) ⇒ <code>number</code>
    * [.onChanged(callback)](#UiSlider+onChanged) ⇒ <code>undefined</code>

<a name="new_UiSlider_new"></a>

### new UiSlider(min, max)
Create a new UiSlider object.


| Param | Type | Description |
| --- | --- | --- |
| min | <code>number</code> | minimum value of the slider. |
| max | <code>number</code> | maximum value of the slider. |

<a name="UiSlider+value"></a>

### uiSlider.value ⇒ <code>number</code>
Set or return the the content of the slider.

**Kind**: instance property of [<code>UiSlider</code>](#UiSlider)  
<a name="UiSlider+onChanged"></a>

### uiSlider.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the slider value
changed.

**Kind**: instance method of [<code>UiSlider</code>](#UiSlider)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

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
