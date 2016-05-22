/*  MergeText.h
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

#ifndef MergeText_h
#define MergeText_h

#include "Merge.h"

#include <QFile>


///
/// MergeText Backend
///
struct MergeText : public Merge
{

	/////////////////////////////////
	// Life Cycle
	/////////////////////////////////
protected:
	MergeText( QChar delimiter, bool line1HasKeys );
	MergeText( const MergeText* merge );
	virtual ~MergeText();


	/////////////////////////////////
	// Implementation of virtual methods
	/////////////////////////////////
public:
	QStringList keys() const;
	QString primaryKey() const;
protected:
	void open();
	void close();
	MergeRecord* readNextRecord();


	/////////////////////////////////
	// Private methods
	/////////////////////////////////
	QString keyFromIndex( int iField ) const;
	QStringList parseLine();
	

	/////////////////////////////////
	// Private data
	/////////////////////////////////
private:
	QChar mDelimeter;
	bool  mLine1HasKeys;

	QFile          mFile;
	QStringList    mKeys;
	int            mNFieldsMax;
};


#endif // MergeText_h
