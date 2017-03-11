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


### Compile and Install

gLabels uses the CMake meta build system.  From the MSYS shell, type the following commands:

<pre>
$ cd <i>glabels_source_directory</i>
$ mkdir build
$ cd build
$ cmake -G "MSYS Makefiles" ..
$ make install
</pre>



Visual Studio
-------------

TBD