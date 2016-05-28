cmake_minimum_required (VERSION 2.8.12)

###############################################################################
# Top-Level gLabels project
###############################################################################
project (glabels_qt)


#=======================================
# Package and Version Information
#=======================================
set (Package_Name "glabels-qt")
set (Short_Name   "glabels-qt")
set (Package_URL  "https://github.com/jimevins/glabels-qt")

set (Major_Version   "0")
set (Minor_Version   "0")
set (Bugfix_Version  "0")

set (Package_Version "${Major_Version}.${Minor_Version}.${Bugfix_Version}")

set (Unique_Package_Name ${Package_Name}-${API_Version})


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
add_subdirectory (libglabels)

