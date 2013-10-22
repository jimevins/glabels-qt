cmake_minimum_required (VERSION 2.8)

project (app CXX)

set (glabels_sources
  glabels_main.cpp
  BarcodeStyle.cpp
  ColorNode.cpp
  LabelModel.cpp
  LabelModelItem.cpp
  LabelRegion.cpp
  MainWindow.cpp
  MergeField.cpp
  MergeRecord.cpp
  TextNode.cpp
)

set (glabels_qobject_headers
  LabelModel.h
  LabelModelItem.h
  MainWindow.h
)

set (glabels_resource_files
  images.qrc
)

qt4_wrap_cpp (glabels_moc_sources ${glabels_qobject_headers})
qt4_add_resources(glabels_qrc_sources ${glabels_resource_files})

include (${QT_USE_FILE})


include_directories (
)

link_directories (
)

add_executable (glabels-qt ${glabels_sources} ${glabels_moc_sources} ${glabels_qrc_sources})

target_link_libraries (glabels-qt
  ${QT_LIBRARIES}
)


install (TARGETS glabels-qt RUNTIME DESTINATION bin)
