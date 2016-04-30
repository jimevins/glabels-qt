cmake_minimum_required (VERSION 2.8)

project (app CXX)

set (glabels_sources
  glabels_main.cpp
  AboutDialog.cpp
  BarcodeBackends.cpp
  BarcodeMenu.cpp
  BarcodeMenuButton.cpp
  BarcodeMenuItem.cpp
  BarcodeStyle.cpp
  ColorButton.cpp
  ColorHistory.cpp
  ColorNode.cpp
  ColorPaletteDialog.cpp
  ColorPaletteItem.cpp
  ColorPaletteButtonItem.cpp
  ColorSwatch.cpp
  Cursors.cpp
  FieldButton.cpp
  FieldMenu.cpp
  FieldMenuItem.cpp
  File.cpp
  FileUtil.cpp
  Handles.cpp
  Help.cpp
  LabelEditor.cpp
  LabelModel.cpp
  LabelModelObject.cpp
  LabelModelBoxObject.cpp
  LabelModelShapeObject.cpp
  LabelRegion.cpp
  MainWindow.cpp
  Merge.cpp
  MergeField.cpp
  MergeView.cpp
  MergeRecord.cpp
  ObjectEditor.cpp
  Outline.cpp
  PageRenderer.cpp
  PreferencesDialog.cpp
  PrintView.cpp
  PropertiesView.cpp
  Preview.cpp
  PreviewOverlayItem.cpp
  SelectProductDialog.cpp
  Settings.cpp
  SimplePreview.cpp
  StartupWizard.cpp
  TemplatePicker.cpp
  TemplatePickerItem.cpp
  TextNode.cpp
  UndoRedoModel.cpp
  XmlLabelCreator.cpp
  XmlLabelParser.cpp
)

set (glabels_qobject_headers
  AboutDialog.h
  BarcodeMenu.h
  BarcodeMenuButton.h
  BarcodeMenuItem.h
  ColorButton.h
  ColorHistory.h
  ColorPaletteDialog.h
  ColorPaletteItem.h
  ColorPaletteButtonItem.h
  FieldButton.h
  FieldMenu.h
  FieldMenuItem.h
  File.h
  LabelEditor.h
  LabelModel.h
  LabelModelObject.h
  LabelModelBoxObject.h
  LabelModelShapeObject.h
  MainWindow.h
  Merge.h
  MergeView.h
  ObjectEditor.h
  PreferencesDialog.h
  PrintView.h
  PropertiesView.h
  Preview.h
  SelectProductDialog.h
  Settings.h
  SimplePreview.h
  StartupWizard.h
  TemplatePicker.h
  UndoRedoModel.h
)

set (glabels_forms
  ui/AboutDialog.ui
  ui/MergeView.ui
  ui/ObjectEditor.ui
  ui/PreferencesDialog.ui
  ui/PrintView.ui
  ui/PropertiesView.ui
  ui/SelectProductDialog.ui
  ui/StartupWizard.ui
)

set (glabels_resource_files
  cursors.qrc
  icons.qrc
  images.qrc
)

qt4_wrap_cpp (glabels_moc_sources ${glabels_qobject_headers})
qt4_wrap_ui (glabels_forms_headers ${glabels_forms})
qt4_add_resources (glabels_qrc_sources ${glabels_resource_files})

include (${QT_USE_FILE})


include_directories (
  ${ZLIB_INCLUDE_DIRS}
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
  ${ZLIB_LIBRARIES}
)


install (TARGETS glabels-qt RUNTIME DESTINATION bin)
