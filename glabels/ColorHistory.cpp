/*  ColorHistory.cpp
 *
 *  Copyright (C) 2014-2016  Jim Evins <evins@snaught.com>
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
#include <QtDebug>


namespace glabels
{

	ColorHistory::ColorHistory()
	{
		// empty
	}


	ColorHistory* ColorHistory::instance()
	{
		static ColorHistory* singletonInstance = nullptr;

		if ( singletonInstance == nullptr )
		{
			singletonInstance = new ColorHistory();
		}

		return singletonInstance;
	}


	void ColorHistory::addColor( const QColor &color )
	{
		QList<QColor> colorList = readColorList();

		// Remove any occurances of this color already in list
		colorList.removeAll( color );

		// Now add to list
		colorList.append( color );

		// Remove oldest colors, if size exceeds current max
		while ( colorList.size() > MAX_COLORS )
		{
			colorList.removeFirst();
		}

		writeColorList( colorList );
	
		emit changed();
	}


	QList<QColor> ColorHistory::getColors()
	{
		return readColorList();
	}


	QColor ColorHistory::getColor( int id )
	{
		QList<QColor> colors = readColorList();
		return colors[id];
	}


	QList<QColor> ColorHistory::readColorList()
	{
		QStringList defaultList;
		QSettings settings;

		settings.beginGroup( "ColorHistory" );
		QStringList colorNameList = settings.value( "colors", defaultList ).toStringList();
		settings.endGroup();

		QList<QColor> colorList;
		foreach ( QString colorName, colorNameList )
		{
			colorList << QColor( colorName );
		}

		// Remove oldest colors, if size exceeds current max
		while ( colorList.size() > MAX_COLORS )
		{
			colorList.removeFirst();
		}

		return colorList;
	}


	void ColorHistory::writeColorList( const QList<QColor>& colorList )
	{
		// Build name list
		QStringList colorNameList;
		foreach ( QColor color, colorList )
		{
			colorNameList << color.name();
		}

		// Save
		QSettings settings;
		settings.beginGroup( "ColorHistory" );
		settings.setValue( "colors", colorNameList );
		settings.endGroup();
	}

} // namespace glabels
