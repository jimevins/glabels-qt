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
#add_definitions (-DQT_DISABLE_DEPRECATED_BEFORE=0x050400)

if (${GNUBARCODE_FOUND})
  add_definitions (-DHAVE_GNU_BARCODE=1)
else (${GNUBARCODE_FOUND})
  set (GNUBARCODE_INCLUDE_DIR "")
  set (GNUBARCODE_LIBRARIES "")
endif (${GNUBARCODE_FOUND})

if (${LIBQRENCODE_FOUND})
  add_definitions (-DHAVE_QRENCODE=1)
else (${LIBQRENCODE_FOUND})
  set (LIBQRENCODE_INCLUDE_DIR "")
  set (LIBQRENCODE_LIBRARIES "")
endif (${LIBQRENCODE_FOUND})

if (${LIBZINT_FOUND})
  add_definitions (-DHAVE_ZINT=1)
else (${LIBZINT_FOUND})
  set (LIBZINT_INCLUDE_DIR "")
  set (LIBZINT_LIBRARIES "")
endif (${LIBZINT_FOUND})


#=======================================
# Auto-generate Version.h
#=======================================
configure_file (Version.h.in ${CMAKE_CURRENT_BINARY_DIR}/Version.h @ONLY)
configure_file (Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Config.h @ONLY)


#=======================================
# Sources
#=======================================

#
# glabels executable
#
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
  DataCache.cpp
  Db.cpp
  Distance.cpp
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
  LabelModelBarcodeObject.cpp
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
  RawText.cpp
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
  BarcodeBackends.h
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
  LabelModelBarcodeObject.h
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

add_executable (glabels-qt WIN32
  ${glabels_sources}
  ${glabels_moc_sources}
  ${glabels_qrc_sources}
  ${glabels_forms_headers}
  ${glabels_win_rc}
)

target_link_libraries (glabels-qt
  Barcode
  Merge
  glbarcode
  ${Qt5Widgets_LIBRARIES}
  ${Qt5PrintSupport_LIBRARIES}
  ${Qt5Xml_LIBRARIES}
  ${Qt5Svg_LIBRARIES}
  ${ZLIB_LIBRARIES}
  ${GNUBARCODE_LIBRARIES}
  ${LIBQRENCODE_LIBRARIES}
  ${LIBZINT_LIBRARIES}
)


#
# glabels-batch executable
#
set (glabels-batch_sources
  glabels-batch_main.cpp
  BarcodeBackends.cpp
  BarcodeStyle.cpp
  Category.cpp
  ColorNode.cpp
  DataCache.cpp
  Db.cpp
  Distance.cpp
  FileUtil.cpp
  Frame.cpp
  FrameCd.cpp
  FrameEllipse.cpp
  FrameRect.cpp
  FrameRound.cpp
  Handles.cpp
  LabelModel.cpp
  LabelModelObject.cpp
  LabelModelBarcodeObject.cpp
  LabelModelBoxObject.cpp
  LabelModelEllipseObject.cpp
  LabelModelImageObject.cpp
  LabelModelLineObject.cpp
  LabelModelShapeObject.cpp
  LabelModelTextObject.cpp
  Layout.cpp
  Markup.cpp
  Outline.cpp
  PageRenderer.cpp
  Paper.cpp
  Point.cpp
  RawText.cpp
  Region.cpp
  Settings.cpp
  Size.cpp
  StrUtil.cpp
  Template.cpp
  TextNode.cpp
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

set (glabels-batch_qobject_headers
  BarcodeBackends.h
  LabelModel.h
  LabelModelObject.h
  LabelModelBarcodeObject.h
  LabelModelBoxObject.h
  LabelModelEllipseObject.h
  LabelModelImageObject.h
  LabelModelLineObject.h
  LabelModelShapeObject.h
  LabelModelTextObject.h
  PageRenderer.h
  Settings.h
)

qt5_wrap_cpp (glabels-batch_moc_sources ${glabels-batch_qobject_headers})

if (WIN32)
  # Windows resource file
  set (glabels-batch_win_rc glabels-batch.rc)
endif ()

add_executable (glabels-batch-qt WIN32
  ${glabels-batch_sources}
  ${glabels-batch_moc_sources}
  ${glabels-batch_win_rc}
)

target_link_libraries (glabels-batch-qt
  Barcode
  Merge
  glbarcode
  ${Qt5PrintSupport_LIBRARIES}
  ${Qt5Xml_LIBRARIES}
  ${Qt5Svg_LIBRARIES}
  ${ZLIB_LIBRARIES}
  ${GNUBARCODE_LIBRARIES}
  ${LIBQRENCODE_LIBRARIES}
  ${LIBZINT_LIBRARIES}
)


#=======================================
# Where to find stuff
#=======================================
include_directories (
  ${glabels_SOURCE_DIR}
  ${ZLIB_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5PrintSupport_INCLUDE_DIRS}
  ${Qt5Xml_INCLUDE_DIRS}
  ${Qt5Svg_INCLUDE_DIRS}
  ${GNUBARCODE_INCLUDE_DIR}
  ${LIBQRENCODE_INCLUDE_DIR}
  ${LIBZINT_INCLUDE_DIR}
)

link_directories (
)


#=======================================
# Subdirectories
#=======================================
add_subdirectory (BarcodeBackends)
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

if (MINGW)
   # Install Windows runtime DLLs in application bin
   set (runtime_dlls
     ${MINGW_BIN_DIR}/libgcc_s_dw2-1.dll
     ${MINGW_BIN_DIR}/libstdc++-6.dll
     ${MINGW_BIN_DIR}/zlib1.dll
     ${QT_BIN_DIR}/libwinpthread-1.dll
     ${QT_BIN_DIR}/Qt5Core.dll
     ${QT_BIN_DIR}/Qt5Gui.dll
     ${QT_BIN_DIR}/Qt5PrintSupport.dll
     ${QT_BIN_DIR}/Qt5Widgets.dll
     ${QT_BIN_DIR}/Qt5Svg.dll
     ${QT_BIN_DIR}/Qt5Xml.dll
   )
   install (FILES ${runtime_dlls} DESTINATION bin)
endif ()
