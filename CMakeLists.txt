cmake_minimum_required (VERSION 2.8.12)

###############################################################################
# gLabels Label Designer Project
###############################################################################
project (glabels)


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

if (MINGW)
   message (STATUS "MinGW location .......... " ${MINGW_BASE_DIR})
   message (STATUS "MinGW Qt location ....... " ${QT_BASE_DIR})
endif ()

message (STATUS "")

#
# Uncomment to print all CMake variables
#
# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
  
