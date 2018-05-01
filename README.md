# libui-napi

Experimental bindings for libui using n-api

```
npm install libui-napi
```

Used to showcase prebuilds

[![build status](https://travis-ci.org/parro-it/libui-napi.svg?branch=master)](https://travis-ci.org/parro-it/libui-napi)
[![Build status](https://ci.appveyor.com/api/projects/status/d1j0kq1wjiqticwn/branch/master?svg=true)](https://ci.appveyor.com/project/parro-it/libui-napi/branch/master)

All prebuilds are build on CI and afterwards downloaded and published in the npm tarball. See [prebuildify-ci](https://github.com/parro-it/prebuildify-ci) for more.

## Usage

``` js
const libui = require('./');

libui.init();
libui.onShouldQuit(() => {
	libui.stop();
});
const win = libui.windowNew("Test Window", 800, 600, false);

libui.windowOnClosing(win, () => {
	if (libui.windowGetTitle(win) == "Test Window") {
		return libui.windowSetTitle(win, "Riprova");
	}
	console.log('closing', libui.windowGetTitle(win));
	libui.windowClose(win);
	libui.stop();
});

libui.windowShow(win);
libui.start();
```

## License

MIT
