
<a id="uipasswordentry"></a>
## UiPasswordEntry ⇐ <code>UiEntryBase</code>
A single line text entry control that hides the input, useful for passwords
and other sensible data.

**Kind**: global class  
**Extends**: <code>UiEntryBase</code>  

* [UiPasswordEntry](#UiPasswordEntry) ⇐ <code>UiEntryBase</code>
    * [new UiPasswordEntry()](#new_UiPasswordEntry_new)
    * [.text](#UiPasswordEntry_text) ⇒ <code>string</code>
    * [.readOnly](#UiPasswordEntry_readOnly) ⇒ <code>boolean</code>
    * [.onChanged(callback)](#UiPasswordEntry_onChanged)
    * [.enabled](#UiPasswordEntry_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiPasswordEntry_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiPasswordEntry_toplevel) ⇒ <code>boolean</code>


<a id="new_uipasswordentry_new"></a>
### new UiPasswordEntry()
Create a new UiPasswordEntry object.


<a id="uipasswordentry_text"></a>
### uiPasswordEntry.text ⇒ <code>string</code>
Set or return the the content of the entry.

**Kind**: instance property of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  

<a id="uipasswordentry_readonly"></a>
### uiPasswordEntry.readOnly ⇒ <code>boolean</code>
Whether the user is allowed to change the entry's contents.

**Kind**: instance property of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  

<a id="uipasswordentry_onchanged"></a>
### uiPasswordEntry.onChanged(callback)
Add a listener to the `changed` event. Emitted whenever the entry contents
changed.

**Kind**: instance method of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |


<a id="uipasswordentry_enabled"></a>
### uiPasswordEntry.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  

<a id="uipasswordentry_visible"></a>
### uiPasswordEntry.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  

<a id="uipasswordentry_toplevel"></a>
### uiPasswordEntry.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiPasswordEntry</code>](#UiPasswordEntry)  
