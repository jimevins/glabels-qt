/*  glabels_main.cpp
 *
 *  Copyright (C) 2011  Jim Evins <evins@snaught.com>
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

#include "MainWindow.h"
#include "libglabels/Db.h"

using namespace glabels;
using namespace libglabels;


int main( int argc, char **argv )
{
	QApplication app( argc, argv );

	QCoreApplication::setOrganizationName( "glabels.org" );
	QCoreApplication::setOrganizationDomain( "glabels.org" );
	QCoreApplication::setApplicationName( "glabels-qt" );

	Db::init();
	////// TEMPORARY TESTING ////////
#if 0
	Db::printKnownPapers();
	Db::printKnownCategories();
	Db::printKnownVendors();
	Db::printKnownTemplates();
#endif
	/////////////////////////////////

	MainWindow mainWin;
	mainWin.show();

	return app.exec();
}
