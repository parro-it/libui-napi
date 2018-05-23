
<a id="uientry"></a>
## UiEntry ⇐ <code>UiEntryBase</code>
A simple, single line text entry control.

**Kind**: global class  
**Extends**: <code>UiEntryBase</code>  

* [UiEntry](#UiEntry) ⇐ <code>UiEntryBase</code>
    * [new UiEntry()](#new_UiEntry_new)
    * [.text](#UiEntry_text) ⇒ <code>string</code>
    * [.readOnly](#UiEntry_readOnly) ⇒ <code>boolean</code>
    * [.onChanged(callback)](#UiEntry_onChanged)
    * [.enabled](#UiEntry_enabled) ⇒ <code>boolean</code>
    * [.visible](#UiEntry_visible) ⇒ <code>boolean</code>
    * [.toplevel](#UiEntry_toplevel) ⇒ <code>boolean</code>


<a id="new_uientry_new"></a>
### new UiEntry()
Create a new UiEntry object.


<a id="uientry_text"></a>
### uiEntry.text ⇒ <code>string</code>
Set or return the the content of the entry.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  

<a id="uientry_readonly"></a>
### uiEntry.readOnly ⇒ <code>boolean</code>
Whether the user is allowed to change the entry's contents.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  

<a id="uientry_onchanged"></a>
### uiEntry.onChanged(callback)
Add a listener to the `changed` event. Emitted whenever the entry contents
changed.

**Kind**: instance method of [<code>UiEntry</code>](#UiEntry)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | callback to execute when the event is fired. |


<a id="uientry_enabled"></a>
### uiEntry.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  

<a id="uientry_visible"></a>
### uiEntry.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  

<a id="uientry_toplevel"></a>
### uiEntry.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiEntry</code>](#UiEntry)  
