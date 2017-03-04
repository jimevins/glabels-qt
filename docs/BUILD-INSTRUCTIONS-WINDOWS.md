gLabels Windows Build Instructions
==================================

gLabels for Windows can be built using one of the following toolchains:

- [MSYS/MINGW](#msysmingw)
- [Visual Studio](#visual-studio)


MSYS/MINGW
----------

### Prerequisites

- MSYS/MINGW, including the following packages
  + mingw32-gcc-g++
  + mingw32-libz
- CMake 2.8.12+
- Qt5 5.4+ for MINGW

Make sure that Qt tools are in your executable search path.  For example, add something like this to your .profile file:

```
export PATH=/c/Qt/Qt5.6.0/5.6/mingw49_32/bin:${PATH}
```

The exact path will depend on the version of Qt and MINGW you have installed.


### Cloning/Downloading

To download, select **Download ZIP** on the [glabels-qt Github page](https://github.com/jimevins/glabels-qt).  Unzip this file into your MSYS home directory (e.g. */mingw/msys/1.0/home/yourname*).


### Compiling and Install

gLabels uses the CMake meta build system.  From the MSYS shell, type the following commands:

```
$ cd glabels-qt-master
$ mkdir build
$ cd build
$ cmake -G "MSYS Makefiles" ..
$ make install
```



Visual Studio
-------------

TBD