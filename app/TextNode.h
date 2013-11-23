/*  TextNode.h
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

#ifndef glabels_TextNode_h
#define glabels_TextNode_h

#include <QString>


namespace glabels
{

	class TextNode
	{

	public:
		TextNode()
			: m_field_flag(false), m_data("")
		{
		}


		TextNode( bool field_flag, const QString &data )
			: m_field_flag(field_flag), m_data(data)
		{
		}

		virtual ~TextNode() {}


		TextNode( const QString &text, int i_start, int &i_next );


		bool operator==( const TextNode &tn )
		{
			return ( (m_field_flag == tn.m_field_flag) &&
				 (m_data       == tn.m_data) );
		}


		bool operator!=( const TextNode &tn )
		{
			return ( (m_field_flag != tn.m_field_flag) ||
				 (m_data       != tn.m_data) );
		}


#if TODO
		string expand( MergeRecord? record );
		bool is_empty_field( MergeRecord? record );
#endif

		bool field_flag( void ) { return m_field_flag; }
		QString data( void ) { return m_data; }

	private:

		bool    m_field_flag;
		QString m_data;

	};

}

#endif // glabels_TextNode_h
