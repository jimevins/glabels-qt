/*  Merge/Merge.cpp
 *
 *  Copyright (C) 2015-2016  Jim Evins <evins@snaught.com>
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

#include "Record.h"


namespace glabels
{
	namespace merge
	{
	
		///
		/// Constructor
		///
		Merge::Merge( const Merge* merge ) : mId(merge->mId), mSource(merge->mSource)
		{
			foreach ( Record* record, merge->mRecordList )
			{
				mRecordList << record->clone();
			}
		}


		///
		/// Destructor
		///
		Merge::~Merge()
		{
			foreach ( Record* record, mRecordList )
			{
				delete record;
			}
			mRecordList.clear();
		}


		///
		/// Get id
		///
		QString Merge::id() const
		{
			return mId;
		}


		///
		/// Get source
		///
		QString Merge::source() const
		{
			return mSource;
		}


		///
		/// Set source
		///
		void Merge::setSource( const QString& source )
		{
			mSource = source;

			// Clear out any old records
			foreach ( Record* record, mRecordList )
			{
				delete record;
			}
			mRecordList.clear();

			open();
			for ( Record* record = readNextRecord(); record != nullptr; record = readNextRecord() )
			{
				mRecordList.append( record );
			}
			close();
		
			emit sourceChanged();
		}


		///
		/// Get record list
		///
		const QList<Record*>& Merge::recordList( ) const
		{
			return mRecordList;
		}


		///
		/// Select matching record
		///
		void Merge::select( Record* record )
		{
			record->setSelected( true );
			emit selectionChanged();
		}
	

		///
		/// Unselect matching record
		///
		void Merge::unselect( Record* record )
		{
			record->setSelected( false );
			emit selectionChanged();
		}

	
		///
		/// Select/unselect i'th record
		///
		void Merge::setSelected( int i, bool state )
		{
			if ( (i >= 0) && (i < mRecordList.size()) )
			{
				mRecordList[i]->setSelected( state );
				emit selectionChanged();
			}
		}


		///
		/// Select all records
		///
		void Merge::selectAll()
		{
			foreach ( Record* record, mRecordList )
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
			foreach ( Record* record, mRecordList )
			{
				record->setSelected( false );
			}
			emit selectionChanged();
		}

	
		///
		/// Return count of selected records
		///
		int Merge::nSelectedRecords() const
		{
			int count = 0;

			foreach ( Record* record, mRecordList )
			{
				if ( record->isSelected() )
				{
					count++;
				}
			}

			return count;
		}


		///
		/// Return list of selected records
		///
		const QList<Record*> Merge::selectedRecords() const
		{
			QList<Record*> list;

			foreach ( Record* record, mRecordList )
			{
				if ( record->isSelected() )
				{
					list.append( record );
				}
			}

			return list;
		}

	} // namespace merge
} // namespace glabels
