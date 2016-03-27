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

#ifndef TextNode_h
#define TextNode_h

#include <QString>


///
/// Text Node Type
///
struct TextNode
{

	/////////////////////////////////
	// Life Cycle
	/////////////////////////////////
public:
	TextNode();

	TextNode( bool field_flag, const QString &data );

	TextNode( const QString &text, int i_start, int &i_next );


	/////////////////////////////////
	// Operators
	/////////////////////////////////
public:
	bool operator==( const TextNode& other );

	bool operator!=( const TextNode& other );


	/////////////////////////////////
	// Properties
	/////////////////////////////////
public:
	//
	// Field Flag Property
	//
	bool fieldFlag( void ) const;

	//
	// Data Property
	//
	const QString& data( void ) const;



	/////////////////////////////////
	// Methods
	/////////////////////////////////
#if TODO
	string expand( MergeRecord? record );
	bool is_empty_field( MergeRecord? record );
#endif


	/////////////////////////////////
	// Private Data
	/////////////////////////////////
private:

	bool    mFieldFlag;
	QString mData;

};


#endif // TextNode_h
