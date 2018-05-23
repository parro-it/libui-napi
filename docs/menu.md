
<a id="uimenu"></a>
## UiMenu
The top bar on a window that can have multiple items.
The menu must be created before the first UiWindow for it to take effect.
It is made up of UiMenuItem instances.

**Kind**: global class  

* [UiMenu](#UiMenu)
    * [new UiMenu(caption)](#new_UiMenu_new)
    * [.appendItem(caption)](#UiMenu_appendItem) ⇒ <code>UiMenuItem</code>
    * [.appendCheckItem(caption)](#UiMenu_appendCheckItem) ⇒ <code>UiMenuItem</code>
    * [.appendQuitItem()](#UiMenu_appendQuitItem) ⇒ <code>UiMenuItem</code>
    * [.appendPreferencesItem()](#UiMenu_appendPreferencesItem) ⇒ <code>UiMenuItem</code>
    * [.appendAboutItem()](#UiMenu_appendAboutItem) ⇒ <code>UiMenuItem</code>
    * [.appendSeparator()](#UiMenu_appendSeparator) ⇒ <code>UiMenuItem</code>


<a id="new_uimenu_new"></a>
### new UiMenu(caption)
Create a new UiMenu object.


| Param | Type | Description |
| --- | --- | --- |
| caption | <code>string</code> | The caption of the menu. |


<a id="uimenu_appenditem"></a>
### uiMenu.appendItem(caption) ⇒ <code>UiMenuItem</code>
Append a normal menu button.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: <code>UiMenuItem</code> - the new appended UiMenuItem  

| Param | Type | Description |
| --- | --- | --- |
| caption | <code>string</code> | The caption of the menu item. |


<a id="uimenu_appendcheckitem"></a>
### uiMenu.appendCheckItem(caption) ⇒ <code>UiMenuItem</code>
Append a menu button with a checkable option.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: <code>UiMenuItem</code> - the new appended UiMenuItem  

| Param | Type | Description |
| --- | --- | --- |
| caption | <code>String</code> | The caption of the menu item. |


<a id="uimenu_appendquititem"></a>
### uiMenu.appendQuitItem() ⇒ <code>UiMenuItem</code>
Append a Quit button. This accepts no text, the caption defaults
to `Quit`.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: <code>UiMenuItem</code> - the new appended UiMenuItem  

<a id="uimenu_appendpreferencesitem"></a>
### uiMenu.appendPreferencesItem() ⇒ <code>UiMenuItem</code>
Append a Preferences button. This accepts no text, the caption
defaults to `Preferences`.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: <code>UiMenuItem</code> - the new appended UiMenuItem  

<a id="uimenu_appendaboutitem"></a>
### uiMenu.appendAboutItem() ⇒ <code>UiMenuItem</code>
Append an About button. This accepts no text, the caption
defaults to `About`.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: <code>UiMenuItem</code> - the new appended UiMenuItem  

<a id="uimenu_appendseparator"></a>
### uiMenu.appendSeparator() ⇒ <code>UiMenuItem</code>
Append a Separator between menu items.

**Kind**: instance method of [<code>UiMenu</code>](#UiMenu)  
**Returns**: <code>UiMenuItem</code> - the new appended UiMenuItem  
