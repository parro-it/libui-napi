<a name="FontDescriptor"></a>

## FontDescriptor
An object that contains information on a system font.

**Kind**: global class  

* [FontDescriptor](#FontDescriptor)
    * [new FontDescriptor(family, size, weight, italic, stretch)](#new_FontDescriptor_new)
    * [.getFamily()](#FontDescriptor+getFamily) ⇒ <code>string</code>
    * [.getSize()](#FontDescriptor+getSize) ⇒ <code>number</code>
    * [.getWeight()](#FontDescriptor+getWeight) ⇒ <code>number</code>
    * [.getItalic()](#FontDescriptor+getItalic) ⇒ <code>number</code>
    * [.getStretch()](#FontDescriptor+getStretch) ⇒ <code>number</code>

<a name="new_FontDescriptor_new"></a>

### new FontDescriptor(family, size, weight, italic, stretch)
Create a new FontDescriptor object.


| Param | Type | Description |
| --- | --- | --- |
| family | <code>string</code> | the name of the font, e.g. "Helvetica" |
| size | <code>number</code> | size in point of the font |
| weight | <code>number</code> | weight of the font |
| italic | <code>number</code> | 1 if the font is italic, otherwise 0 |
| stretch | <code>number</code> | horizontal stretch value for the font |

<a name="FontDescriptor+getFamily"></a>

### fontDescriptor.getFamily() ⇒ <code>string</code>
Return the name of the font, e.g. "Helvetica".

**Kind**: instance method of [<code>FontDescriptor</code>](#FontDescriptor)  
<a name="FontDescriptor+getSize"></a>

### fontDescriptor.getSize() ⇒ <code>number</code>
Return the size in point of the font.

**Kind**: instance method of [<code>FontDescriptor</code>](#FontDescriptor)  
<a name="FontDescriptor+getWeight"></a>

### fontDescriptor.getWeight() ⇒ <code>number</code>
Return weight of the font.

**Kind**: instance method of [<code>FontDescriptor</code>](#FontDescriptor)  
<a name="FontDescriptor+getItalic"></a>

### fontDescriptor.getItalic() ⇒ <code>number</code>
Return 1 if the font is italic, otherwise 0.

**Kind**: instance method of [<code>FontDescriptor</code>](#FontDescriptor)  
<a name="FontDescriptor+getStretch"></a>

### fontDescriptor.getStretch() ⇒ <code>number</code>
Return horizontal stretch value for the font.

**Kind**: instance method of [<code>FontDescriptor</code>](#FontDescriptor)  
