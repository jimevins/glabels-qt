/*  Merge.cpp
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

#include "Merge.h"


namespace glabels
{

	///
	/// Constructor
	///
	Merge::Merge( QString id, QString name, SourceType type )
		: mId(id), mName(name), mType(type)
	{
	}


	///
	/// Destructor
	///
	Merge::~Merge()
	{
	}


	///
	/// Set source
	///
	void Merge::setSource( const QString& source )
	{
		mSource = source;

		// Clear out any old records
		foreach ( MergeRecord* record, mRecordList )
		{
			delete record;
		}
		mRecordList.clear();

		open();
		for ( MergeRecord* record = readNextRecord(); record != 0; record = readNextRecord() )
		{
			mRecordList.append( record );
		}
		close();
		
		emit sourceChanged();
	}


	///
	/// Select matching record
	///
	void Merge::select( MergeRecord* record )
	{
		record->setSelected( true );
		emit selectionChanged();
	}
	

	///
	/// Unselect matching record
	///
	void Merge::unselect( MergeRecord* record )
	{
		record->setSelected( false );
		emit selectionChanged();
	}

	
	///
	/// Select all records
	///
	void Merge::selectAll()
	{
		foreach ( MergeRecord* record, mRecordList )
		{
			record->setSelected( true );
		}
		emit selectionChanged();
	}

	
	///
	/// Unselect all records
	///
	void Merge::unselectAll()
	{
		foreach ( MergeRecord* record, mRecordList )
		{
			record->setSelected( false );
		}
		emit selectionChanged();
	}

	
	///
	/// Return list of selected records
	///
	const QList<MergeRecord*> Merge::selectedRecords() const
	{
		QList<MergeRecord*> list;

		foreach ( MergeRecord* record, mRecordList )
		{
			if ( record->isSelected() )
			{
				list.append( record );
			}
		}

		return list;
	}

}


