/*  MergeTextCsv.cpp
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

#include "MergeTextCsv.h"


///
/// Constructor
///
MergeTextCsv::MergeTextCsv() : MergeText(',',false)
{
	mId = "Text/CSV";
}


///
/// Constructor
///
MergeTextCsv::MergeTextCsv( const MergeTextCsv* merge )	: MergeText( merge )
{
}


///
/// Destructor
///
MergeTextCsv::~MergeTextCsv()
{
}


///
/// Clone
///
MergeTextCsv* MergeTextCsv::clone() const
{
	return new MergeTextCsv( this );
}


///
/// Get ID
///
QString MergeTextCsv::id()
{
	return "Text/CSV";
}


///
/// Create
///
Merge* MergeTextCsv::create()
{
	return new MergeTextCsv();
}
