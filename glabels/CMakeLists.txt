project (glabels LANGUAGES CXX)

#=======================================
# Sources
#=======================================
set (glabels_sources
  main.cpp
  AboutDialog.cpp
  BarcodeMenu.cpp
  BarcodeMenuButton.cpp
  BarcodeMenuItem.cpp
  ColorButton.cpp
  ColorHistory.cpp
  ColorPaletteDialog.cpp
  ColorPaletteItem.cpp
  ColorPaletteButtonItem.cpp
  ColorSwatch.cpp
  Cursors.cpp
  FieldButton.cpp
  File.cpp
  Help.cpp
  Icons.cpp
  LabelEditor.cpp
  MainWindow.cpp
  MergeView.cpp
  MiniPreviewPixmap.cpp
  ObjectEditor.cpp
  PreferencesDialog.cpp
  PrintView.cpp
  PropertiesView.cpp
  Preview.cpp
  PreviewOverlayItem.cpp
  SelectProductDialog.cpp
  SimplePreview.cpp
  StartupView.cpp
  TemplatePicker.cpp
  TemplatePickerItem.cpp
  UndoRedoModel.cpp
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
  MainWindow.h
  MergeView.h
  ObjectEditor.h
  PreferencesDialog.h
  PrintView.h
  PropertiesView.h
  Preview.h
  SelectProductDialog.h
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

#=====================================
# Target
#=====================================
add_executable (glabels-qt WIN32
  ${glabels_sources}
  ${glabels_moc_sources}
  ${glabels_qrc_sources}
  ${glabels_forms_headers}
  ${glabels_win_rc}
)

#target_compile_features (glabels-qt
#  PUBLIC cxx_std_11
#)
set_property (TARGET glabels-qt PROPERTY CXX_STANDARD 11)

target_include_directories (glabels-qt
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries (glabels-qt
  Model
  Qt5::Widgets
)

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
