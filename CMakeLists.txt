cmake_minimum_required (VERSION 2.8)

project (glabels_qt)


set (Package_Name "glabels-qt")
set (Short_Name   "glabels-qt")
set (Package_URL  "https://github.com/jimevins/glabels-qt")

set (Major_Version   "0")
set (Minor_Version   "0")
set (Bugfix_Version  "0")

set (Package_Version "${Major_Version}.${Minor_Version}.${Bugfix_Version}")

set (Unique_Package_Name ${Package_Name}-${API_Version})

if (WIN32)
	# Make sure we can find MINGW libraries, e.g. zlib
	set (CMAKE_PREFIX_PATH C:/MinGW )
endif ()
	
find_package(Qt4 4.8.4 REQUIRED QtCore QtGui QtXml)
find_package(ZLIB REQUIRED)


add_definitions (-std=c++11 -g)


#
# Subdirectories
#
add_subdirectory (glabels)
add_subdirectory (libglabels)

