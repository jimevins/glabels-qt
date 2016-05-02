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

#ifndef Merge_h
#define Merge_h

#include <QObject>
#include <QString>
#include <QList>

#include "MergeRecord.h"


///
/// Merge Object
///
struct Merge : QObject
{
	Q_OBJECT


	/////////////////////////////////
	// Source Type
	/////////////////////////////////
public:
	enum SourceType { NONE, FIXED, FILE };
		
		
	/////////////////////////////////
	// Life Cycle
	/////////////////////////////////
protected:
	Merge( SourceType type );
	Merge( const Merge* merge );
	virtual ~Merge();


	/////////////////////////////////
	// Object duplication
	/////////////////////////////////
	virtual Merge* clone() const = 0;


	/////////////////////////////////
	// Properties
	/////////////////////////////////
public:
	SourceType type() const;
	QString source() const;
	void setSource( const QString& source );

	const QList<MergeRecord*>& recordList( void ) const;


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
	SourceType          mType;

	QString             mSource;
	QList<MergeRecord*> mRecordList;
};


#endif // Merge_h
