<a name="UiMultilineEntry"></a>

## UiMultilineEntry
A multiline text entry.

**Kind**: global class  

* [UiMultilineEntry](#UiMultilineEntry)
    * [new UiMultilineEntry()](#new_UiMultilineEntry_new)
    * [.text](#UiMultilineEntry+text) ⇒ <code>string</code>
    * [.getReadOnly()](#UiMultilineEntry+getReadOnly) ⇒ <code>boolean</code>
    * [.append(text)](#UiMultilineEntry+append) ⇒ <code>undefined</code>
    * [.onChanged(callback)](#UiMultilineEntry+onChanged) ⇒ <code>undefined</code>

<a name="new_UiMultilineEntry_new"></a>

### new UiMultilineEntry()
Create a new UiMultilineEntry object.

<a name="UiMultilineEntry+text"></a>

### uiMultilineEntry.text ⇒ <code>string</code>
Set or return the the content of the multiline entry.

**Kind**: instance property of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  
<a name="UiMultilineEntry+getReadOnly"></a>

### uiMultilineEntry.getReadOnly() ⇒ <code>boolean</code>
Whether the user is allowed to change the entry text.

**Kind**: instance method of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  
<a name="UiMultilineEntry+append"></a>

### uiMultilineEntry.append(text) ⇒ <code>undefined</code>
Append specified text to the entry content.

**Kind**: instance method of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the text to append. |

<a name="UiMultilineEntry+onChanged"></a>

### uiMultilineEntry.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the entry content changed.

**Kind**: instance method of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

