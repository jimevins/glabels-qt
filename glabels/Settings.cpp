/*  Settings.cpp
 *
 *  Copyright (C) 2016  Jim Evins <evins@snaught.com>
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

#include "Settings.h"

#include <QLocale>
#include <QString>
#include <QtDebug>


Settings* Settings::mInstance = 0;


Settings::Settings()
{
}


void Settings::init()
{
	if ( mInstance == 0 )
	{
		mInstance = new Settings();
	}
}


Settings* Settings::instance()
{
	init();

	return mInstance;
}


glabels::Distance::Units Settings::units()
{
	// Guess at a suitable default
	QString defaultIdString;
	if ( QLocale::system().measurementSystem() == QLocale::ImperialSystem )
	{
		defaultIdString = glabels::Distance::toId( glabels::Distance::Units::IN );
	}
	else
	{
		defaultIdString = glabels::Distance::toId( glabels::Distance::Units::MM );
	}
	
	mInstance->beginGroup( "Locale" );
	QString idString = mInstance->value( "units", defaultIdString ).toString();
	mInstance->endGroup();

	return glabels::Distance::toUnits( idString );
}


void Settings::setUnits( glabels::Distance::Units units )
{
	QString idString = glabels::Distance::toId( units );

	mInstance->beginGroup( "Locale" );
	mInstance->setValue( "units", idString );
	mInstance->endGroup();

	emit mInstance->changed();
}


bool Settings::searchIsoPaperSizes()
{
	// Guess at a suitable default
	bool defaultValue;
	switch (QLocale::system().country())
	{
	case QLocale::UnitedStates:
	case QLocale::Canada:
		defaultValue = false;
		break;

	default:
		defaultValue = true;
		break;
	}
	
	mInstance->beginGroup( "Search" );
	bool returnValue = mInstance->value( "isoPaperSizes", defaultValue ).toBool();
	mInstance->endGroup();

	return returnValue;
}


void Settings::setSearchIsoPaperSizes( bool searchIsoPaperSizes )
{
	mInstance->beginGroup( "Search" );
	mInstance->setValue( "isoPaperSizes", searchIsoPaperSizes );
	mInstance->endGroup();

	emit mInstance->changed();
}


bool Settings::searchUsPaperSizes()
{
	// Guess at a suitable default
	bool defaultValue;
	switch (QLocale::system().country())
	{
	case QLocale::UnitedStates:
	case QLocale::Canada:
		defaultValue = true;
		break;

	default:
		defaultValue = false;
		break;
	}
	
	mInstance->beginGroup( "Search" );
	bool returnValue = mInstance->value( "usPaperSizes", defaultValue ).toBool();
	mInstance->endGroup();

	return returnValue;
}


void Settings::setSearchUsPaperSizes( bool searchUsPaperSizes )
{
	mInstance->beginGroup( "Search" );
	mInstance->setValue( "usPaperSizes", searchUsPaperSizes );
	mInstance->endGroup();

	emit mInstance->changed();
}


bool Settings::searchOtherPaperSizes()
{
	// Guess at a suitable default
	bool defaultValue = true;
	
	mInstance->beginGroup( "Search" );
	bool returnValue = mInstance->value( "otherPaperSizes", defaultValue ).toBool();
	mInstance->endGroup();

	return returnValue;
}


void Settings::setSearchOtherPaperSizes( bool searchOtherPaperSizes )
{
	mInstance->beginGroup( "Search" );
	mInstance->setValue( "otherPaperSizes", searchOtherPaperSizes );
	mInstance->endGroup();

	emit mInstance->changed();
}


bool Settings::searchAllCategories()
{
	// Guess at a suitable default
	bool defaultValue = true;
	
	mInstance->beginGroup( "Search" );
	bool returnValue = mInstance->value( "allCategories", defaultValue ).toBool();
	mInstance->endGroup();

	return returnValue;
}


void Settings::setSearchAllCategories( bool searchAllCategories )
{
	mInstance->beginGroup( "Search" );
	mInstance->setValue( "allCategories", searchAllCategories );
	mInstance->endGroup();

	emit mInstance->changed();
}


QStringList Settings::searchCategoryList()
{
	QStringList defaultList;
	
	mInstance->beginGroup( "Search" );
	QStringList returnList = mInstance->value( "categoryList", defaultList ).toStringList();
	mInstance->endGroup();

	return returnList;
}


void Settings::setSearchCategoryList( const QStringList& searchCategoryList )
{
	mInstance->beginGroup( "Search" );
	mInstance->setValue( "categoryList", searchCategoryList );
	mInstance->endGroup();

	emit mInstance->changed();
}
