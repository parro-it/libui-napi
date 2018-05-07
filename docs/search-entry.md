<a name="UiSearchEntry"></a>

## UiSearchEntry ⇐ <code>UiEntryBase</code>
A single line text entry widget to search text.

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
Whether the user is allowed to change the entry text.

**Kind**: instance property of [<code>UiSearchEntry</code>](#UiSearchEntry)  
<a name="UiEntryBase+onChanged"></a>

### uiSearchEntry.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the entry content changed.

**Kind**: instance method of [<code>UiSearchEntry</code>](#UiSearchEntry)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

