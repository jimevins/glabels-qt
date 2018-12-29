![gLabels Label Designer](glabels/images/glabels-label-designer.png)

![Cover Image](docs/images/cover-image.png)

[![Travis Build Status](https://travis-ci.org/jimevins/glabels-qt.svg?branch=master)](https://travis-ci.org/jimevins/glabels-qt)
[![Appveyor Build Status](https://ci.appveyor.com/api/projects/status/github/jimevins/glabels-qt?branch=master&svg=true)](https://ci.appveyor.com/project/jimevins/glabels-qt)

*******************************************************************************

## What is gLabels-qt?

gLabels-qt is the development version of the next major version of gLabels (4.0).


## What's new in gLabels 4?

- Based on the Qt5 framework.
- Updated UI based on typical workflows.
- Intended to be a cross-platform application.
    * So far, it has been built and tested under Linux, Windows 7, and Windows 10. (Windows testing is still very intermittent.)


## Status

gLabels-qt has been under off-and-on development for several years.
It is still missing several features to bring it in parity with glabels-3.4.  These include

- Optional Evolution and VCard backends.
- An online manual


## Download

### Latest Release

There are currently no official releases of gLabels 4.

### Continuous Integration Snapshots

Continuous integration snapshots are not official releases.  These snapshots represent the latest
bleeding-edge development (unstable) code.  Please, DO NOT use it in a production environment.  Do not
expect compatibility or consistency of features between snapshots.

| Platform | Files | Notes |
|:---------|:------|:------|
| Linux x86_64 [AppImage](http:appimage.org) | [glabels-continuous-x86_64.AppImage](https://github.com/jimevins/glabels-qt/releases/download/continuous/glabels-continuous-x86_64.AppImage) | Download, make it executable, and run! |
| Archlinux          | [Archlinux User Repository Page](https://aur.archlinux.org/packages/glabels-qt-git/) | Maintained by [Mario Blättermann](https://github.com/mariobl) |
| Ubuntu             | [PPA Page](https://code.launchpad.net/~krisives/+archive/ubuntu/glabels-qt) | Maintained by [Kristopher Ives](https://github.com/krisives).<br>https://github.com/krisives/glabels-qt-packaging |
| Windows x86_64     | [glabels-3.99.0-win64.exe](https://github.com/jimevins/glabels-qt/releases/download/continuous/glabels-3.99.0-win64.exe) | Windows installer |
| Source Code TAR.GZ | [continuous.tar.gz](https://github.com/jimevins/glabels-qt/archive/continuous.tar.gz) | |
| Source Code ZIP    | [continuous.zip](https://github.com/jimevins/glabels-qt/archive/continuous.tar.gz) | |


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

* For code contributions, see [docs/CONTRIBUTING.md](docs/CONTRIBUTING.md).


## License

gLabels-qt is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

gLabels-qt is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

See [LICENSE](LICENSE) in this directory.

The following sub-components are also made available under less
restrictive licensing:

### Glbarcode

   gLabels-qt currently includes a version of the glbarcode++ library, located in
   the "glbarcode/" subdirectory.  It is licensed under the GNU LESSER GENERAL
   PUBLIC LICENSE (LGPL); either version 3 of the License, or (at your option)
   any later version -- see the [glbarcode/LICENSE](glbarcode/LICENSE).

### Template Database

   The XML files in the "templates/" subdirectory constitute the glabels
   label database.  No copyright is claimed on the facts contained within
   the database and can be used for any purpose.  However, to clear up any
   ambiguity, the DTD file that defines the format of these files is
   licensed using the MIT/X license, see [templates/LICENSE](templates/LICENSE).
