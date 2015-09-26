/*  Merge.h
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

#ifndef glabels_Merge_h
#define glabels_Merge_h

#include <QObject>
#include <QString>
#include <QList>

#include "MergeRecord.h"


namespace glabels
{

	///
	/// Merge Record Structure
	///
	struct Merge : QObject
	{
		Q_OBJECT


		/////////////////////////////////
		// Source Type
		/////////////////////////////////
		enum SourceType { NONE, FIXED, FILE };
		
		
		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	protected:
		Merge( QString id, QString name, SourceType type );


		/////////////////////////////////
		// Properties
		/////////////////////////////////
	public:
		inline QString id() const;
		inline QString name() const;
		inline SourceType type() const;
		inline QString source() const;
		void setSource( const QString& source );

		inline const QList<MergeRecord*>& recordList( void ) const;


		/////////////////////////////////
		// Selection methods
		/////////////////////////////////
	public:
		void select( MergeRecord* record );
		void unselect( MergeRecord* record );
		void selectAll();
		void unselectAll();
		const QList<MergeRecord*> selectedRecords() const;


		/////////////////////////////////
		// Virtual methods
		/////////////////////////////////
	public:
		virtual QList<QString> keyList() const = 0;
		virtual QString primaryKey() const = 0;
	protected:
		virtual void open() = 0;
		virtual void close() = 0;
		virtual MergeRecord* readNextRecord() = 0;
		

		/////////////////////////////////
		// Signals
		/////////////////////////////////
	signals:
		void sourceChanged();
		void selectionChanged();
		

		/////////////////////////////////
		// Private data
		/////////////////////////////////
	private:
		QString             mId;
		QString             mName;
		SourceType          mType;

		QString             mSource;
		bool                mSelected;
		QList<MergeRecord*> mRecordList;
	};


	/////////////////////////////////
	// INLINE METHODS
	/////////////////////////////////
	QString Merge::id() const
	{
		return mId;
	}


	QString Merge::name() const
	{
		return mId;
	}


	Merge::SourceType Merge::type() const
	{
		return mType;
	}


	QString Merge::source() const
	{
		return mSource;
	}


	const QList<MergeRecord*>& Merge::recordList( void ) const
	{
		return mRecordList;
	}

}

#endif // glabels_Merge_h
