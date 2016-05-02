/*  MergeNone.cpp
 *
 *  Copyright (C) 2015  Jim Evins <evins@snaught.com>
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

#include "MergeNone.h"


///
/// Constructor
///
MergeNone::MergeNone() : Merge( Merge::NONE )
{
}


///
/// Constructor
///
MergeNone::MergeNone( const MergeNone* merge ) : Merge( merge )
{
}


///
/// Destructor
///
MergeNone::~MergeNone()
{
}


///
/// Clone
///
MergeNone* MergeNone::clone() const
{
	return new MergeNone( this );
}


///
/// Get key list
///
QList<QString> MergeNone::keyList() const
{
	QList<QString> emptyList;
	return emptyList;
}


///
/// Get primary key
///
QString MergeNone::primaryKey() const
{
	return "";
}


///
/// Open source
///
void MergeNone::open()
{
}


///
/// Close source
///
void MergeNone::close()
{
}


///
/// Read next record
///
MergeRecord* MergeNone::readNextRecord()
{
	return 0;
}
