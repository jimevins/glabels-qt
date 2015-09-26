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

#ifndef glabels_MergeRecord_h
#define glabels_MergeRecord_h

#include <QString>
#include <QList>

#include "MergeField.h"


namespace glabels
{

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


		/////////////////////////////////
		// Properties
		/////////////////////////////////
	public:
		inline bool isSelected() const;
		inline void setSelected( bool value );
		inline bool empty() const;

		inline const QList<MergeField>& fieldList() const;
		inline void setFieldList( QList<MergeField>& value );


		/////////////////////////////////
		// Private data
		/////////////////////////////////
	private:
		bool              mSelected;
		QList<MergeField> mFieldList;
	};


	/////////////////////////////////
	// INLINE METHODS
	/////////////////////////////////
	bool MergeRecord::isSelected() const
	{
		return mSelected;
	}


	void MergeRecord::setSelected( bool value )
	{
		mSelected = value;
	}


	bool MergeRecord::empty() const
	{
		return mFieldList.size() == 0;
	}


	const QList<MergeField>& MergeRecord::fieldList() const
	{
		return mFieldList;
	}


	void MergeRecord::setFieldList( QList<MergeField>& value )
	{
		mFieldList = value;
	}

}

#endif // glabels_MergeRecord_h
