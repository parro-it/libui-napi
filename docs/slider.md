<a name="UiSlider"></a>

## UiSlider
Horizontal slide to set numerical values.

**Kind**: global class

* [UiSlider](#UiSlider)
    * [new UiSlider(min, max)](#new_UiSlider_new)
    * [.value](#UiSlider+value) ⇒ <code>number</code>
    * [.onChanged(callback)](#UiSlider+onChanged) ⇒ <code>undefined</code>

<a name="new_UiSlider_new"></a>

### new UiSlider(min, max)

| Param | Type | Description |
| --- | --- | --- |
| min | <code>number</code> | minimum allowed value of the slider. |
| max | <code>number</code> | maximum allowed value of the slider. |

<a name="UiSlider+value"></a>

### uiSlider.value ⇒ <code>number</code>
Set or return the the content of the multiline entry.

**Kind**: instance property of [<code>UiSlider</code>](#UiSlider)
<a name="UiSlider+onChanged"></a>

### uiSlider.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the slider value changed.

**Kind**: instance method of [<code>UiSlider</code>](#UiSlider)

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

