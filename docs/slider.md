<a name="UiSlider"></a>

## UiSlider ⇐ <code>UiControl</code>
Horizontal slider to set numerical values.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiSlider](#UiSlider) ⇐ <code>UiControl</code>
    * [new UiSlider(min, max)](#new_UiSlider_new)
    * [.value](#UiSlider+value) ⇒ <code>number</code>
    * [.onChanged(callback)](#UiSlider+onChanged)
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiSlider_new"></a>

### new UiSlider(min, max)
Create a new UiSlider object.


| Param | Type | Default | Description |
| --- | --- | --- | --- |
| min | <code>number</code> | <code>0</code> | minimum value of the slider. |
| max | <code>number</code> | <code>100</code> | maximum value of the slider. |

<a name="UiSlider+value"></a>

### uiSlider.value ⇒ <code>number</code>
Set or return the the content of the slider.

**Kind**: instance property of [<code>UiSlider</code>](#UiSlider)  
<a name="UiSlider+onChanged"></a>

### uiSlider.onChanged(callback)
Add a listener to the `changed` event. Emitted whenever the slider value
changed.

**Kind**: instance method of [<code>UiSlider</code>](#UiSlider)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name=""></a>

### uiSlider.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiSlider</code>](#UiSlider)  
<a name=""></a>

### uiSlider.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiSlider</code>](#UiSlider)  
<a name=""></a>

### uiSlider.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiSlider</code>](#UiSlider)  
