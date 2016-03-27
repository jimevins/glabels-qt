/*  ColorHistory.cpp
 *
 *  Copyright (C) 2014  Jim Evins <evins@snaught.com>
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

#include "ColorHistory.h"

#include <QSettings>


ColorHistory::ColorHistory()
{
}


ColorHistory* ColorHistory::instance()
{
	static ColorHistory* singletonInstance = 0;

	if ( singletonInstance == 0 )
	{
		singletonInstance = new ColorHistory();
	}

	return singletonInstance;
}


void ColorHistory::addColor( const QColor &color )
{
	QColor oldColors[MAX_COLORS];
	QColor newColors[MAX_COLORS];
	int n;

	readColorArray( oldColors, &n );

	int i;
	newColors[0] = color;
	for ( i = 0; ( i < (MAX_COLORS-1) ) && (i < n); i++ )
	{
		newColors[i+1] = oldColors[i];
	}

	writeColorArray( newColors, i+1 );
	emit changed();
}


QColor ColorHistory::getColor( int i )
{
	QColor colors[MAX_COLORS];
	int n;

	readColorArray( colors, &n );
		
	if ( (n > 0) && (i < n) )
	{
		return colors[i];
	}
	else
	{
		return QColor( 0, 0, 0, 0 );
	}
}


void ColorHistory::readColorArray( QColor array[MAX_COLORS], int* n )
{
	QSettings settings;

	settings.beginGroup( "ColorHistory" );

	settings.beginReadArray( "history" );
	*n = settings.value( "history/size", 0 ).toInt();
	for ( int i = 0; i < *n; i++ )
	{
		settings.setArrayIndex(i);
		array[i] = settings.value( "color" ).value<QColor>();
	}
	settings.endArray();

	settings.endGroup();
}


void ColorHistory::writeColorArray( const QColor array[MAX_COLORS], int n )
{
	QSettings settings;

	settings.beginGroup( "ColorHistory" );

	settings.beginWriteArray( "history" );
	for ( int i = 0; (i < n) && (i < MAX_COLORS); i++ )
	{
		settings.setArrayIndex(i);
		settings.setValue( "color", array[i] );
	}
	settings.endArray();

	settings.endGroup();
}
