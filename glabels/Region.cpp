/*  Region.cpp
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

#include "Region.h"


///
/// Constructor
///
Region::Region() : mX1(0), mY1(0), mX2(0), mY2(0)
{
}


///
/// Constructor
///
Region::Region( const glabels::Distance& x1, const glabels::Distance& y1,
	        const glabels::Distance& x2, const glabels::Distance& y2 )
	: mX1(x1), mY1(y1), mX2(x2), mY2(y2)
{
}


///
/// Get x1
///
glabels::Distance Region::x1( void ) const
{
	return mX1;
}


///
/// Set x1
///
void Region::setX1( const glabels::Distance& value )
{
	mX1 = value;
}


///
/// Get y1
///
glabels::Distance Region::y1( void ) const
{
	return mY1;
}


///
/// Set y1
///
void Region::setY1( const glabels::Distance& value )
{
	mY1 = value;
}


///
/// Get x2
///
glabels::Distance Region::x2( void ) const
{
	return mX2;
}


///
/// Set x2
///
void Region::setX2( const glabels::Distance& value )
{
	mX2 = value;
}


///
/// Get y2
///
glabels::Distance Region::y2( void ) const
{
	return mY2;
}


///
/// Set y2
///
void Region::setY2( const glabels::Distance& value )
{
	mY2 = value;
}


///
/// Convert to a QRectF
///
QRectF Region::rect() const
{
	QRectF r;

	r.setX( min( mX1, mX2 ).pt() );
	r.setY( min( mY1, mY2 ).pt() );
	r.setWidth( fabs( mX2 - mX1 ).pt() );
	r.setHeight( fabs( mY2 - mY1 ).pt() );

	return r;
}
