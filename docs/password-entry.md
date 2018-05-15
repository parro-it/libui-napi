<a name="UiPasswordEntry"></a>

## UiPasswordEntry ⇐ <code>UiEntryBase</code>
A single line text entry control that hides the input, useful for passwords
and other sensible data.

**Kind**: global class  
**Extends**: <code>UiEntryBase</code>  

* [UiPasswordEntry](#UiPasswordEntry) ⇐ <code>UiEntryBase</code>
    * [new UiPasswordEntry()](#new_UiPasswordEntry_new)
    * [.text](#) ⇒ <code>string</code>
    * [.readOnly](#) ⇒ <code>boolean</code>
    * [.onChanged(callback)](#) ⇒ <code>undefined</code>
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiPasswordEntry_new"></a>

### new UiPasswordEntry()
Create a new UiPasswordEntry object.

<a name=""></a>

### uiPasswordEntry.text ⇒ <code>string</code>
Set or return the the content of the entry.

**Kind**: instance property of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  
<a name=""></a>

### uiPasswordEntry.readOnly ⇒ <code>boolean</code>
Whether the user is allowed to change the entry's contents.

**Kind**: instance property of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  
<a name=""></a>

### uiPasswordEntry.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the entry contents
changed.

**Kind**: instance method of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |

<a name=""></a>

### uiPasswordEntry.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  
<a name=""></a>

### uiPasswordEntry.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  
<a name=""></a>

### uiPasswordEntry.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  
