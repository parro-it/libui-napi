<a name="UiSearchEntry"></a>

## UiSearchEntry ⇐ <code>UiEntryBase</code>
A single line text entry control to search text.

**Kind**: global class  
**Extends**: <code>UiEntryBase</code>  

* [UiSearchEntry](#UiSearchEntry) ⇐ <code>UiEntryBase</code>
    * [new UiSearchEntry()](#new_UiSearchEntry_new)
    * [.text](#) ⇒ <code>string</code>
    * [.readOnly](#) ⇒ <code>boolean</code>
    * [.onChanged(callback)](#) ⇒ <code>undefined</code>
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiSearchEntry_new"></a>

### new UiSearchEntry()
Create a new UiSearchEntry object.

<a name=""></a>

### uiSearchEntry.text ⇒ <code>string</code>
Set or return the the content of the entry.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
<a name=""></a>

### uiSearchEntry.readOnly ⇒ <code>boolean</code>
Whether the user is allowed to change the entry's contents.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
<a name=""></a>

### uiSearchEntry.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the entry contents
changed.

**Kind**: instance method of [<code>UiSearchEntry</code>](#UiSearchEntry)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name=""></a>

### uiSearchEntry.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
<a name=""></a>

### uiSearchEntry.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
<a name=""></a>

### uiSearchEntry.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
