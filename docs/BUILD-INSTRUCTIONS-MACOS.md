gLabels MacOS Build Instructions
================================

## Prerequisites

For Intel Macs
```
brew install cmake
brew install qt
```

For Apple Silicon Macs
```
brew install gcc
brew install cmake
brew install qt5
```



## Compile and Install

<pre>
cd <i>glabels_source_directory</i>
mkdir build
cd build

# For Intel Macs
cmake -D CMAKE_PREFIX_PATH=/usr/local/opt/qt  ..

# For Apple Silicon Macs
cmake -D CMAKE_PREFIX_PATH="/opt/homebrew/opt/qt5" -DCMAKE_C_COMPILER=/opt/homebrew/bin/gcc-12 -DCMAKE_CXX_COMPILER=/opt/homebrew/bin/g++-12  ..

make
sudo make install
</pre>
