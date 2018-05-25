
<a id="uimultilineentry"></a>
## UiMultilineEntry ⇐ <code>UiControl</code>
A multiline text entry.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiMultilineEntry](#UiMultilineEntry) ⇐ <code>UiControl</code>
    * [new UiMultilineEntry()](#new_UiMultilineEntry_new)
    * [.text](#UiMultilineEntry_text) ⇒ <code>string</code>
    * [.readOnly](#UiMultilineEntry_readOnly) ⇒ <code>boolean</code>
    * [.append(text)](#UiMultilineEntry_append)
    * [.onChanged(callback)](#UiMultilineEntry_onChanged)
    * [.enabled](#UiMultilineEntry_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiMultilineEntry_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiMultilineEntry_toplevel) ⇒ <code>boolean</code>


<a id="new_uimultilineentry_new"></a>
### new UiMultilineEntry()
Create a new UiMultilineEntry object.


<a id="uimultilineentry_text"></a>
### uiMultilineEntry.text ⇒ <code>string</code>
Set or return the the content of the multiline entry.

**Kind**: instance property of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  

<a id="uimultilineentry_readonly"></a>
### uiMultilineEntry.readOnly ⇒ <code>boolean</code>
Whether the user is allowed to change the entry's contents.

**Kind**: instance property of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  

<a id="uimultilineentry_append"></a>
### uiMultilineEntry.append(text)
Append the specified text to the entry's contents.

**Kind**: instance method of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the text to append. |


<a id="uimultilineentry_onchanged"></a>
### uiMultilineEntry.onChanged(callback)
Add a listener to the `changed` event. Emitted whenever the entry's contents
changed.

**Kind**: instance method of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |


<a id="uimultilineentry_enabled"></a>
### uiMultilineEntry.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  

<a id="uimultilineentry_visible"></a>
### uiMultilineEntry.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  

<a id="uimultilineentry_toplevel"></a>
### uiMultilineEntry.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  
