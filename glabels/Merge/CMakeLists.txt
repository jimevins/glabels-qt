cmake_minimum_required (VERSION 2.8)

###############################################################################
# gLabels Merge subsystem
###############################################################################
project (Merge CXX)


#=======================================
# Sources
#=======================================
set (merge_sources
  Merge.cpp
  MergeFactory.cpp
  MergeRecord.cpp
  MergeNone.cpp
  MergeText.cpp
  MergeTextCsv.cpp
)

set (merge_qobject_headers
  Merge.h
)

set (merge_forms
)

set (merge_resource_files
)

qt4_wrap_cpp (merge_moc_sources ${merge_qobject_headers})
qt4_wrap_ui (merge_forms_headers ${merge_forms})
qt4_add_resources (merge_qrc_sources ${merge_resource_files})

add_library (Merge STATIC
  ${merge_sources}
  ${merge_moc_sources}
  ${merge_qrc_sources}
  ${merge_forms_headers}
)


#=======================================
# Where to find stuff
#=======================================
include_directories (
)

link_directories (
)


#=======================================
# Subdirectories
#=======================================


#=======================================
# Install
#=======================================
