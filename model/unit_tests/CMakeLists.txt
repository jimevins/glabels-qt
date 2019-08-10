if (Qt5Test_FOUND)

  #=======================================
  # Test SubstitutionField class
  #=======================================
  qt5_wrap_cpp (TestSubstitutionField_moc_sources TestSubstitutionField.h)
  add_executable (TestSubstitutionField TestSubstitutionField.cpp ${TestSubstitutionField_moc_sources})
  target_link_libraries (TestSubstitutionField Model Qt5::Test)
  add_test (NAME SubstitutionField COMMAND TestSubstitutionField)

  #=======================================
  # Test XmlUtil class
  #=======================================
  qt5_wrap_cpp (TestXmlUtil_moc_sources TestXmlUtil.h)
  add_executable (TestXmlUtil TestXmlUtil.cpp ${TestXmlUtil_moc_sources})
  target_link_libraries (TestXmlUtil Model Qt5::Test)
  add_test (NAME XmlUtil COMMAND TestXmlUtil)

  #=======================================
  # Test XmlLabelCreator/Parser classes
  #=======================================
  qt5_wrap_cpp (TestXmlLabel_moc_sources TestXmlLabel.h)
  add_executable (TestXmlLabel TestXmlLabel.cpp ${TestXmlLabel_moc_sources})
  target_link_libraries (TestXmlLabel Model Qt5::Test)
  add_test (NAME XmlLabel COMMAND TestXmlLabel)

  #=======================================
  # Test Barcode classes
  #=======================================
  qt5_wrap_cpp (TestBarcode_moc_sources TestBarcode.h)
  add_executable (TestBarcode TestBarcode.cpp ${TestBarcode_moc_sources})
  target_link_libraries (TestBarcode Model Qt5::Test)
  add_test (NAME Barcode COMMAND TestBarcode)

  #=======================================
  # Test ColorNode class
  #=======================================
  qt5_wrap_cpp (TestColorNode_moc_sources TestColorNode.h)
  add_executable (TestColorNode TestColorNode.cpp ${TestColorNode_moc_sources})
  target_link_libraries (TestColorNode Model Qt5::Test)
  add_test (NAME ColorNode COMMAND TestColorNode)

  #=======================================
  # Test Merge classes
  #=======================================
  qt5_wrap_cpp (TestMerge_moc_sources TestMerge.h)
  add_executable (TestMerge TestMerge.cpp ${TestMerge_moc_sources})
  target_link_libraries (TestMerge Model Qt5::Test)
  add_test (NAME Merge COMMAND TestMerge)

  #=======================================
  # Test Model class
  #=======================================
  qt5_wrap_cpp (TestModel_moc_sources TestModel.h)
  add_executable (TestModel TestModel.cpp ${TestModel_moc_sources})
  target_link_libraries (TestModel Model Qt5::Test)
  add_test (NAME Model COMMAND TestModel)

  #=======================================
  # Test ModelBarcodeObject class
  #=======================================
  qt5_wrap_cpp (TestModelBarcodeObject_moc_sources TestModelBarcodeObject.h)
  add_executable (TestModelBarcodeObject TestModelBarcodeObject.cpp ${TestModelBarcodeObject_moc_sources})
  target_link_libraries (TestModelBarcodeObject Model Qt5::Test)
  add_test (NAME ModelBarcodeObject COMMAND TestModelBarcodeObject)

  #=======================================
  # Test ModelBoxObject class
  #=======================================
  qt5_wrap_cpp (TestModelBoxObject_moc_sources TestModelBoxObject.h)
  add_executable (TestModelBoxObject TestModelBoxObject.cpp ${TestModelBoxObject_moc_sources})
  target_link_libraries (TestModelBoxObject Model Qt5::Test)
  add_test (NAME ModelBoxObject COMMAND TestModelBoxObject)

  #=======================================
  # Test ModelEllipseObject class
  #=======================================
  qt5_wrap_cpp (TestModelEllipseObject_moc_sources TestModelEllipseObject.h)
  add_executable (TestModelEllipseObject TestModelEllipseObject.cpp ${TestModelEllipseObject_moc_sources})
  target_link_libraries (TestModelEllipseObject Model Qt5::Test)
  add_test (NAME ModelEllipseObject COMMAND TestModelEllipseObject)

  #=======================================
  # Test ModelImageObject class
  #=======================================
  qt5_wrap_cpp (TestModelImageObject_moc_sources TestModelImageObject.h)
  add_executable (TestModelImageObject TestModelImageObject.cpp ${TestModelImageObject_moc_sources})
  target_link_libraries (TestModelImageObject Model Qt5::Test)
  add_test (NAME ModelImageObject COMMAND TestModelImageObject)

  #=======================================
  # Test ModelLineObject class
  #=======================================
  qt5_wrap_cpp (TestModelLineObject_moc_sources TestModelLineObject.h)
  add_executable (TestModelLineObject TestModelLineObject.cpp ${TestModelLineObject_moc_sources})
  target_link_libraries (TestModelLineObject Model Qt5::Test)
  add_test (NAME ModelLineObject COMMAND TestModelLineObject)

  #=======================================
  # Test ModelTextObject class
  #=======================================
  qt5_wrap_cpp (TestModelTextObject_moc_sources TestModelTextObject.h)
  add_executable (TestModelTextObject TestModelTextObject.cpp ${TestModelTextObject_moc_sources})
  target_link_libraries (TestModelTextObject Model Qt5::Test)
  add_test (NAME ModelTextObject COMMAND TestModelTextObject)

  #=======================================
  # Test RawText class
  #=======================================
  qt5_wrap_cpp (TestRawText_moc_sources TestRawText.h)
  add_executable (TestRawText TestRawText.cpp ${TestRawText_moc_sources})
  target_link_libraries (TestRawText Model Qt5::Test)
  add_test (NAME RawText COMMAND TestRawText)

  #=======================================
  # Test TextNode class
  #=======================================
  qt5_wrap_cpp (TestTextNode_moc_sources TestTextNode.h)
  add_executable (TestTextNode TestTextNode.cpp ${TestTextNode_moc_sources})
  target_link_libraries (TestTextNode Model Qt5::Test)
  add_test (NAME TextNode COMMAND TestTextNode)

endif (Qt5Test_FOUND)
