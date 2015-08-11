/*  Units.cpp
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
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

#include "Units.h"

#include <QDebug>


namespace
{
        const double POINTS_PER_POINT =  1.0; /* internal units are points. */
        const double POINTS_PER_INCH  = 72.0;
        const double POINTS_PER_MM    =  2.83464566929;
        const double POINTS_PER_CM    =  (10.0*POINTS_PER_MM);
        const double POINTS_PER_PICA  =  (1.0/12.0);
}


namespace libglabels
{

	Units::Units( const QString &id, const QString &name, double pointsPerUnit )
		: mId(id), mName(name), mPointsPerUnit(pointsPerUnit)
	{
		mUnitsPerPoint = 1.0 / mPointsPerUnit;
	}


	Units *Units::fromId( const QString &id )
	{
		if ( id == "pt" )
		{
			return point();
		}
		else if ( id == "in" )
		{
			return inch();
		}
		else if ( id == "mm" )
		{
			return mm();
		}
		else if ( id == "cm" )
		{
			return cm();
		}
		else if ( id == "pc" )
		{
			return pica();
		}
		else if ( id == "" )
		{
			/* Missing or empty units id defaults to points. */
			return point();
		}
		else
		{
			qWarning() << "Unknown Units ID \"" << id << "\", defaults to \"pt\"";
			return point();
		}

	}


	Units *Units::point()
	{
		static Units *instance = NULL;

		if ( instance == NULL )
		{
			instance = new Units( "pt", tr("points"), POINTS_PER_POINT );
		}

		return instance;
	}


	Units *Units::inch()
	{
		static Units *instance = NULL;

		if ( instance == NULL )
		{
			instance = new Units( "in", tr("inches"), POINTS_PER_INCH );
		}

		return instance;
	}


	Units *Units::mm()
	{
		static Units *instance = NULL;

		if ( instance == NULL )
		{
			instance = new Units( "mm", tr("mm"), POINTS_PER_MM );
		}

		return instance;
	}


	Units *Units::cm()
	{
		static Units *instance = NULL;

		if ( instance == NULL )
		{
			instance = new Units( "cm", tr("cm"), POINTS_PER_CM );
		}

		return instance;
	}


	Units *Units::pica()
	{
		static Units *instance = NULL;

		if ( instance == NULL )
		{
			instance = new Units( "pc", tr("picas"), POINTS_PER_PICA );
		}

		return instance;
	}


	bool Units::isIdValid( QString id )
	{
		return ( (id == "pt") || (id == "in") || (id == "mm") || (id == "cm") || (id == "pc") || (id == "") );
	}

}
