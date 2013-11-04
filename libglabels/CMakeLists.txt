cmake_minimum_required (VERSION 2.8)

project (libglabels CXX)

configure_file (Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Config.h @ONLY)

set (libglabels_sources
  Category.cpp
  Paper.cpp
  Vendor.cpp
  Units.cpp
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
  XmlUtil.cpp
)

set (libglabels_qobject_headers
)

set (libglabels_resource_files
)

qt4_wrap_cpp (libglabels_moc_sources ${libglabels_qobject_headers})
qt4_add_resources(libglabels_qrc_sources ${libglabels_resource_files})

include (${QT_USE_FILE})


include_directories (
  ${CMAKE_CURRENT_BINARY_DIR}
)

link_directories (
)

add_library (libglabels ${libglabels_sources} ${libglabels_moc_sources} ${libglabels_qrc_sources})

install (TARGETS libglabels ARCHIVE DESTINATION lib)
