# libui-node controls events

Many controls have events that are raised when their properties changed, because user interacts with GUI or because programmer has invoked a property setter.

All events are methods that accepts a single callback that receive 0 arguments.

```js
var control = new libui.UiEntry();

control.onChanged(() => {
	console.log(control.text);
});

// set the text contained in the entry
control.text = 'sample text';
```

Controls don't keep an internal list of event listener. If you register more that one callbacks, previous one is lost and never get called. This is implemented directly in `libui`, maybe we implement `Node.js` style event emitter in a future release.

You can remove an event listener by calling the method with a `null` argument:

```js
var control = new libui.UiEntry();

control.onChanged(() => {
	console.log(control.text);
});

control.onChanged(null);

// set the text contained in the entry
// callback is not called.
control.text = 'sample text';
```
