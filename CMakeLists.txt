cmake_minimum_required (VERSION 2.8.12)

###############################################################################
# gLabels Label Designer Project
###############################################################################
project (glabels)

#
# Path for locally defined cmake modules
#
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


#=======================================
# Version Information
#=======================================
set (Website  "http://glabels.org")

set (Major_Version   "3")
set (Minor_Version   "99")
set (Micro_Version   "0")

set (Full_Version "${Major_Version}.${Minor_Version}.${Micro_Version}")


#=======================================
# Dependencies
#=======================================
if (MINGW)
   # Locate MINGW directories
   string (REPLACE "/g++.exe" "" MINGW_BIN_DIR  ${CMAKE_CXX_COMPILER})
   string (REPLACE "/bin"     "" MINGW_BASE_DIR ${MINGW_BIN_DIR})

   # Make sure we can find MINGW libraries, e.g. zlib
   set (CMAKE_PREFIX_PATH ${MINGW_BASE_DIR} )
endif ()

find_package(Qt5Widgets 5.4 REQUIRED)
find_package(Qt5PrintSupport 5.4 REQUIRED)
find_package(Qt5Xml 5.4 REQUIRED)
find_package(Qt5Svg 5.4 REQUIRED)
find_package(Qt5LinguistTools)

if (MINGW)
   # Locate Qt directories
   execute_process (COMMAND qtpaths --install-prefix OUTPUT_VARIABLE QT_BASE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
   set (QT_BIN_DIR ${QT_BASE_DIR}/bin)
endif ()

find_package(ZLIB 1.2 REQUIRED)

#
# Optional dependencies
#
find_package (GnuBarcode QUIET)
find_package (LibQrencode QUIET)
find_package (LibZint QUIET)

#=======================================
# Subdirectories
#=======================================
add_subdirectory (glbarcode)
add_subdirectory (glabels)
add_subdirectory (templates)
add_subdirectory (translations)
add_subdirectory (data)


#=======================================
# Print configuration information
#=======================================
message (STATUS "")
message (STATUS "Project name ............ " ${CMAKE_PROJECT_NAME})
message (STATUS "Project version ......... " ${Full_Version})
message (STATUS "Installation prefix ..... " ${CMAKE_INSTALL_PREFIX})
message (STATUS "Source code location .... " ${glabels_SOURCE_DIR})
message (STATUS "C++ Compiler ............ " ${CMAKE_CXX_COMPILER_ID} " " ${CMAKE_CXX_COMPILER} " " ${CMAKE_CXX_COMPILER_VERSION})
message (STATUS "Qt version .............. " ${Qt5Core_VERSION})
message (STATUS "zlib version ............ " ${ZLIB_VERSION_STRING})

if (GNUBARCODE_FOUND)
  message (STATUS "GNU Barcode (optional)... " ${GNUBARCODE_VERSION_STRING})
else (GNUBARCODE_FOUND)
  message (STATUS "GNU Barcode (optional)... No.")
endif (GNUBARCODE_FOUND)

if (LIBQRENCODE_FOUND)
  message (STATUS "qrencode (optional)...... " ${LIBQRENCODE_VERSION_STRING})
else (LIBQRENCODE_FOUND)
  message (STATUS "qrencode (optional)...... No.")
endif (LIBQRENCODE_FOUND)

if (LIBZINT_FOUND)
  message (STATUS "libzint (optional)....... " ${LIBZINT_VERSION_STRING})
else (LIBZINT_FOUND)
  message (STATUS "libzint (optional)....... No.")
endif (LIBZINT_FOUND)

if (MINGW)
   message (STATUS "MinGW location .......... " ${MINGW_BASE_DIR})
   message (STATUS "MinGW Qt location ....... " ${QT_BASE_DIR})
endif (MINGW)

message (STATUS "")

#
# Uncomment to print all CMake variables
#
# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
  
