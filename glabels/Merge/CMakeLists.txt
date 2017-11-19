#=======================================
# Sources
#=======================================
set (merge_sources
  Factory.cpp
  Record.cpp
  Merge.cpp
  None.cpp
  Text.cpp
  TextCsv.cpp
  TextCsvKeys.cpp
  TextTsv.cpp
  TextTsvKeys.cpp
  TextColon.cpp
  TextColonKeys.cpp
  TextSemicolon.cpp
  TextSemicolonKeys.cpp
  SubstitutionField.cpp
)

set (merge_qobject_headers
  Merge.h
)

qt5_wrap_cpp (merge_moc_sources ${merge_qobject_headers})

add_library (Merge STATIC
  ${merge_sources}
  ${merge_moc_sources}
)


#=======================================
# Where to find stuff
#=======================================
include_directories (
  ${Qt5Widgets_INCLUDE_DIRS}
)

link_directories (
)


#=======================================
# Subdirectories
#=======================================
add_subdirectory (unit_tests)


#=======================================
# Install
#=======================================
