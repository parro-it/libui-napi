## Classes

<dl>
<dt><a href="#UiSearchEntry">UiSearchEntry</a> ⇐ <code><a href="#UiEntryBase">UiEntryBase</a></code></dt>
<dd><p>A single line text entry control to search text.</p>
</dd>
<dt><a href="#UiEntryBase">UiEntryBase</a> ⇐ <code><a href="#UiControl">UiControl</a></code></dt>
<dd><p>A base class for text related entries.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiSearchEntry"></a>

## UiSearchEntry ⇐ [<code>UiEntryBase</code>](#UiEntryBase)
A single line text entry control to search text.

**Kind**: global class  
**Extends**: [<code>UiEntryBase</code>](#UiEntryBase)  

* [UiSearchEntry](#UiSearchEntry) ⇐ [<code>UiEntryBase</code>](#UiEntryBase)
    * [new UiSearchEntry()](#new_UiSearchEntry_new)
    * [.text](#UiEntryBase+text) ⇒ <code>string</code>
    * [.readOnly](#UiEntryBase+readOnly) ⇒ <code>boolean</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
    * [.onChanged(callback)](#UiEntryBase+onChanged) ⇒ <code>undefined</code>

<a name="new_UiSearchEntry_new"></a>

### new UiSearchEntry()
Create a new UiSearchEntry object.

<a name="UiEntryBase+text"></a>

### uiSearchEntry.text ⇒ <code>string</code>
Set or return the the content of the entry.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
<a name="UiEntryBase+readOnly"></a>

### uiSearchEntry.readOnly ⇒ <code>boolean</code>
Whether the user is allowed to change the entry's contents.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
<a name="UiControl+enabled"></a>

### uiSearchEntry.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
<a name="UiControl+visible"></a>

### uiSearchEntry.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
<a name="UiControl+toplevel"></a>

### uiSearchEntry.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
<a name="UiEntryBase+onChanged"></a>

### uiSearchEntry.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the entry contents
changed.

**Kind**: instance method of [<code>UiSearchEntry</code>](#UiSearchEntry)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name="UiEntryBase"></a>

## UiEntryBase ⇐ [<code>UiControl</code>](#UiControl)
A base class for text related entries.

**Kind**: global class  
**Extends**: [<code>UiControl</code>](#UiControl)  

* [UiEntryBase](#UiEntryBase) ⇐ [<code>UiControl</code>](#UiControl)
    * [.text](#UiEntryBase+text) ⇒ <code>string</code>
    * [.readOnly](#UiEntryBase+readOnly) ⇒ <code>boolean</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
    * [.onChanged(callback)](#UiEntryBase+onChanged) ⇒ <code>undefined</code>

<a name="UiEntryBase+text"></a>

### uiEntryBase.text ⇒ <code>string</code>
Set or return the the content of the entry.

**Kind**: instance property of [<code>UiEntryBase</code>](#UiEntryBase)  
<a name="UiEntryBase+readOnly"></a>

### uiEntryBase.readOnly ⇒ <code>boolean</code>
Whether the user is allowed to change the entry's contents.

**Kind**: instance property of [<code>UiEntryBase</code>](#UiEntryBase)  
<a name="UiControl+enabled"></a>

### uiEntryBase.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiEntryBase</code>](#UiEntryBase)  
<a name="UiControl+visible"></a>

### uiEntryBase.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiEntryBase</code>](#UiEntryBase)  
<a name="UiControl+toplevel"></a>

### uiEntryBase.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiEntryBase</code>](#UiEntryBase)  
<a name="UiEntryBase+onChanged"></a>

### uiEntryBase.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the entry contents
changed.

**Kind**: instance method of [<code>UiEntryBase</code>](#UiEntryBase)  

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
