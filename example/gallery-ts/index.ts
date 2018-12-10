import {startLoop, stopLoop, UiButton, UiWindow} from 'libui-napi';

const win = new UiWindow('Using libui-node with TypeScript', 800, 600, false);
win.onClosing(() => {
    win.close();
    stopLoop();
});

const btn = new UiButton('full');
btn.setText('full screen');
btn.onClicked(() => {
    win.fullscreen = !win.fullscreen;
    btn.text = win.fullscreen ? 'normal' : 'fullscreen';
});

win.setChild(btn);

win.show();

startLoop();
