# - Try to find the Zint barcode library
# Once done this will define
#
#  LIBZINT_FOUND - System has Zint barcode
#  LIBZINT_INCLUDE_DIR - The Zint barcode include directory
#  LIBZINT_LIBRARIES - The libraries needed to use Zint barcode
#  LIBZINT_VERSION_STRING - the version of Zint barcode found

set (LIBZINT_DEFINITIONS "")

find_path (LIBZINT_INCLUDE_DIR NAMES zint.h)

find_library (LIBZINT_LIBRARIES NAMES zint )

if (LIBZINT_INCLUDE_DIR AND EXISTS "${LIBZINT_INCLUDE_DIR}/zint.h")
  file (STRINGS "${LIBZINT_INCLUDE_DIR}/zint.h" ZINT_MAJOR_H REGEX "^#define ZINT_VERSION_MAJOR *[0-9]*")
  file (STRINGS "${LIBZINT_INCLUDE_DIR}/zint.h" ZINT_MINOR_H REGEX "^#define ZINT_VERSION_MINOR *[0-9]*")
  file (STRINGS "${LIBZINT_INCLUDE_DIR}/zint.h" ZINT_MICRO_H REGEX "^#define ZINT_VERSION_RELEASE *[0-9]*")
  string (REGEX REPLACE "^.*VERSION_MAJOR *([0-9]*)" "\\1" ZINT_MAJOR ${ZINT_MAJOR_H})
  string (REGEX REPLACE "^.*VERSION_MINOR *([0-9]*)" "\\1" ZINT_MINOR ${ZINT_MINOR_H})
  string (REGEX REPLACE "^.*VERSION_RELEASE *([0-9]*)" "\\1" ZINT_MICRO ${ZINT_MICRO_H})
  set (LIBZINT_VERSION_STRING ${ZINT_MAJOR}.${ZINT_MINOR}.${ZINT_MICRO})
endif()

# handle the QUIETLY and REQUIRED arguments and set LIBZINT_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibZint
                                  REQUIRED_VARS LIBZINT_LIBRARIES LIBZINT_INCLUDE_DIR
                                  VERSION_VAR LIBZINT_VERSION_STRING)

mark_as_advanced(LIBZINT_INCLUDE_DIR LIBZINT_LIBRARIES)
