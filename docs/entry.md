## Classes

<dl>
<dt><a href="#UiEntry">UiEntry</a> ⇐ <code><a href="#UiEntryBase">UiEntryBase</a></code></dt>
<dd><p>A simple, single line text entry control.</p>
</dd>
<dt><a href="#UiEntryBase">UiEntryBase</a> ⇐ <code><a href="#UiControl">UiControl</a></code></dt>
<dd><p>A base class for text related entries.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiEntry"></a>

## UiEntry ⇐ [<code>UiEntryBase</code>](#UiEntryBase)
A simple, single line text entry control.

**Kind**: global class  
**Extends**: [<code>UiEntryBase</code>](#UiEntryBase)  

* [UiEntry](#UiEntry) ⇐ [<code>UiEntryBase</code>](#UiEntryBase)
    * [new UiEntry()](#new_UiEntry_new)
    * [.text](#UiEntryBase+text) ⇒ <code>string</code>
    * [.readOnly](#UiEntryBase+readOnly) ⇒ <code>boolean</code>
    * [.enabled](#UiControl+enabled) ⇒ <code>boolean</code>
    * [.visible](#UiControl+visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiControl+toplevel) ⇒ <code>boolean</code>
    * [.onChanged(callback)](#UiEntryBase+onChanged) ⇒ <code>undefined</code>

<a name="new_UiEntry_new"></a>

### new UiEntry()
Create a new UiEntry object.

<a name="UiEntryBase+text"></a>

### uiEntry.text ⇒ <code>string</code>
Set or return the the content of the entry.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  
<a name="UiEntryBase+readOnly"></a>

### uiEntry.readOnly ⇒ <code>boolean</code>
Whether the user is allowed to change the entry's contents.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  
<a name="UiControl+enabled"></a>

### uiEntry.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  
<a name="UiControl+visible"></a>

### uiEntry.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  
<a name="UiControl+toplevel"></a>

### uiEntry.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  
<a name="UiEntryBase+onChanged"></a>

### uiEntry.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the entry contents
changed.

**Kind**: instance method of [<code>UiEntry</code>](#UiEntry)  

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
