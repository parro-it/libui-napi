
<a id="uitab"></a>
## UiTab ⇐ <code>UiControl</code>
A container that show each chidren in a separate tab.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiTab](#UiTab) ⇐ <code>UiControl</code>
    * [new UiTab()](#new_UiTab_new)
    * [.getMargined(index)](#UiTab_getMargined) ⇒ <code>boolean</code>
    * [.setMargined(index, value)](#UiTab_setMargined)
    * [.append(control, string)](#UiTab_append)
    * [.insertAt(label, before, control)](#UiTab_insertAt)
    * [.numPages()](#UiTab_numPages) ⇒ <code>number</code>
    * [.deleteAt(index)](#UiTab_deleteAt)
    * [.enabled](#UiTab_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiTab_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiTab_toplevel) ⇒ <code>boolean</code>


<a id="new_uitab_new"></a>
### new UiTab()
Create a new UiTab object.


<a id="uitab_getmargined"></a>
### uiTab.getMargined(index) ⇒ <code>boolean</code>
Return whether an internal margin is added to a page of the tab.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  
**Returns**: <code>boolean</code> - - whether the page has margins  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the page to check. |


<a id="uitab_setmargined"></a>
### uiTab.setMargined(index, value)
Add an internal margin to a page of the Tab.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the page to set the margin on. |
| value | <code>boolean</code> | whether to enable or disable the margin. |


<a id="uitab_append"></a>
### uiTab.append(control, string)
Append a new child control as last tab page.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  

| Param | Type | Description |
| --- | --- | --- |
| control | <code>UiControl</code> | the control to add as a child. |
| string | <code>boolean</code> | the text to show for the new page caption. |


<a id="uitab_insertat"></a>
### uiTab.insertAt(label, before, control)
Insert a new child control before specified position.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  

| Param | Type | Description |
| --- | --- | --- |
| label | <code>string</code> | the text to show for the new page caption. |
| before | <code>number</code> | the control will be inserted before this position |
| control | <code>UiControl</code> | the control to insert |


<a id="uitab_numpages"></a>
### uiTab.numPages() ⇒ <code>number</code>
Return the total number of tab pages contained in the control.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  
**Returns**: <code>number</code> - number of pages  

<a id="uitab_deleteat"></a>
### uiTab.deleteAt(index)
Remove the tab and control at specified position.

**Kind**: instance method of [<code>UiTab</code>](#UiTab)  

| Param | Type | Description |
| --- | --- | --- |
| index | <code>number</code> | the index of the tab to remove. |


<a id="uitab_enabled"></a>
### uiTab.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiTab</code>](#UiTab)  

<a id="uitab_visible"></a>
### uiTab.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiTab</code>](#UiTab)  

<a id="uitab_toplevel"></a>
### uiTab.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiTab</code>](#UiTab)  
