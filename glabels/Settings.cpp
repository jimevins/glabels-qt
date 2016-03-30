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


bool Settings::preferIsoPaperSizes()
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
	
	mInstance->beginGroup( "Locale" );
	bool returnValue = mInstance->value( "preferIsoPaperSizes", defaultValue ).toBool();
	mInstance->endGroup();

	return returnValue;
}


void Settings::setPreferIsoPaperSizes( bool preferIsoPaperSizes )
{
	
	mInstance->beginGroup( "Locale" );
	mInstance->setValue( "preferIsoPaperSizes", preferIsoPaperSizes );
	mInstance->endGroup();

	emit mInstance->changed();
}


glabels::Distance::Units Settings::units()
{
	// Guess at a suitable default
	QString defaultIdString;
	switch (QLocale::system().measurementSystem())
	{
	case QLocale::ImperialSystem:
		defaultIdString = "in";
		break;
	default:
		defaultIdString = "mm";
		break;
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
