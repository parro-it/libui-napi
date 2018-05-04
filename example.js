const {
	App,
	Window,
	MultilineEntry
} = require('.');

App.init();
App.onShouldQuit(() => {
	App.stop();
	global.gc();
});

function createWindow() {
	let win = Window.create("Test Window", 800, 600, false);

	const entry = MultilineEntry.create();
	MultilineEntry.setText(entry, "A test line\n");
	MultilineEntry.append(entry, "A second test line\n");
	MultilineEntry.onChanged(entry, () => {
		console.log(`Text changed to ${MultilineEntry.getText(entry)}`);
	});
	Window.setChild(win, entry);

	Window.onContentSizeChanged(win, () => {
		const size = Window.getContentSize(win);
		console.log(`size changed to ${size.width}x${size.height}`);
	});
	let step = 0;
	Window.onClosing(win, () => {
		if (Window.getTitle(win) == "Test Window") {
			setInterval(() => {
				if (step === 0){
					Window.setContentSize(win, 400, 300);
				}
				if (step === 1){
					Window.setMargined(win, true);
				}
				if (step === 2){
					Window.setMargined(win, false);
					Window.setFullscreen(win, true);
				}
				if (step === 3){
					Window.setFullscreen(win, false);
					Window.setBorderless(win, true);
				}
				if (step === 4){
					Window.setBorderless(win, false);
				}
				step++;

				console.log({
					Margined: Window.getMargined(win),
					Fullscreen: Window.getFullscreen(win),
					Borderless: Window.getBorderless(win),
				});
			}, 3000);
			return Window.setTitle(win, "Riprova");
		}
		console.log('closing', Window.getTitle(win));
		Window.close(win);
		win = null;
		App.stop();
		global.gc();
	});

	Window.show(win);
}

createWindow();
App.start();
global.gc();


