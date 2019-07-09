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

endif (Qt5Test_FOUND)
