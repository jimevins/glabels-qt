# - Try to find the LibQrencode QRCode generator library
# Once done this will define
#
#  LIBQRENCODE_FOUND - System has LibQrencode
#  LIBQRENCODE_INCLUDE_DIR - The LibQrencode include directory
#  LIBQRENCODE_LIBRARIES - The libraries needed to use LibQrencode
#  LIBQRENCODE_DEFINITIONS - Compiler switches required for using LibQrencode
#  LIBQRENCODE_VERSION_STRING - the version of LibQrencode found

# use pkg-config to get the directories and then use these values with find_path() and find_library()
find_package(PkgConfig QUIET)
PKG_CHECK_MODULES(PC_LIBQRENCODE QUIET libqrencode)
set(LIBQRENCODE_DEFINITIONS ${PC_LIBQRENCODE_CFLAGS_OTHER})

find_path(LIBQRENCODE_INCLUDE_DIR NAMES qrencode.h
   HINTS
   ${PC_LIBQRENCODE_INCLUDEDIR}
   ${PC_LIBQRENCODE_INCLUDE_DIRS}
   PATH_SUFFIXES libqrencode
   )

find_library(LIBQRENCODE_LIBRARIES NAMES qrencode libqrencode
   HINTS
   ${PC_LIBQRENCODE_LIBDIR}
   ${PC_LIBQRENCODE_LIBRARY_DIRS}
   )

if(PC_LIBQRENCODE_VERSION)
    set(LIBQRENCODE_VERSION_STRING ${PC_LIBQRENCODE_VERSION})
endif()

# handle the QUIETLY and REQUIRED arguments and set LIBQRENCODE_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibQrencode
                                  REQUIRED_VARS LIBQRENCODE_LIBRARIES LIBQRENCODE_INCLUDE_DIR
                                  VERSION_VAR LIBQRENCODE_VERSION_STRING)

mark_as_advanced(LIBQRENCODE_INCLUDE_DIR LIBQRENCODE_LIBRARIES)
