import {startLoop, stopLoop, onShouldQuit} from 'libui-napi';
import {
	UiWindow,
	UiHorizontalBox,
	UiMultilineEntry,
	UiVerticalSeparator
} from 'libui-napi';

onShouldQuit(() => {
	stopLoop();
});

async function createWindow() {
	await startLoop();

	const win = new UiWindow('Test Window', 800, 600, false);
	win.margined = true;
	const logEntry = new UiMultilineEntry();

	const entry = new UiMultilineEntry();
	entry.text = 'A test line\n';
	entry.append('A second test line\n');
	entry.onChanged(() => {
		const msg = `Text changed to ${entry.text}`;
		logEntry.append(msg + '\n');
	});

	const box = new UiHorizontalBox();
	box.padded = true;
	box.append(entry, true);
	box.append(new UiVerticalSeparator(), false);
	box.append(logEntry, true);

	win.setChild(box);

	win.onContentSizeChanged(() => {
		const size = win.contentSize;
		console.log(`size changed to ${size.width}x${size.height}`);
	});

	win.onClosing(() => {
		win.close();
		stopLoop().then(() => console.log('goodbye...')).catch(err => console.error(err));
	});

	win.show();
}

createWindow()
	.catch(err => console.error(err));

