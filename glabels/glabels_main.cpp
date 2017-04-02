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

#include "FileUtil.h"
#include "Db.h"
#include "MainWindow.h"
#include "Settings.h"

#include "Merge/Factory.h"

#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>
#include <QtDebug>


int main( int argc, char **argv )
{
	QApplication app( argc, argv );

	QCoreApplication::setOrganizationName( "glabels.org" );
	QCoreApplication::setOrganizationDomain( "glabels.org" );
	QCoreApplication::setApplicationName( "glabels-qt" );

	//
	// Setup translators
	//
	QLocale locale = QLocale::system();
	QString qtTranslationsDir = QLibraryInfo::location( QLibraryInfo::TranslationsPath );
	QString myTranslationsDir = glabels::FileUtil::translationsDir().canonicalPath();
	
	QTranslator qtTranslator;
	if ( qtTranslator.load( locale, "qt", "_", qtTranslationsDir ) )
	{
		app.installTranslator(&qtTranslator);
	}

	QTranslator glabelsTranslator;
	if ( glabelsTranslator.load( locale, "glabels", "_", myTranslationsDir ) )
	{
		app.installTranslator(&glabelsTranslator);
	}

	QTranslator templatesTranslator;
	if ( templatesTranslator.load( locale, "templates", "_", myTranslationsDir ) )
	{
		app.installTranslator(&templatesTranslator);
	}

	
	//
	// Initialize subsystems
	//
	glabels::Settings::init();
	glabels::Db::init();
	glabels::merge::Factory::init();

	
	/// @TODO open file(s) from command line if present, otherwise start wizard

	
	//
	// Launch main window
	//
	glabels::MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
