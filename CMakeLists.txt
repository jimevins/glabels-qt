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
if (WIN32)
	# Make sure we can find MINGW libraries, e.g. zlib
	set (CMAKE_PREFIX_PATH C:/MinGW )
endif ()

find_package(Qt5Widgets 5.4 REQUIRED)
find_package(Qt5PrintSupport 5.4 REQUIRED)
find_package(Qt5Xml 5.4 REQUIRED)
find_package(Qt5Svg 5.4 REQUIRED)

find_package(ZLIB 1.2 REQUIRED)


#=======================================
# Subdirectories
#=======================================
add_subdirectory (glabels)
add_subdirectory (templates)
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
message (STATUS "")

#
# Uncomment to print all CMake variables
#
# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
  
