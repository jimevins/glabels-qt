#=======================================
# Sources
#=======================================
set (barcode_sources
  GnuBarcode.cpp
  QrEncode.cpp
  Zint.cpp
)

add_library (Barcode STATIC
  ${barcode_sources}
)


#=======================================
# Where to find stuff
#=======================================
include_directories (
)

link_directories (
)


#=======================================
# Subdirectories
#=======================================


#=======================================
# Install
#=======================================
