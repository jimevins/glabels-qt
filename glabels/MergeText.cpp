/*  MergeText.cpp
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

#include "MergeText.h"


///
/// Constructor
///
MergeText::MergeText( QChar delimiter, bool line1HasKeys ) : Merge( Merge::FILE )
{
}


///
/// Constructor
///
MergeText::MergeText( const MergeText* merge )
	: Merge( merge ), mDelimeter(merge->mDelimeter), mLine1HasKeys(merge->mLine1HasKeys)
{
}


///
/// Destructor
///
MergeText::~MergeText()
{
}


///
/// Get key list
///
QList<QString> MergeText::keyList() const
{
	QList<QString> emptyList;
	return emptyList;
}


///
/// Get primary key
///
QString MergeText::primaryKey() const
{
	return "";
}


///
/// Open source
///
void MergeText::open()
{
	mFile.setFileName( source() );
	mFile.open( QIODevice::ReadOnly|QIODevice::Text );

	if ( mLine1HasKeys && mFile.isOpen() )
	{
		// Todo parse line #1, create key list from string list
	}
}


///
/// Close source
///
void MergeText::close()
{
	if ( mFile.isOpen() )
	{
		mFile.close();
	}
}


///
/// Read next record
///
MergeRecord* MergeText::readNextRecord()
{
	return 0;
}
