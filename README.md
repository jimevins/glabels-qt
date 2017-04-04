![logo](glabels/images/glabels-logo.png)
![gLabels Label Designer](glabels/images/glabels-label-designer.png)

[![Build Status](https://travis-ci.org/jimevins/glabels-qt.svg?branch=master)](https://travis-ci.org/jimevins/glabels-qt)

*******************************************************************************

## What is gLabels-qt?

gLabels-qt is the development repository for the next major version of gLabels (4.0).

![screenshot](docs/images/screenshot.png)

## What's new in gLabels-qt?

- Based on the Qt cross-platform framework.
- Unlike previous versions, glabels-qt is a cross-platform application.  So far, it
  has been built and tested under both Linux and Windows 7 (using MSYS/MINGW toolchain).
- Updated UI based on typical workflows.

## Status

gLabels-qt has been under off-and-on development since October 2013.
It is still missing several features to bring it in parity with glabels-3.4.  These include

- Barcode objects
- Compatability with older glabels files
- Batch mode
- Internationalization
- Custom product templates designer
- Online manual

## Download

The latest [AppImage](http://appimage.org/) for Linux can be downloaded from an URL that can be found in the latest [Travis CI build log](https://travis-ci.org/jimevins/glabels-qt) (toward the end). It should run on many distributions. Just download, [make executable](http://discourse.appimage.org/t/how-to-make-an-appimage-executable/80), and run.

## Build Instructions

- [Linux Build Instructions](docs/BUILD-INSTRUCTIONS-LINUX.md)
- [Windows Build Instructions](docs/BUILD-INSTRUCTIONS-WINDOWS.md)
- Mac Build Instructions (TBD)

## Help Needed

* Help is needed to add support to build and package glabels for various platforms and packaging systems.
These include

  - Windows (VisualStudio)
  - Windows (MINGW)
  - Mac
  - Linux (flatpak)
  - Linux (snap)

* Help is needed writing online documentation.

* Help is needed writing translations.

* Suggestions.

* For code contributions, see [docs/HACKING.md](docs/HACKING.md).

