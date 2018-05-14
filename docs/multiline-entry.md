## Classes

<dl>
<dt><a href="#UiMultilineEntry">UiMultilineEntry</a></dt>
<dd><p>A multiline text entry.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiMultilineEntry"></a>

## UiMultilineEntry
A multiline text entry.

**Kind**: global class  

* [UiMultilineEntry](#UiMultilineEntry)
    * [new UiMultilineEntry()](#new_UiMultilineEntry_new)
    * [.text](#UiMultilineEntry+text) ⇒ <code>string</code>
    * [.readOnly](#UiMultilineEntry+readOnly) ⇒ <code>boolean</code>
    * [.append(text)](#UiMultilineEntry+append) ⇒ <code>undefined</code>
    * [.onChanged(callback)](#UiMultilineEntry+onChanged) ⇒ <code>undefined</code>

<a name="new_UiMultilineEntry_new"></a>

### new UiMultilineEntry()
Create a new UiMultilineEntry object.

<a name="UiMultilineEntry+text"></a>

### uiMultilineEntry.text ⇒ <code>string</code>
Set or return the the content of the multiline entry.

**Kind**: instance property of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  
<a name="UiMultilineEntry+readOnly"></a>

### uiMultilineEntry.readOnly ⇒ <code>boolean</code>
Whether the user is allowed to change the entry's contents.

**Kind**: instance property of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  
<a name="UiMultilineEntry+append"></a>

### uiMultilineEntry.append(text) ⇒ <code>undefined</code>
Append the specified text to the entry's contents.

**Kind**: instance method of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  

| Param | Type | Description |
| --- | --- | --- |
| text | <code>string</code> | the text to append. |

<a name="UiMultilineEntry+onChanged"></a>

### uiMultilineEntry.onChanged(callback) ⇒ <code>undefined</code>
Add a listener to the `changed` event. Emitted whenever the entry's contents
changed.

**Kind**: instance method of [<code>UiMultilineEntry</code>](#UiMultilineEntry)  

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
