cmake_minimum_required (VERSION 2.8)

project (qtLabels)


set (Package_Name "qtLabels")
set (Short_Name   "qtLabels")
set (Package_URL  "https://github.com/jimevins/qtLabels")

set (Major_Version   "0")
set (Minor_Version   "0")
set (Bugfix_Version  "0")

set (Package_Version "${Major_Version}.${Minor_Version}.${Bugfix_Version}")

set (Unique_Package_Name ${Package_Name}-${API_Version})


find_package(Qt4 REQUIRED)


add_definitions (-g)


#
# Subdirectories
#
add_subdirectory (app)

