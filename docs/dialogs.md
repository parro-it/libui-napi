# UiDialogs

Static methods for opening dialogs.

* [UiDialogs](#uidialogs)
    * [.openFile(parent)](#uidialogsopenfileparent) ⇒ <code>string | null</code>
    * [.saveFile(parent)](#uidialogssavefileparent) ⇒ <code>string | null</code>
    * [.msgBox(parent, title, description)](#uidialogsmsgboxparent-title-description)
    * [.msgBoxError(parent, title, description)](#uidialogsmsgboxerrorparent-title-description)

### `UiDialogs.openFile(parent)`

Open a dialog to open a single file. Either the filepath or `null` (on canceling) is returned.

**Arguments**

* parent: UiWindow

### `UiDialogs.saveFile(parent)`

Open a dialog to save a single file. Either the filepath or `null` (on canceling) is returned.

**Arguments**

* parent: UiWindow


### `UiDialogs.msgBox(parent, title, description)`

Opens a dialog to notify the user.

**Arguments**

* parent: UiWindow
* title: String
* description: String

### `UiDialogs.msgBoxError(parent, title, description)`

Opens a dialog to notify the user about an error.

**Arguments**

* parent: UiWindow
* title: String
* description: String