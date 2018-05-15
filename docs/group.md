<a name="UiGroup"></a>

## UiGroup ⇐ <code>UiControl</code>
A container for a single control that provides a caption and visually groups
it's child.

**Kind**: global class  
**Extends**: <code>UiControl</code>  

* [UiGroup](#UiGroup) ⇐ <code>UiControl</code>
    * [new UiGroup(title)](#new_UiGroup_new)
    * [.title](#UiGroup+title) ⇒ <code>string</code>
    * [.setChild(control, stretchy)](#UiGroup+setChild)
    * [.margined](#UiGroup+margined) ⇒ <code>boolean</code>
    * [.enabled](#) ⇒ <code>boolean</code>
    * [.visible](#) ⇒ <code>boolean</code>
    * [.toplevel](#) ⇒ <code>boolean</code>

<a name="new_UiGroup_new"></a>

### new UiGroup(title)
Create a new UiGroup object.


| Param | Type | Description |
| --- | --- | --- |
| title | <code>string</code> | text to show in Group title bar. |

<a name="UiGroup+title"></a>

### uiGroup.title ⇒ <code>string</code>
Set or return the text to show in group caption.

**Kind**: instance property of [<code>UiGroup</code>](#UiGroup)  
<a name="UiGroup+setChild"></a>

### uiGroup.setChild(control, stretchy)
Set the control to show in this group content area.
UiGroup instances can contain only one control. If you need
more, you have to use [Containers](containers.md).

**Kind**: instance method of [<code>UiGroup</code>](#UiGroup)  

| Param | Type | Description |
| --- | --- | --- |
| control | <code>UiControl</code> | the control to add as child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |

<a name="UiGroup+margined"></a>

### uiGroup.margined ⇒ <code>boolean</code>
When true, an internal margin is added to the group.

**Kind**: instance property of [<code>UiGroup</code>](#UiGroup)  
<a name=""></a>

### uiGroup.enabled ⇒ <code>boolean</code>
Set or return whether the control is enabled.

**Kind**: instance property of [<code>UiGroup</code>](#UiGroup)  
<a name=""></a>

### uiGroup.visible ⇒ <code>boolean</code>
Set or return whether the control is visible.

**Kind**: instance property of [<code>UiGroup</code>](#UiGroup)  
<a name=""></a>

### uiGroup.toplevel ⇒ <code>boolean</code>
Set or return whether the control is a top level one.

**Kind**: instance property of [<code>UiGroup</code>](#UiGroup)  
