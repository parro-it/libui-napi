## Classes

<dl>
<dt><a href="#UiMenu">UiMenu</a></dt>
<dd><p>The top bar on a window that can have multiple items.
The menu must be created before the first UiWindow for it to take effect.
It is made up of UiMenuItem instances.</p>
</dd>
<dt><a href="#UiMenuItem">UiMenuItem</a></dt>
<dd></dd>
</dl>

<a name="UiMenu"></a>

## UiMenu
The top bar on a window that can have multiple items.
The menu must be created before the first UiWindow for it to take effect.
It is made up of UiMenuItem instances.

**Kind**: global class  

* [UiMenu](#UiMenu)
    * [new UiMenu(caption)](#new_UiMenu_new)
    * [.appendItem(caption)](#UiMenu+appendItem) ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
    * [.appendCheckItem(caption)](#UiMenu+appendCheckItem) ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
    * [.appendQuitItem()](#UiMenu+appendQuitItem) ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
    * [.appendPreferencesItem()](#UiMenu+appendPreferencesItem) ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
    * [.appendAboutItem()](#UiMenu+appendAboutItem) ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
    * [.appendSeparator()](#UiMenu+appendSeparator) ⇒ [<code>UiMenuItem</code>](#UiMenuItem)

<a name="new_UiMenu_new"></a>

### new UiMenu(caption)
Create a new UiMenu object.


| Param | Type | Description |
| --- | --- | --- |
| caption | <code>string</code> | The caption of the menu. |

<a name="UiMenu+appendItem"></a>

### uiMenu.appendItem(caption) ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
Append a normal menu button.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: [<code>UiMenuItem</code>](#UiMenuItem) - the new appended UiMenuItem  

| Param | Type | Description |
| --- | --- | --- |
| caption | <code>string</code> | The caption of the menu item. |

<a name="UiMenu+appendCheckItem"></a>

### uiMenu.appendCheckItem(caption) ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
Append a menu button with a checkable option.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: [<code>UiMenuItem</code>](#UiMenuItem) - the new appended UiMenuItem  

| Param | Type | Description |
| --- | --- | --- |
| caption | <code>String</code> | The caption of the menu item. |

<a name="UiMenu+appendQuitItem"></a>

### uiMenu.appendQuitItem() ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
Append a Quit button. This accepts no text, the caption defaults to `Quit`.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: [<code>UiMenuItem</code>](#UiMenuItem) - the new appended UiMenuItem  
<a name="UiMenu+appendPreferencesItem"></a>

### uiMenu.appendPreferencesItem() ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
Append a Preferences button. This accepts no text, the caption defaults to `Preferences`.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: [<code>UiMenuItem</code>](#UiMenuItem) - the new appended UiMenuItem  
<a name="UiMenu+appendAboutItem"></a>

### uiMenu.appendAboutItem() ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
Append an About button. This accepts no text, the caption defaults to `About`.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: [<code>UiMenuItem</code>](#UiMenuItem) - the new appended UiMenuItem  
<a name="UiMenu+appendSeparator"></a>

### uiMenu.appendSeparator() ⇒ [<code>UiMenuItem</code>](#UiMenuItem)
Append a Separator between menu items.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: [<code>UiMenuItem</code>](#UiMenuItem) - the new appended UiMenuItem  
<a name="UiMenuItem"></a>

## UiMenuItem
**Kind**: global class  

* [UiMenuItem](#UiMenuItem)
    * [new UiMenuItem()](#new_UiMenuItem_new)
    * [.checked](#UiMenuItem+checked) ⇒ <code>boolean</code>
    * [.enable()](#UiMenuItem+enable) ⇒ <code>undefined</code>
    * [.disable()](#UiMenuItem+disable) ⇒ <code>undefined</code>
    * [.onClicked(callback)](#UiMenuItem+onClicked) ⇒ <code>undefined</code>

<a name="new_UiMenuItem_new"></a>

### new UiMenuItem()
Create a new UiMenuItem object.

<a name="UiMenuItem+checked"></a>

### uiMenuItem.checked ⇒ <code>boolean</code>
If the item is created using appendCheckItem, then set whether it is checked or not.

**Kind**: instance property of [<code>UiMenuItem</code>](#UiMenuItem)  
<a name="UiMenuItem+enable"></a>

### uiMenuItem.enable() ⇒ <code>undefined</code>
Enable the menu item.

**Kind**: instance method of [<code>UiMenuItem</code>](#UiMenuItem)  
<a name="UiMenuItem+disable"></a>

### uiMenuItem.disable() ⇒ <code>undefined</code>
Disable the menu item

**Kind**: instance method of [<code>UiMenuItem</code>](#UiMenuItem)  
<a name="UiMenuItem+onClicked"></a>

### uiMenuItem.onClicked(callback) ⇒ <code>undefined</code>
Register a callback for the click event of the menu item.

**Kind**: instance method of [<code>UiMenuItem</code>](#UiMenuItem)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | the function to register as callback for the event. |

