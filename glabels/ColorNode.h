/*  ColorNode.h
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

#ifndef glabels_ColorNode_h
#define glabels_ColorNode_h

#include <QString>
#include <QColor>
#include <stdint.h>


namespace glabels
{

	///
	/// Color Node Type
	///
	struct ColorNode
	{

		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		ColorNode();

		ColorNode( bool fieldFlag, const QColor& color, const QString& key );

		ColorNode( bool fieldFlag, uint32_t rgba, const QString& key );

		ColorNode( const QColor& color );

		ColorNode( const QString& key );


		/////////////////////////////////
		// Operators
		/////////////////////////////////
	public:
		bool operator==( const ColorNode& cn );

		bool operator!=( const ColorNode& cn );


		/////////////////////////////////
		// Properties
		/////////////////////////////////
	public:
		//
		// Field Flag Property
		//
		bool fieldFlag( void ) const;
		void setFieldFlag( bool fieldFlag );
		

		//
		// Color Property
		//
		const QColor& color( void ) const;
		void setColor( const QColor& color );


		//
		// Key Property
		//
		const QString& key( void ) const;
		void setKey( const QString& key );
		


		/////////////////////////////////
		// Methods
		/////////////////////////////////
	public:
		uint32_t rgba( void ) const;
		
#if TODO
		QColor expand( MergeRecord? record );
#endif


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		bool    mFieldFlag;
		QColor  mColor;
		QString mKey;

	};

}

#endif // glabels_ColorNode_h
