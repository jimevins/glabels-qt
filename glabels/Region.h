/*  Region.h
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

#ifndef Region_h
#define Region_h


#include <QRectF>

#include "Distance.h"


namespace glabels
{

	///
	/// Label Region Type
	///
	struct Region
	{

		/////////////////////////////////
		// Constructors
		/////////////////////////////////
	public:
		Region();
		Region( const Distance& x1, const Distance& y1,
		        const Distance& x2, const Distance& y2 );
	

		/////////////////////////////////
		// Properties
		/////////////////////////////////
	public:
		//
		// X1 Property
		//
		Distance x1( void ) const;
		void setX1( const Distance& value );


		//
		// Y1 Property
		//
		Distance y1( void ) const;
		void setY1( const Distance& value );


		//
		// X2 Property
		//
		Distance x2( void ) const;
		void setX2( const Distance& value );



		//
		// Y2 Property
		//
		Distance y2( void ) const;
		void setY2( const Distance& value );


		/////////////////////////////////
		// Methods
		/////////////////////////////////
	public:
		QRectF rect() const;


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		Distance mX1;
		Distance mY1;
		Distance mX2;
		Distance mY2;
	};

}


#endif // Region_h
