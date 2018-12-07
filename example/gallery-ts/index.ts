import {startLoop, stopLoop, UiWindow} from 'libui-napi';


const win = new UiWindow('Using libui-node with TypeScript', 800, 600, false);
win.onClosing(() => {
    win.close();
    stopLoop();
});
win.show();
startLoop();
