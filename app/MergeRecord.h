/*  MergeRecord.h
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
 *
 *  This file is part of qtLabels.
 *
 *  qtLabels is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  qtLabels is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with qtLabels.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef qtlabels_MergeRecord_h
#define qtlabels_MergeRecord_h

#include <QString>
#include <list>

#include "MergeField.h"

using namespace std;


namespace qtLabels
{

	struct MergeRecord
	{
	public:
		MergeRecord() : m_selected( false )
		{
		}


	public:
		inline bool selected( void ) { return m_selected; }
		inline void selected( bool value ) { m_selected = value; }

		inline list<MergeField> field_list( void ) { return m_field_list; }
		inline void field_list( list<MergeField> &value ) { m_field_list = value; }


	private:
		bool             m_selected;
		list<MergeField> m_field_list;
	};

}

#endif // qtlabels_MergeRecord_h
