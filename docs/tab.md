<a name="UiTab"></a>

## UiTab ⇐ <code>UiControl</code>
A container that show each chidren in a separate tab.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiTab](#UiTab) ⇐ <code>UiControl</code>
    * [new UiTab()](#new_UiTab_new)
    * [.margined](#UiTab+margined) ⇒ <code>boolean</code>
    * [.append(control, string)](#UiTab+append) ⇒ <code>undefined</code>
    * [.insertAt(label, before, control)](#UiTab+insertAt) ⇒ <code>undefined</code>
    * [.numPages()](#UiTab+numPages) ⇒ <code>number</code>
    * [.deleteAt(index)](#UiTab+deleteAt) ⇒ <code>undefined</code>
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

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
| control | <code>UiControl</code> | the control to add as a child. |
| string | <code>boolean</code> | the text to show for the new page caption. |

<a name="UiTab+insertAt"></a>

### uiTab.insertAt(label, before, control) ⇒ <code>undefined</code>
Insert a new child control before specified position.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  

| Param | Type | Description |
| --- | --- | --- |
| label | <code>string</code> | the text to show for the new page caption. |
| before | <code>number</code> | the control will be inserted before this position |
| control | <code>UiControl</code> | the control to insert |

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

<a name=""></a>

### uiTab.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiTab</code>](#UiTab)  
<a name=""></a>

### uiTab.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiTab</code>](#UiTab)  
<a name=""></a>

### uiTab.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiTab</code>](#UiTab)  
