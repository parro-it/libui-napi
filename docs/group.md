## Classes

<dl>
<dt><a href="#UiGroup">UiGroup</a></dt>
<dd><p>A container for a single control that provides a caption and visually groups
it&#39;s child.</p>
</dd>
<dt><a href="#UiControl">UiControl</a></dt>
<dd><p>Base class for all controls.</p>
</dd>
</dl>

<a name="UiGroup"></a>

## UiGroup
A container for a single control that provides a caption and visually groups
it's child.

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
| control | [<code>UiControl</code>](#UiControl) | the control to add as child. |
| stretchy | <code>boolean</code> | whever the control should fill all the available space. |

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
