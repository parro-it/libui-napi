## Classes

<dl>
<dt><a href="#UiTab">UiTab</a></dt>
<dd><p>A container that show each chidren in a separate tab.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiTab"></a>

## UiTab
A container that show each chidren in a separate tab.

**Kind**: global class  

* [UiTab](#UiTab)
    * [new UiTab()](#new_UiTab_new)
    * [.margined](#UiTab+margined) ⇒ <code>boolean</code>
    * [.append(control, string)](#UiTab+append) ⇒ <code>undefined</code>
    * [.insertAt(label, before, control)](#UiTab+insertAt) ⇒ <code>undefined</code>
    * [.numPages()](#UiTab+numPages) ⇒ <code>number</code>
    * [.deleteAt(index)](#UiTab+deleteAt) ⇒ <code>undefined</code>

<a name="new_UiTab_new"></a>

### new UiTab()
Create a new UiTab object.

<a name="UiTab+margined"></a>

### uiTab.margined ⇒ <code>boolean</code>
When true, an internal margin is added to the Tab.

**Kind**: instance property of [<code>UiTab</code>](#UiTab)  
<a name="UiTab+append"></a>

### uiTab.append(control, string) ⇒ <code>undefined</code>
Append a new child control as last tab page.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  

| Param | Type | Description |
| --- | --- | --- |
| control | [<code>UiControl</code>](#UiControl) | the control to add as a child. |
| string | <code>boolean</code> | the text to show for the new page caption. |

<a name="UiTab+insertAt"></a>

### uiTab.insertAt(label, before, control) ⇒ <code>undefined</code>
Insert a new child control before specified position.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  

| Param | Type | Description |
| --- | --- | --- |
| label | <code>string</code> | the text to show for the new page caption. |
| before | <code>number</code> | the control will be inserted before this position |
| control | [<code>UiControl</code>](#UiControl) | the control to insert |

<a name="UiTab+numPages"></a>

### uiTab.numPages() ⇒ <code>number</code>
Return the total number of tab pages contained in the control.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  
**Returns**: <code>number</code> - number of pages  
<a name="UiTab+deleteAt"></a>

### uiTab.deleteAt(index) ⇒ <code>undefined</code>
Remove the tab and control at specified position.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the tab to remove. |

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
