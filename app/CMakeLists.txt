cmake_minimum_required (VERSION 2.8)

project (app CXX)

set (glabels_sources
  glabels_main.cpp
  BarcodeStyle.cpp
  ColorNode.cpp
  File.cpp
  Help.cpp
  LabelModel.cpp
  LabelModelObject.cpp
  LabelModelBoxObject.cpp
  LabelRegion.cpp
  MainWindow.cpp
  MergeField.cpp
  MergeRecord.cpp
  TemplatePicker.cpp
  TemplatePickerItem.cpp
  TextNode.cpp
  NewLabelDialog.cpp
  SimplePreview.cpp
  View.cpp
)

set (glabels_qobject_headers
  LabelModel.h
  LabelModelObject.h
  LabelModelBoxObject.h
  NewLabelDialog.h
  MainWindow.h
  SimplePreview.h
  TemplatePicker.h
  View.h
)

set (glabels_forms
  ui/NewLabelDialog.ui
)

set (glabels_resource_files
  icons.qrc
  images.qrc
)

qt4_wrap_cpp (glabels_moc_sources ${glabels_qobject_headers})
qt4_wrap_ui (glabels_forms_headers ${glabels_forms})
qt4_add_resources(glabels_qrc_sources ${glabels_resource_files})

include (${QT_USE_FILE})


include_directories (
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${glabels_qt_SOURCE_DIR}
)

link_directories (
  ${glabels_qt_SOURCE_DIR}/libglabels
)

add_executable (glabels-qt ${glabels_sources} ${glabels_moc_sources} ${glabels_qrc_sources} ${glabels_forms_headers})

target_link_libraries (glabels-qt
  libglabels
  ${QT_LIBRARIES}
)


install (TARGETS glabels-qt RUNTIME DESTINATION bin)
