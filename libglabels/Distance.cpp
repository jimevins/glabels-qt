/*  Distance.cpp
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

#include "Distance.h"

#include <QTextStream>
#include <QtDebug>


namespace libglabels
{

	QString Distance::toId( Units units )
	{
		QString idString;
		
		switch (units)
		{
		case Units::PT:
			idString = "pt";
			break;
		case Units::IN:
			idString = "in";
			break;
		case Units::MM:
			idString = "mm";
			break;
		case Units::CM:
			idString = "cm";
			break;
		case Units::PC:
			idString = "pc";
			break;
		}

		return idString;
	}
	

	QString Distance::toTrName( Units units )
	{
		QString nameString;
		
		switch (units)
		{
		case Units::PT:
			nameString = tr("points");
			break;
		case Units::IN:
			nameString = tr("inches");
			break;
		case Units::MM:
			nameString = tr("mm");
			break;
		case Units::CM:
			nameString = tr("cm");
			break;
		case Units::PC:
			nameString = tr("picas");
			break;
		}

		return nameString;
	}
	

	bool Distance::isIdValid( const QString& unitsId )
	{
		bool retValue = false;
		
		if ( unitsId == "pt" )
		{
			retValue = true;
		}
		else if ( unitsId == "in" )
		{
			retValue = true;
		}
		else if ( unitsId == "mm" )
		{
			retValue = true;
		}
		else if ( unitsId == "cm" )
		{
			retValue = true;
		}
		else if ( unitsId == "pc" )
		{
			retValue = true;
		}

		return retValue;
	}

	
	Distance::Units Distance::toUnits( const QString& unitsId )
	{
		Units units;

		if ( unitsId == "pt" )
		{
			units = Units::PT;
		}
		else if ( unitsId == "in" )
		{
			units = Units::IN;
		}
		else if ( unitsId == "mm" )
		{
			units = Units::MM;
		}
		else if ( unitsId == "cm" )
		{
			units = Units::CM;
		}
		else if ( unitsId == "pc" )
		{
			units = Units::PC;
		}
		else
		{
			units = Units::PT;
		}

		return units;
	}

	
	Distance::Distance( double d, Units units )
	{
		switch (units)
		{
		case Units::PT:
			mDPts = d;
			break;
		case Units::IN:
			mDPts = d * PTS_PER_INCH;
			break;
		case Units::MM:
			mDPts = d * PTS_PER_MM;
			break;
		case Units::CM:
			mDPts = d * PTS_PER_CM;
			break;
		case Units::PC:
			mDPts = d * PTS_PER_PICA;
			break;
		}
	}


	Distance::Distance( double d, const QString& unitsId )
	{
		Units units = toUnits( unitsId );
		
		switch (units)
		{
		case Units::PT:
			mDPts = d;
			break;
		case Units::IN:
			mDPts = d * PTS_PER_INCH;
			break;
		case Units::MM:
			mDPts = d * PTS_PER_MM;
			break;
		case Units::CM:
			mDPts = d * PTS_PER_CM;
			break;
		case Units::PC:
			mDPts = d * PTS_PER_PICA;
			break;
		}
	}


	Distance Distance::fromString( const QString& string )
	{
		QString stringCopy = string;
		QTextStream valueStream( &stringCopy, QIODevice::ReadOnly );

		double value;
		QString unitsString;
		valueStream >> value >> unitsString;

		if ( !unitsString.isEmpty() && !isIdValid( unitsString ) )
		{
			qWarning() << "Error: invalid Distance::Units \"" << string << "\"";
		}

		return Distance( value, unitsString );
	}


	double Distance::inUnits( Units units ) const
	{
		double d;

		switch (units)
		{
		case Units::PT:
			d = pt();
			break;
		case Units::IN:
			d = in();
			break;
		case Units::MM:
			d = mm();
			break;
		case Units::CM:
			d = cm();
			break;
		case Units::PC:
			d = pc();
			break;
		}

		return d;
	}
	

	double Distance::inUnits( const QString& unitsId ) const
	{
		return inUnits( toUnits( unitsId ) );
	}


	QString Distance::toString( Units units ) const
	{
		return QString::number( inUnits(units) ) + toId(units);
	}


	QString Distance::toString( const QString& unitsId ) const
	{
		return QString::number( inUnits(unitsId) ) + unitsId;
	}
}
