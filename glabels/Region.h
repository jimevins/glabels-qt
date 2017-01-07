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

#include "libglabels/Distance.h"


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
	Region( const glabels::Distance& x1, const glabels::Distance& y1,
	        const glabels::Distance& x2, const glabels::Distance& y2 );
	

	/////////////////////////////////
	// Properties
	/////////////////////////////////
public:
	//
	// X1 Property
	//
	glabels::Distance x1( void ) const;
	void setX1( const glabels::Distance& value );


	//
	// Y1 Property
	//
	glabels::Distance y1( void ) const;
	void setY1( const glabels::Distance& value );


	//
	// X2 Property
	//
	glabels::Distance x2( void ) const;
	void setX2( const glabels::Distance& value );



	//
	// Y2 Property
	//
	glabels::Distance y2( void ) const;
	void setY2( const glabels::Distance& value );


	/////////////////////////////////
	// Methods
	/////////////////////////////////
public:
	QRectF rect() const;


	/////////////////////////////////
	// Private Data
	/////////////////////////////////
private:
	glabels::Distance mX1;
	glabels::Distance mY1;
	glabels::Distance mX2;
	glabels::Distance mY2;
};


#endif // Region_h
