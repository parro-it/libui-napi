<a name="UiForm"></a>

## UiForm ⇐ <code>UiControl</code>
A container that organizes children as labeled fields.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiForm](#UiForm) ⇐ <code>UiControl</code>
    * [new UiForm()](#new_UiForm_new)
    * [.padded](#UiForm+padded) ⇒ <code>boolean</code>
    * [.append(label, control, stretchy)](#UiForm+append) ⇒ <code>undefined</code>
    * [.deleteAt(index)](#UiForm+deleteAt) ⇒ <code>undefined</code>
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiForm_new"></a>

### new UiForm()
Create a new UiForm object.

<a name="UiForm+padded"></a>

### uiForm.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiForm</code>](#UiForm)  
<a name="UiForm+append"></a>

### uiForm.append(label, control, stretchy) ⇒ <code>undefined</code>
Append a new child control as the last field with the specified label.

**Kind**: instance method of [<code>UiForm</code>](#UiForm)  

| Param | Type | Description |
| --- | --- | --- |
| label | <code>string</code> | the text to use as label of the field. |
| control | <code>UiControl</code> | the control to add as child. |
| stretchy | <code>boolean</code> | whether the control should fill all the available space. |

<a name="UiForm+deleteAt"></a>

### uiForm.deleteAt(index) ⇒ <code>undefined</code>
Remove a child control at the specified position.

**Kind**: instance method of [<code>UiForm</code>](#UiForm)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |

<a name=""></a>

### uiForm.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiForm</code>](#UiForm)  
<a name=""></a>

### uiForm.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiForm</code>](#UiForm)  
<a name=""></a>

### uiForm.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiForm</code>](#UiForm)  
