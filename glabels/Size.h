/*  Size.h
 *
 *  Copyright (C) 2017  Jim Evins <evins@snaught.com>
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

#ifndef Size_h
#define Size_h

#include <QSizeF>
#include "libglabels/Distance.h"


///
/// Size Type
///
class Size
{

	/////////////////////////////////
	// Constructors
	/////////////////////////////////
public:
	Size();
	Size( const glabels::Distance& w, const glabels::Distance& h );
	

	/////////////////////////////////
	// Properties
	/////////////////////////////////
public:
	//
	// w Property
	//
	glabels::Distance w( void ) const;
	void setW( const glabels::Distance& value );


	//
	// H Property
	//
	glabels::Distance h( void ) const;
	void setH( const glabels::Distance& value );


	/////////////////////////////////
	// Methods
	/////////////////////////////////
public:
	QSizeF qSizeF() const;


	/////////////////////////////////
	// Private Data
	/////////////////////////////////
private:
	glabels::Distance mW;
	glabels::Distance mH;

};


#endif // Size_h
