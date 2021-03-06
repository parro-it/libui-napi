# libui-node

> Node.js bindings for [libui](https://github.com/andlabs/libui) library.

[libui](https://github.com/andlabs/libui) is a lightweight, portable GUI library that uses the native GUI technologies of each platform it supports.

It is in early stage of development, but is evolving at great pace and is really awesome. It could become an awesome alternative to Electron to develop multiplatform GUI, expecially suited to develop small apps.

[![Join the community on Spectrum](https://withspectrum.github.io/badge/badge.svg)](https://spectrum.chat/libui-node)
[![Travis Build Status](https://img.shields.io/travis/parro-it/libui-node/master.svg)](http://travis-ci.org/parro-it/libui-node)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/ebcssfrpaypfwha4?svg=true)](https://ci.appveyor.com/project/parro-it/libui-node)
[![NPM module](https://img.shields.io/npm/v/libui-node.svg)](https://npmjs.org/package/libui-node)
[![NPM downloads](https://img.shields.io/npm/dt/libui-node.svg)](https://npmjs.org/package/libui-node)


# Screenshots

<p align="center">
macOS
</p>

![macOS](docs/media/Window-macOS.png)

<p align="center">
Linux
</p>

![Linux](docs/media/Window-Linux.png)

<p align="center">
Windows
</p>

![Windows](docs/media/Window-Windows.png)

# Supported platforms

* Windows: Windows Vista SP2 with Platform Update or newer
* Unix: GTK+ 3.10 or newer
* Mac OS X: OS X 10.8 or newer
* Node.js version 4 or greater.

# Prerequisites

## Prebuilt binaries

All prebuilds are build on CI and afterwards downloaded and published in the npm install phase.
Prebuild t binaries are available for the following platforms:

* macOS 64bit
* Windows 64bit
* Linux 64bit

If you are using one of these platform, you don't need to recompile
libui-node source code from scratch.

The only additional dependecy you nedd is [GTK+ 3](https://packages.ubuntu.com/source/xenial/gtk+3.0) to run on Linux.

Otherwise, libui-node sources will be compiled during part of the `install`
phase. You need the following additionl dependency in order to compile:

## Windows

- [windows-build-tools](https://www.npmjs.com/package/windows-build-tools) or Visual Studio 2015 to compile the project.
- [Visual C++ Redistributable Package per Visual Studio 2013](https://www.microsoft.com/it-it/download/details.aspx?id=40784)

## Linux

If they are not provided by default in your distribution:
- [build-essential](https://packages.ubuntu.com/xenial/build-essential) to compile the project.
- [GTK+ 3](https://packages.ubuntu.com/source/xenial/gtk+-3.0)

## macOS

- [Xcode 8](https://developer.apple.com/xcode/) to compile the project.

# Installation

```bash
npm install -S libui-node
```

`libui` prebuilt binaries are automatically downloaded after install.

If you get this error on Windows:

```
'__pfnDliNotifyHook2': redefinition; different type modifiers
```

you need to install latest npm version:

```bash
$ npm i -g npm
```

see [this node-gyp issue](https://github.com/nodejs/node-gyp/issues/972)
for more details.

# Documentation & examples

Documentation is in [docs folder](docs).
You can also find working examples in [example folder](https://github.com/parro-it/libui-node/tree/master/example).

## How to run the examples

First, you have to clone the GitHub repo and npm install it:

```bash
git clone https://github.com/parro-it/libui-node.git
npm install
```

Then, to run the control gallery example (requires Node.js >= 6), type:

```bash
node example/core-api.js
```


# Contribution & design

1) Make sure to read and agree with our [code of conduct](CODE_OF_CONDUCT.md)
2) Follow guidelines provided in our [contribution guide](CONTRIBUTING.md)

# Related projects

* [libui](https://github.com/andlabs/libui) - Simple and portable (but not inflexible) GUI library in C that uses the native GUI technologies of each platform it supports.
* [nbind](https://github.com/charto/nbind) - Magical headers that make your C++ library accessible from JavaScript
* [proton-native](https://github.com/kusti8/proton-native) - A React environment for cross platform native desktop apps https://proton-native.js.org
* [vuido](https://vuido.mimec.org/) - Native desktop applications using Vue.js.
https://proton-native.js.org

# Contributors

[![Andrea Parodi](https://avatars0.githubusercontent.com/u/11197111?s=130)](https://github.com/parro-it) |
[![Juha Järvi](https://avatars3.githubusercontent.com/u/778781?s=130)](https://github.com/jjrv) |
[![Niklas Mischkulnig](https://avatars2.githubusercontent.com/u/4586894?s=130)](https://github.com/mischnic) |
[![Gustav Hansen](https://avatars0.githubusercontent.com/u/9812956?s=130)](https://github.com/kusti8)
---|---|---|---
[Andrea Parodi](https://github.com/parro-it) | [Juha Järvi](https://github.com/jjrv) | [Niklas Mischkulnig](https://github.com/mischnic) | [Gustav Hansen](https://github.com/kusti8)

# License

The MIT License (MIT)

Copyright (c) 2018 parro-it

