## Classes

<dl>
<dt><a href="#UiSearchEntry">UiSearchEntry</a> ⇐ <code>UiEntryBase</code></dt>
<dd><p>A single line text entry control to search text.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiSearchEntry"></a>

## UiSearchEntry ⇐ <code>UiEntryBase</code>
A single line text entry control to search text.

**Kind**: global class  
**Extends**: <code>UiEntryBase</code>  

* [UiSearchEntry](#UiSearchEntry) ⇐ <code>UiEntryBase</code>
    * [new UiSearchEntry()](#new_UiSearchEntry_new)
    * [.text](#UiEntryBase+text) ⇒ <code>string</code>
    * [.readOnly](#UiEntryBase+readOnly) ⇒ <code>boolean</code>
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
<a name="UiEntryBase+onChanged"></a>

### uiSearchEntry.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the entry contents
changed.

**Kind**: instance method of [<code>UiSearchEntry</code>](#UiSearchEntry)  

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
