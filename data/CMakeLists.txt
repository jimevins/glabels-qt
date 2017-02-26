cmake_minimum_required (VERSION 2.8.12)

###############################################################################
# gLabels data subproject
###############################################################################
project (data)

#=======================================
# Install
#=======================================
install (FILES glabels-qt.desktop           DESTINATION share/applications)
install (FILES x-glabels-document.mime.xml  DESTINATION share/mime/packages)
install (FILES glabels-qt.appdata.xml       DESTINATION share/appdata)

