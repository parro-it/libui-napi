
<a id="uimenuitem"></a>
## UiMenuItem
A single button contained in a menu.

**Kind**: global class  

* [UiMenuItem](#UiMenuItem)
    * [new UiMenuItem()](#new_UiMenuItem_new)
    * [.enable()](#UiMenuItem_enable)
    * [.disable()](#UiMenuItem_disable)
    * [.onClicked(callback)](#UiMenuItem_onClicked)
    * [.checked](#UiMenuItem_checked) ⇒ <code>boolean</code>


<a id="new_uimenuitem_new"></a>
### new UiMenuItem()
Create a new UiMenuItem object.


<a id="uimenuitem_enable"></a>
### uiMenuItem.enable()
Enable the menu item.

**Kind**: instance method of [<code>UiMenuItem</code>](#UiMenuItem)  

<a id="uimenuitem_disable"></a>
### uiMenuItem.disable()
Disable the menu item

**Kind**: instance method of [<code>UiMenuItem</code>](#UiMenuItem)  

<a id="uimenuitem_onclicked"></a>
### uiMenuItem.onClicked(callback)
Register a callback for the click event of the menu item.

**Kind**: instance method of [<code>UiMenuItem</code>](#UiMenuItem)  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>function</code> | the function to register as callback for the event. |


<a id="uimenuitem_checked"></a>
### uiMenuItem.checked ⇒ <code>boolean</code>
If the item is created using appendCheckItem, then set
whether it is checked or not.

**Kind**: instance property of [<code>UiMenuItem</code>](#UiMenuItem)  
