/*  MergeRecord.h
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

#ifndef MergeRecord_h
#define MergeRecord_h

#include <QString>
#include <QList>

#include "MergeField.h"


///
/// Merge Record Structure
///
struct MergeRecord
{
	/////////////////////////////////
	// Life Cycle
	/////////////////////////////////
public:
	MergeRecord();
	MergeRecord( const MergeRecord* record );


	/////////////////////////////////
	// Object duplication
	/////////////////////////////////
	MergeRecord* clone() const;


	/////////////////////////////////
	// Properties
	/////////////////////////////////
public:
	bool isSelected() const;
	void setSelected( bool value );
	bool isEmpty() const;

	const QList<MergeField>& fieldList() const;
	void setFieldList( QList<MergeField>& value );


	/////////////////////////////////
	// Private data
	/////////////////////////////////
private:
	bool              mSelected;
	QList<MergeField> mFieldList;
};


#endif // MergeRecord_h
