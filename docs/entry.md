<a name="UiEntry"></a>

## UiEntry ⇐ <code>UiEntryBase</code>
A simple, single line text entry widget.

**Kind**: global class  
**Extends**: <code>UiEntryBase</code>  

* [UiEntry](#UiEntry) ⇐ <code>UiEntryBase</code>
    * [new UiEntry()](#new_UiEntry_new)
    * [.text](#UiEntryBase+text) ⇒ <code>string</code>
    * [.readOnly](#UiEntryBase+readOnly) ⇒ <code>boolean</code>
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
Whether the user is allowed to change the entry text.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  
<a name="UiEntryBase+onChanged"></a>

### uiEntry.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the entry content changed.

**Kind**: instance method of [<code>UiEntry</code>](#UiEntry)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

