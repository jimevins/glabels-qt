if (Qt5Test_FOUND)

  #=======================================
  # Test SubstitutionField class
  #=======================================
  qt5_wrap_cpp (TestSubstitutionField_moc_sources TestSubstitutionField.h)
  add_executable (TestSubstitutionField TestSubstitutionField.cpp ${TestSubstitutionField_moc_sources})
  target_link_libraries (TestSubstitutionField Model Qt5::Test)
  add_test (NAME SubstitutionField COMMAND TestSubstitutionField)

endif (Qt5Test_FOUND)
