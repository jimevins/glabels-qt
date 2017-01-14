cmake_minimum_required (VERSION 2.8.12)

###############################################################################
# Top-Level gLabels project
###############################################################################
project (glabels_qt)


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
# Compilation
#=======================================
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions (-std=c++11 -g)
if (NOT WIN32)
	add_definitions (-fPIC)
endif ()


#=======================================
# Subdirectories
#=======================================
add_subdirectory (glabels)

