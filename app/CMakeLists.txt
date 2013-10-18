cmake_minimum_required (VERSION 2.8)

project (app CXX)

set (qtlabels_sources
  qtlabels_main.cpp
  BarcodeStyle.cpp
  ColorNode.cpp
  LabelModel.cpp
  LabelModelItem.cpp
  LabelRegion.cpp
  MergeField.cpp
  MergeRecord.cpp
  TextNode.cpp
)

set (qobject_headers
  LabelModel.h
  LabelModelItem.h
)

qt4_wrap_cpp (moc_sources ${qobject_headers})


include (${QT_USE_FILE})


include_directories (
)

link_directories (
)

add_executable (qtlabels ${qtlabels_sources} ${moc_sources})

target_link_libraries (qtlabels
  ${QT_LIBRARIES}
)


install (TARGETS qtlabels RUNTIME DESTINATION bin)
