<a name="UiForm"></a>

## UiForm
A container that organize children as labeled fields.

**Kind**: global class  

* [UiForm](#UiForm)
    * [new UiForm()](#new_UiForm_new)
    * [.getPadded()](#UiForm+getPadded) ⇒ <code>boolean</code>
    * [.append(label, control, stretchy)](#UiForm+append) ⇒ <code>undefined</code>
    * [.deleteAt(index)](#UiForm+deleteAt) ⇒ <code>undefined</code>

<a name="new_UiForm_new"></a>

### new UiForm()
Create a new UiForm object.

<a name="UiForm+getPadded"></a>

### uiForm.getPadded() ⇒ <code>boolean</code>
If true, the container insert some space between children.

**Kind**: instance method of [<code>UiForm</code>](#UiForm)  
<a name="UiForm+append"></a>

### uiForm.append(label, control, stretchy) ⇒ <code>undefined</code>
Append a new child control as last field with specified label.

**Kind**: instance method of [<code>UiForm</code>](#UiForm)  

| Param | Type | Description |
| --- | --- | --- |
| label | <code>string</code> | the text to use as label of the field. |
| control | <code>UiControl</code> | the control to add as child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |

<a name="UiForm+deleteAt"></a>

### uiForm.deleteAt(index) ⇒ <code>undefined</code>
Remove a child control at specified position.

**Kind**: instance method of [<code>UiForm</code>](#UiForm)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |

