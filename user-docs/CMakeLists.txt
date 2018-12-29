add_custom_target (user-docs DEPENDS manpages)

set (man_sources
  man/glabels-qt.rst
  man/glabels-batch-qt.rst
)

#=======================================
# Rebuild man pages
#=======================================
foreach (_man_source ${man_sources})
  string (REGEX REPLACE "([^.]*)\.rst" "_build/\\1.1" _man_page ${_man_source})
  list (APPEND man_pages ${_man_page})
endforeach ()

add_custom_command (
  OUTPUT ${man_pages}
  COMMAND sphinx-build -M man ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/_build
  COMMENT "Generating man pages."
  DEPENDS ${man_sources} 
)

add_custom_target (manpages DEPENDS ${man_pages})

#=======================================
# Rebuild user manual
#=======================================
# TODO

#=======================================
# Install
#=======================================
install (FILES ${man_pages} DESTINATION share/man/man1)

