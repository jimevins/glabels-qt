#=======================================
# Translation files
#=======================================
# without this a "make clean" would delete the .ts files
set_directory_properties (PROPERTIES CLEAN_NO_CUSTOM 1)

#
# gLabels Translation Files
#
set (glabels_ts_files
  glabels_C.ts
)

#
# Template Translation Files
#
set (templates_ts_files
  templates_C.ts
)

qt5_create_translation (glabels_qm_files
  ${CMAKE_SOURCE_DIR}/glabels ${glabels_ts_files}
)

qt5_create_translation (templates_qm_files
  ${CMAKE_CURRENT_BINARY_DIR}/template-strings.h ${templates_ts_files}
  OPTIONS -locations none
)

add_custom_target (update_translations DEPENDS ${glabels_qm_files} ${templates_qm_files})

# Add updating translations as a dependency for glabels-qt
add_dependencies (glabels-qt update_translations)


#=======================================
# Compilation
#=======================================
add_compile_options (-std=c++11 -g)
if (NOT WIN32)
   add_compile_options (-fPIC)
endif ()


#=======================================
# XmlStrings utility
#=======================================
set (XmlStrings_sources
  XmlStrings.cpp
)

add_executable (XmlStrings WIN32
  ${XmlStrings_sources}
)

target_link_libraries (XmlStrings
  ${Qt5Xml_LIBRARIES}
  ${Qt5Svg_LIBRARIES}
)

include_directories (
  ${Qt5Xml_INCLUDE_DIRS}
  ${Qt5Svg_INCLUDE_DIRS}
)


#=======================================
# Extract translatable strings from XML
# template files.
#=======================================
# Use absolute locations of XML files
string (REGEX REPLACE "([^;]+)" "${CMAKE_SOURCE_DIR}/templates/\\1"
  xml_files "${template_files};${other_db_files}"
)

add_custom_command (
  OUTPUT template-strings.h
  COMMAND XmlStrings ${xml_files} > template-strings.h
  COMMENT "Extracting template strings."
  DEPENDS XmlStrings ${xml_files}
)

set_source_files_properties (template-strings.h PROPERTIES GENERATED TRUE)

add_custom_target (template-strings DEPENDS template-strings.h)


#=======================================
# Subdirectories
#=======================================


#=======================================
# Install
#=======================================
install (FILES ${glabels_qm_files}   DESTINATION share/glabels-qt/translations)
install (FILES ${templates_qm_files} DESTINATION share/glabels-qt/translations)
