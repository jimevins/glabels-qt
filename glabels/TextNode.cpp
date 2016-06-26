/*  TextNode.cpp
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


///
/// Default Constructor
///
TextNode::TextNode()
	: mIsField(false), mData("")
{
}


///
/// Constructor from Data
///
TextNode::TextNode( bool isField, const QString &data )
	: mIsField(isField), mData(data)
{
}


///
/// Constructor from Parsing Next Token in Text
///
TextNode::TextNode( const QString &text, int iStart, int &iNext )
{
	State   state = START;
	QString literalText;
	QString fieldName;
	bool    isField = false;

	int i = iStart;

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
				literalText.append( c );
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
				literalText.append( c );
				i++;
				state = LITERAL;
				break;
			}
			break;

		case LITERAL_DOLLAR:
			switch (c.unicode()) {
			case '{':
				/* "${" indicates the start of a new field node, gather for literal too. */
				literalText.append( '$' );
				i++;
				state = DONE;
				break;
			case '\n':
				/* Append "$" to literal text, don't gather newline. */
				literalText.append( '$' );
				i++;
				state = DONE;
				break;
			case 0:
				/* Append "$" to literal text, don't gather null. */
				literalText.append( '$' );
				i++;
				state = DONE;
				break;
			default:
				/* Append "$" to literal text, gather this character too. */
				literalText.append( '$' );
				literalText.append( c );
				i+=2;
				state = LITERAL;
				break;
			}
			break;

		case START_DOLLAR:
			switch (c.unicode()) {
			case '{':
				/* This is probably the begining of a field node, gather for literal too. */
				literalText.append( c );
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
				literalText.append( c );
				i++;
				state = LITERAL;
				break;
			}
			break;

		case FIELD:
			switch (c.unicode()) {
			case '}':
				/* We now finally know that this node is really field node. */
				isField = true;
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
				fieldName.append( c );
				literalText.append( c );
				i++;
				state = FIELD;
				break;
			}
			break;

		}

	}

	mIsField = isField;
	mData    = isField ? fieldName : literalText;

	iNext = i;
}


///
/// == Operator
///
bool TextNode::operator==( const TextNode& other )
{
	return ( (mIsField == other.mIsField) &&
		 (mData    == other.mData) );
}


///
/// != Operator
///
bool TextNode::operator!=( const TextNode& other )
{
	return ( (mIsField != other.mIsField) ||
		 (mData    != other.mData) );
}


///
/// isField? Property Getter
///
bool TextNode::isField( void ) const
{
	return mIsField;
}


///
/// Data Property Getter
///
const QString& TextNode::data( void ) const
{
	return mData;
}


///
/// Get text, expand if necessary
///
QString TextNode::text( merge::Record* record ) const
{
	if ( mIsField )
	{
		if ( !record )
		{
			return QString("${%1}").arg( mData );
		}
		else
		{
			if ( record->contains( mData ) )
			{
				return (*record)[ mData ];
			}
			else
			{
				return "";
			}
		}
	}
	else
	{
		return mData;
	}
}


///
/// Is it an empty field
///
bool TextNode::isEmptyField( merge::Record* record ) const
{
	if ( record && mIsField )
	{
		if ( record->contains( mData ) )
		{
			return ( (*record)[mData].isEmpty() );
		}
	}

	return false;
}
