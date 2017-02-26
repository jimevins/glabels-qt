#=======================================
# Compilation
#=======================================
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_compile_options (-std=c++11 -g)
if (NOT WIN32)
	add_compile_options (-fPIC)
endif ()


#=======================================
# Auto-generate Version.h
#=======================================
configure_file (Version.h.in ${CMAKE_CURRENT_BINARY_DIR}/Version.h @ONLY)
configure_file (Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Config.h @ONLY)


#=======================================
# Sources
#=======================================
set (glabels_sources
  glabels_main.cpp
  AboutDialog.cpp
  BarcodeBackends.cpp
  BarcodeMenu.cpp
  BarcodeMenuButton.cpp
  BarcodeMenuItem.cpp
  BarcodeStyle.cpp
  Category.cpp
  ColorButton.cpp
  ColorHistory.cpp
  ColorNode.cpp
  ColorPaletteDialog.cpp
  ColorPaletteItem.cpp
  ColorPaletteButtonItem.cpp
  ColorSwatch.cpp
  Cursors.cpp
  Db.cpp
  Distance.cpp
  EnumUtil.cpp
  FieldButton.cpp
  File.cpp
  FileUtil.cpp
  Frame.cpp
  FrameCd.cpp
  FrameEllipse.cpp
  FrameRect.cpp
  FrameRound.cpp
  Handles.cpp
  Help.cpp
  Icons.cpp
  LabelEditor.cpp
  LabelModel.cpp
  LabelModelObject.cpp
  LabelModelBoxObject.cpp
  LabelModelEllipseObject.cpp
  LabelModelImageObject.cpp
  LabelModelLineObject.cpp
  LabelModelShapeObject.cpp
  LabelModelTextObject.cpp
  Layout.cpp
  MainWindow.cpp
  Markup.cpp
  MergeView.cpp
  MiniPreviewPixmap.cpp
  ObjectEditor.cpp
  Outline.cpp
  PageRenderer.cpp
  Paper.cpp
  Point.cpp
  PreferencesDialog.cpp
  PrintView.cpp
  PropertiesView.cpp
  Preview.cpp
  PreviewOverlayItem.cpp
  Region.cpp
  SelectProductDialog.cpp
  Settings.cpp
  SimplePreview.cpp
  Size.cpp
  StartupView.cpp
  StrUtil.cpp
  Template.cpp
  TemplatePicker.cpp
  TemplatePickerItem.cpp
  TextNode.cpp
  UndoRedoModel.cpp
  Units.cpp
  Vendor.cpp
  XmlCategoryParser.cpp
  XmlLabelCreator.cpp
  XmlLabelParser.cpp
  XmlPaperParser.cpp
  XmlTemplateCreator.cpp
  XmlTemplateParser.cpp
  XmlUtil.cpp
  XmlVendorParser.cpp
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
  File.h
  LabelEditor.h
  LabelModel.h
  LabelModelObject.h
  LabelModelBoxObject.h
  LabelModelEllipseObject.h
  LabelModelImageObject.h
  LabelModelLineObject.h
  LabelModelShapeObject.h
  LabelModelTextObject.h
  MainWindow.h
  MergeView.h
  ObjectEditor.h
  PageRenderer.h
  PreferencesDialog.h
  PrintView.h
  PropertiesView.h
  Preview.h
  SelectProductDialog.h
  Settings.h
  SimplePreview.h
  StartupView.h
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
  ui/StartupView.ui
)

set (glabels_resource_files
  cursors.qrc
  icons.qrc
  images.qrc
)

qt5_wrap_cpp (glabels_moc_sources ${glabels_qobject_headers})
qt5_wrap_ui (glabels_forms_headers ${glabels_forms})
qt5_add_resources (glabels_qrc_sources ${glabels_resource_files})

if (WIN32)
  # Windows resource file
  set (glabels_win_rc glabels.rc)
endif ()


add_executable (glabels-qt
  ${glabels_sources}
  ${glabels_moc_sources}
  ${glabels_qrc_sources}
  ${glabels_forms_headers}
  ${glabels_win_rc}
)

target_link_libraries (glabels-qt
  Merge
  ${Qt5Widgets_LIBRARIES}
  ${Qt5PrintSupport_LIBRARIES}
  ${Qt5Xml_LIBRARIES}
  ${Qt5Svg_LIBRARIES}
  ${ZLIB_LIBRARIES}
)


#=======================================
# Where to find stuff
#=======================================
include_directories (
  ${ZLIB_INCLUDE_DIRS}
  ${glabels_qt_SOURCE_DIR}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5PrintSupport_INCLUDE_DIRS}
  ${Qt5Xml_INCLUDE_DIRS}
  ${Qt5Svg_INCLUDE_DIRS}
)


#=======================================
# Subdirectories
#=======================================
add_subdirectory (Merge)


#=======================================
# Install
#=======================================
install (TARGETS glabels-qt RUNTIME DESTINATION bin)

install (FILES icons/scalable/apps/glabels.svg DESTINATION share/icons/hicolor/scalable/apps)
install (FILES icons/16x16/apps/glabels.svg    DESTINATION share/icons/hicolor/16x16/apps)
install (FILES icons/22x22/apps/glabels.svg    DESTINATION share/icons/hicolor/22x22/apps)
install (FILES icons/32x32/apps/glabels.svg    DESTINATION share/icons/hicolor/32x32/apps)
install (FILES icons/48x48/apps/glabels.svg    DESTINATION share/icons/hicolor/48x48/apps)

install (FILES icons/scalable/mimetypes/x-glabels-project.svg DESTINATION share/icons/hicolor/scalable/mimetypes)
install (FILES icons/16x16/mimetypes/x-glabels-project.svg    DESTINATION share/icons/hicolor/16x16/mimetypes)
install (FILES icons/22x22/mimetypes/x-glabels-project.svg    DESTINATION share/icons/hicolor/22x22/mimetypes)
install (FILES icons/24x24/mimetypes/x-glabels-project.svg    DESTINATION share/icons/hicolor/24x24/mimetypes)
