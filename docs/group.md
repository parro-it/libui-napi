<a name="UiGroup"></a>

## UiGroup
A container for a single widget that provide a caption and visually group it's children.

**Kind**: global class  

* [UiGroup](#UiGroup)
    * [new UiGroup(title)](#new_UiGroup_new)
    * [.title](#UiGroup+title) ⇒ <code>string</code>
    * [.margined](#UiGroup+margined) ⇒ <code>boolean</code>
    * [.setChild(control, stretchy)](#UiGroup+setChild)

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
<a name="UiGroup+margined"></a>

### uiGroup.margined ⇒ <code>boolean</code>
When true, an internal margin is added to the group.

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

