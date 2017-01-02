/*  Size.cpp
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

#include "Size.h"


///
/// Constructor
///
Size::Size() : mW(0), mH(0)
{
}


///
/// Constructor
///
Size::Size( const glabels::Distance& w, const glabels::Distance& h ) : mW(w), mH(h)
{
}


///
/// Get w
///
glabels::Distance Size::w( void ) const
{
	return mW;
}


///
/// Set w
///
void Size::setW( const glabels::Distance& value )
{
	mW = value;
}


///
/// Get h
///
glabels::Distance Size::h( void ) const
{
	return mH;
}


///
/// Set h
///
void Size::setH( const glabels::Distance& value )
{
	mH = value;
}


///
/// Convert to a QSizeF
///
QSizeF Size::qSizeF() const
{
	QSizeF s;

	s.setWidth( mW.pt() );
	s.setHeight( mH.pt() );

	return s;
}
