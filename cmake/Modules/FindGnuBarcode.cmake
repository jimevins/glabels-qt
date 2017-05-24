# - Try to find the GNU Barcode library
# Once done this will define
#
#  GNUBARCODE_FOUND - System has GNU Barcode
#  GNUBARCODE_INCLUDE_DIR - The GNU Barcode include directory
#  GNUBARCODE_LIBRARIES - The libraries needed to use GNU Barcode
#  GNUBARCODE_VERSION_STRING - the version of GNU Barcode found

set (GNUBARCODE_DEFINITIONS "")

find_path (GNUBARCODE_INCLUDE_DIR NAMES barcode.h PATH_SUFFIXES barcode)

find_library (GNUBARCODE_LIBRARIES NAMES barcode )

if (GNUBARCODE_INCLUDE_DIR AND EXISTS "${GNUBARCODE_INCLUDE_DIR}/barcode.h")
  file (STRINGS "${GNUBARCODE_INCLUDE_DIR}/barcode.h" BARCODE_H REGEX "^#define BARCODE_VERSION *\"[^\"]*\"")
  string (REGEX REPLACE "^.*VERSION *\"([^\"]*)\"" "\\1" GNUBARCODE_VERSION_STRING ${BARCODE_H})
endif()

# handle the QUIETLY and REQUIRED arguments and set GNUBARCODE_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GnuBarcode
                                  REQUIRED_VARS GNUBARCODE_LIBRARIES GNUBARCODE_INCLUDE_DIR
                                  VERSION_VAR GNUBARCODE_VERSION_STRING)

mark_as_advanced(GNUBARCODE_INCLUDE_DIR GNUBARCODE_LIBRARIES)
