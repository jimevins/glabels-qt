cmake_minimum_required (VERSION 2.8)

###############################################################################
# gLabels libglabels subproject
###############################################################################
project (libglabels CXX)


#=======================================
# Sources
#=======================================
configure_file (Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Config.h @ONLY)

set (libglabels_sources
  Category.cpp
  Paper.cpp
  Vendor.cpp
  Point.cpp
  Layout.cpp
  Markup.cpp
  Frame.cpp
  FrameRect.cpp
  FrameCd.cpp
  FrameRound.cpp
  FrameEllipse.cpp
  StrUtil.cpp
  Template.cpp
  Db.cpp
  XmlCategoryParser.cpp
  XmlPaperParser.cpp
  XmlVendorParser.cpp
  XmlTemplateParser.cpp
  XmlTemplateCreator.cpp
  XmlUtil.cpp
  MiniPreviewPixmap.cpp
  Units.cpp
  Distance.cpp
)

set (libglabels_qobject_headers
)

set (libglabels_resource_files
)

qt4_wrap_cpp (libglabels_moc_sources ${libglabels_qobject_headers})
qt4_add_resources(libglabels_qrc_sources ${libglabels_resource_files})

add_library (libglabels
  ${libglabels_sources}
  ${libglabels_moc_sources}
  ${libglabels_qrc_sources}
)


#=======================================
# Where to find stuff
#=======================================
include_directories (
  ${CMAKE_CURRENT_BINARY_DIR}
)

link_directories (
)


#=======================================
# Install
#=======================================
install (TARGETS libglabels ARCHIVE DESTINATION lib)
