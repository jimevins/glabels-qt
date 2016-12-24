/*  LabelRegion.cpp
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

#include "LabelRegion.h"


///
/// Get x1
///
glabels::Distance LabelRegion::x1( void ) const
{
	return mX1;
}


///
/// Set x1
///
void LabelRegion::setX1( const glabels::Distance& value )
{
	mX1 = value;
}


///
/// Get y1
///
glabels::Distance LabelRegion::y1( void ) const
{
	return mY1;
}


///
/// Set y1
///
void LabelRegion::setY1( const glabels::Distance& value )
{
	mY1 = value;
}


///
/// Get x2
///
glabels::Distance LabelRegion::x2( void ) const
{
	return mX2;
}


///
/// Set x2
///
void LabelRegion::setX2( const glabels::Distance& value )
{
	mX2 = value;
}


///
/// Get y2
///
glabels::Distance LabelRegion::y2( void ) const
{
	return mY2;
}


///
/// Set y2
///
void LabelRegion::setY2( const glabels::Distance& value )
{
	mY2 = value;
}


///
/// Convert to a QRectF
///
QRectF LabelRegion::rect() const
{
	QRectF r;

	r.setX( min( mX1, mX2 ).pt() );
	r.setY( min( mY1, mY2 ).pt() );
	r.setWidth( fabs( mX2 - mX1 ).pt() );
	r.setHeight( fabs( mY2 - mY1 ).pt() );

	return r;
}
