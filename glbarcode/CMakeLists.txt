#=======================================
# Compilation
#=======================================
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_compile_options (-std=c++11 -g)
if (NOT WIN32)
   add_compile_options (-fPIC)
endif ()

# Uncomment to build with pedantic flags
#add_compile_options (-Werror -Wall -Wpedantic)


#=======================================
# Sources
#=======================================
set (LIB_SOURCES
  Factory.cpp
  Barcode.cpp
  Barcode1dBase.cpp
  Barcode2dBase.cpp
  BarcodeCode39.cpp
  BarcodeCode39Ext.cpp
  BarcodeUpcBase.cpp
  BarcodeUpcA.cpp
  BarcodeEan13.cpp
  BarcodePostnet.cpp
  BarcodePostnet5.cpp
  BarcodePostnet9.cpp
  BarcodePostnet11.cpp
  BarcodeCepnet.cpp
  BarcodeOnecode.cpp
  BarcodeDataMatrix.cpp
  BarcodeQrcode.cpp
  DrawingPrimitives.cpp
  Renderer.cpp
  QtRenderer.cpp
)

add_library (glbarcode
  ${LIB_SOURCES}
)


#=======================================
# Where to find stuff
#=======================================
include_directories (
  ${Qt5Widgets_INCLUDE_DIRS}
)

