/*  TextNode.cpp
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

#include "TextNode.h"


namespace {
	typedef enum {
		START,
		LITERAL,
		LITERAL_DOLLAR,
		START_DOLLAR,
		FIELD,
		DONE
	} State;
}


namespace qtLabels
{

	TextNode::TextNode( const QString &text, int i_start, int &i_next )
	{
		State   state = START;
		QString literal_text;
		QString field_name;
		bool    field_flag = false;

		int i = i_start;

		while ( state != DONE )
		{
			QChar c = text[i];

			switch (state) {

			case START:
				switch (c.unicode()) {
				case '$':
					/* May be start of a field node. */
					i++;
					state = START_DOLLAR;
					break;
				case '\n':
					state = DONE;
					break;
				case 0:
					state = DONE;
					break;
				default:
					/* Start a literal text node. */
					literal_text.append( c );
					i++;
					state = LITERAL;
					break;
				}
				break;

			case LITERAL:
				switch (c.unicode()) {
				case '$':
					/* May be the beginning of a field node. */
					i++;
					state = LITERAL_DOLLAR;
					break;
				case '\n':
					state = DONE;
					break;
				case 0:
					state = DONE;
					break;
				default:
					literal_text.append( c );
					i++;
					state = LITERAL;
					break;
				}
				break;

			case LITERAL_DOLLAR:
				switch (c.unicode()) {
				case '{':
					/* "${" indicates the start of a new field node, gather for literal too. */
					literal_text.append( '$' );
					i++;
					state = DONE;
					break;
				case '\n':
					/* Append "$" to literal text, don't gather newline. */
					literal_text.append( '$' );
					i++;
					state = DONE;
					break;
				case 0:
					/* Append "$" to literal text, don't gather null. */
					literal_text.append( '$' );
					i++;
					state = DONE;
					break;
				default:
					/* Append "$" to literal text, gather this character too. */
					literal_text.append( '$' );
					literal_text.append( c );
					i+=2;
					state = LITERAL;
					break;
				}
				break;

			case START_DOLLAR:
				switch (c.unicode()) {
				case '{':
					/* This is probably the begining of a field node, gather for literal too. */
					literal_text.append( c );
					i++;
					state = FIELD;
					break;
				case '\n':
					state = DONE;
					break;
				case 0:
					state = DONE;
					break;
				default:
					/* The "$" was literal. */
					literal_text.append( c );
					i++;
					state = LITERAL;
					break;
				}
				break;

			case FIELD:
				switch (c.unicode()) {
				case '}':
					/* We now finally know that this node is really field node. */
					field_flag = true;
					i++;
					state = DONE;
					break;
				case '\n':
					state = DONE;
					break;
				case 0:
					state = DONE;
					break;
				default:
					/* Gather for field name and literal, just in case. */
					field_name.append( c );
					literal_text.append( c );
					i++;
					state = FIELD;
					break;
				}
				break;

			}

		}

		m_field_flag = field_flag;
		m_data       = field_flag ? field_name : literal_text;

		i_next = i;
	}


#if TODO
		public string expand( MergeRecord? record )
		{
			if ( field_flag )
			{

				if ( record == null )
				{
					return "${%s}".printf( data );
				}
				else
				{
					string? text = record.eval_key( data );
					if ( text != null )
					{
						return text;
					}
					else
					{
						return "";
					}
				}

			}
			else
			{
				return data;
			}
		}


		public bool is_empty_field( MergeRecord? record )
		{
			if ( (record !=null) && field_flag )
			{
				string? text = record.eval_key( data );
				return ( (text == null) || (text == "") );
			}
			else
			{
				return false;
			}
		}
#endif

}

