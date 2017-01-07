/*  Distance.h
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

#ifndef glabels_Distance_h
#define glabels_Distance_h


#include <QCoreApplication>
#include <QString>

#include "Units.h"


namespace glabels
{


	class Distance
	{
		Q_DECLARE_TR_FUNCTIONS(Distance)

	public:
		Distance();
		Distance( double d, Units::Enum unitsEnum = Units::PT );
		Distance( double d, const Units& units );
		Distance( double d, const QString& unitsId );

		static Distance pt( double dPts );
		static Distance in( double dInches );
		static Distance mm( double dMm );
		static Distance cm( double dCm );
		static Distance pc( double dPicas );
		static Distance fromString( const QString& string );


		double pt() const;
		double in() const;
		double mm() const;
		double cm() const;
		double pc() const;
		double inUnits( const Units& units ) const;
		double inUnits( Units::Enum unitsEnum ) const;
		double inUnits( const QString& unitsId ) const;


		QString toString( const Units& units ) const;
		QString toString( Units::Enum unitsEnum ) const;
		QString toString( const QString& unitsId ) const;


		Distance& operator+=( const Distance& d );
		Distance& operator-=( const Distance& d );
		Distance operator-();

		friend inline Distance operator+( const Distance& d1, const Distance& d2 );
		friend inline Distance operator-( const Distance& d1, const Distance& d2 );
		friend inline Distance operator*( double x, const Distance& d );
		friend inline Distance operator*( const Distance& d, double x );
		friend inline double   operator/( const Distance& d1, const Distance& d2 );
		friend inline Distance operator/( const Distance& d, double x );
		
		friend inline bool operator<( const Distance& d1, const Distance& d2 );
		friend inline bool operator<=( const Distance& d1, const Distance& d2 );
		friend inline bool operator>( const Distance& d1, const Distance& d2 );
		friend inline bool operator>=( const Distance& d1, const Distance& d2 );
		friend inline bool operator==( const Distance& d1, const Distance& d2 );
		friend inline bool operator!=( const Distance& d1, const Distance& d2 );
		
		friend inline Distance fabs( const Distance& d );
		friend inline Distance min( const Distance& d1, const Distance& d2 );
		friend inline Distance max( const Distance& d1, const Distance& d2 );
		friend inline Distance fmod( const Distance& d1, const Distance& d2 );

		
	private:
		double mDPts;

	};

}


#include "Distance.inl"


#endif // glabels_Distance_h
