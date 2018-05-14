## Classes

<dl>
<dt><a href="#UiForm">UiForm</a> ⇐ <code><a href="#UiControl">UiControl</a></code></dt>
<dd><p>A container that organizes children as labeled fields.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiForm"></a>

## UiForm ⇐ [<code>UiControl</code>](#UiControl)
A container that organizes children as labeled fields.

**Kind**: global class  
**Extends**: [<code>UiControl</code>](#UiControl)  

* [UiForm](#UiForm) ⇐ [<code>UiControl</code>](#UiControl)
    * [new UiForm()](#new_UiForm_new)
    * [.padded](#UiForm+padded) ⇒ <code>boolean</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
    * [.append(label, control, stretchy)](#UiForm+append) ⇒ <code>undefined</code>
    * [.deleteAt(index)](#UiForm+deleteAt) ⇒ <code>undefined</code>

<a name="new_UiForm_new"></a>

### new UiForm()
Create a new UiForm object.

<a name="UiForm+padded"></a>

### uiForm.padded ⇒ <code>boolean</code>
If true, the container inserts some space between children.

**Kind**: instance property of [<code>UiForm</code>](#UiForm)  
<a name="UiControl+enabled"></a>

### uiForm.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiForm</code>](#UiForm)  
<a name="UiControl+visible"></a>

### uiForm.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiForm</code>](#UiForm)  
<a name="UiControl+toplevel"></a>

### uiForm.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiForm</code>](#UiForm)  
<a name="UiForm+append"></a>

### uiForm.append(label, control, stretchy) ⇒ <code>undefined</code>
Append a new child control as the last field with the specified label.

**Kind**: instance method of [<code>UiForm</code>](#UiForm)  

| Param | Type | Description |
| --- | --- | --- |
| label | <code>string</code> | the text to use as label of the field. |
| control | [<code>UiControl</code>](#UiControl) | the control to add as child. |
| stretchy | <code>boolean</code> | whether the control should fill all the available space. |

<a name="UiForm+deleteAt"></a>

### uiForm.deleteAt(index) ⇒ <code>undefined</code>
Remove a child control at the specified position.

**Kind**: instance method of [<code>UiForm</code>](#UiForm)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the control to remove |

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
