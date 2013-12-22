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


namespace glabels
{

	class ColorNode
	{

	public:
		ColorNode();

		ColorNode( bool fieldFlag, const QColor& color, const QString& key );

		ColorNode( const QColor& color );

		ColorNode( const QString& key );

		bool operator==( const ColorNode& cn );

		bool operator!=( const ColorNode& cn );

#if TODO
		QColor expand( MergeRecord? record );
#endif


		// field flag property
		bool fieldFlag( void ) const;
		

		// color property
		const QColor& color( void ) const;
		

		// key property
		const QString& key( void ) const;
		

	private:
		bool    mFieldFlag;
		QColor  mColor;
		QString mKey;

	};

}

#endif // glabels_ColorNode_h
