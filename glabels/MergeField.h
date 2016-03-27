/*  MergeField.h
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

#ifndef MergeField_h
#define MergeField_h

#include <QString>


///
/// Merge Field Structure
///
struct MergeField
{

	/////////////////////////////////
	// Properties
	/////////////////////////////////
public:
	//
	// Key Property
	//
	inline const QString key( void ) const;
	inline void setKey( const QString &value );


	//
	// Value Property
	//
	inline const QString value( void ) const;
	inline void setValue( const QString &value );


	/////////////////////////////////
	// Private data
	/////////////////////////////////
private:
	QString mKey;
	QString mValue;

};


/////////////////////////////////
// INLINE METHODS
/////////////////////////////////
const QString MergeField::key( void ) const
{
	return mKey;
}


void MergeField::setKey( const QString &value )
{
	mKey = value;
}


const QString MergeField::value( void ) const
{
	return mValue;
}


void MergeField::setValue( const QString &value )
{
	mValue = value;
}


#endif // MergeField_h
