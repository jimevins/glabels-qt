/*  glabels_main.cpp
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
 *
 *  This file is part of gLabels-qt.
 *
 *  gLabels-qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gLabels-qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gLabels-qt.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <QApplication>

#include "libglabels/Db.h"
#include "Merge/Factory.h"
#include "Settings.h"
#include "MainWindow.h"


int main( int argc, char **argv )
{
	QApplication app( argc, argv );

	QCoreApplication::setOrganizationName( "glabels.org" );
	QCoreApplication::setOrganizationDomain( "glabels.org" );
	QCoreApplication::setApplicationName( "glabels-qt" );

	Settings::init();
	glabels::Db::init();
	merge::Factory::init();
	////// TEMPORARY TESTING ////////
#if 0
	glabels::Db::printKnownPapers();
	glabels::Db::printKnownCategories();
	glabels::Db::printKnownVendors();
	glabels::Db::printKnownTemplates();
#endif
	/////////////////////////////////

	/// @TODO open file(s) from command line if present, otherwise start wizard
	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
