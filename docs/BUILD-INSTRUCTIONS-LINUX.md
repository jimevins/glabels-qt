gLabels Linux Build Instructions
================================

# Prerequisites

- g++
- CMake 2.8.12+
- Qt5 5.4+ Development Packages ( Qt5Core, Qt5Widgets, Qt5PrintSupport, Qt5Xml, Qt5Svg )
- zlib 1.2+ Development Package

> Even if the above library packages are installed, their corresponding development packages
> may also need to be installed.  Development packages are usually named somegthing like
> libraryName-dev or libraryName-devel.

# Cloning/Downloading

To clone the gLabels source:

```
$ git clone https://github.com/jimevins/glabels-qt.git
```


# Compiling and Install

gLabels uses the CMake meta build system.  Use the following commands to build and install gLabels:

```
$ cd ./glabels-qt
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```
