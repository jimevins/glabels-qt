cmake_minimum_required (VERSION 3.2)

###############################################################################
# gLabels Label Designer Project
###############################################################################
project (glabels-qt VERSION "3.99.0")

#
# Path for locally defined cmake modules
#
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


#=======================================
# Packaging and Version Information
#=======================================
set (Website  "glabels.org")
set (CPACK_PACKAGE_VENDOR ${Website})

set (CPACK_PACKAGE_NAME glabels)

string (TIMESTAMP _date "%Y%m%d")
set (CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set (CPACK_PACKAGE_VERSION_TWEAK ${_date})

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "gLabels Label Designer")
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")

set (CPACK_PACKAGE_EXECUTABLES "glabels-qt;gLabels")
set (CPACK_CREATE_DESKTOP_LINKS "glabels-qt")

set (CPACK_NSIS_DISPLAY_NAME "gLabels")
set (CPACK_NSIS_URL_INFO_ABOUT "http://${Website}")
set (CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/glabels/windows-icon/glabels.ico")
set (CPACK_NSIS_MODIFY_PATH "ON")

include (CPack)


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

find_package (Qt5Core 5.4 REQUIRED)
find_package (Qt5Widgets 5.4 REQUIRED)
find_package (Qt5PrintSupport 5.4 REQUIRED)
find_package (Qt5Xml 5.4 REQUIRED)
find_package (Qt5Svg 5.4 REQUIRED)
find_package (Qt5LinguistTools)

if (WIN32)
   # Locate Qt directories
   execute_process (COMMAND qtpaths --install-prefix OUTPUT_VARIABLE QT_BASE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
   set (QT_BIN_DIR ${QT_BASE_DIR}/bin)
endif ()

#
# Optional dependencies
#
find_package (ZLIB 1.2 QUIET)
find_package (GnuBarcode 0.98 QUIET)
find_package (LibQrencode 3.4 QUIET)
find_package (LibZint 2.6 QUIET)
# Unit testing support
find_package (Qt5Test 5.4 QUIET)


#=======================================
# Global compiler options
#=======================================
#
# Uncomment to compile everything with aggressively pedantic options
# (not recommended -- only for testing -- also not portable)
#
#add_compile_options("-Wall" "-Werror" "-Wpedantic")
add_compile_options("-g")


#=======================================
# Unit Testing
#=======================================
if (Qt5Test_FOUND)
  enable_testing ()
endif ()

#=======================================
# Subdirectories
#=======================================
add_subdirectory (glbarcode)
add_subdirectory (backends)
add_subdirectory (model)
add_subdirectory (glabels)
add_subdirectory (glabels-batch)
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

if (ZLIB_FOUND)
  message (STATUS "zlib (optional).......... " ${ZLIB_VERSION_STRING})
else (ZLIB_FOUND)
  message (STATUS "zlib (optional).......... No.")
endif (ZLIB_FOUND)

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

if (Qt5Test_FOUND)
  message (STATUS "QtTest (optional)........ " ${Qt5Test_VERSION})
else (Qt5Test_FOUND)
  message (STATUS "QtTest (optional)........ No.")
endif (Qt5Test_FOUND)

if (MSVC)
   message (STATUS "MSVC Qt location ........ " ${QT_BASE_DIR})
endif (MSVC)

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
  
