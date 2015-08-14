/*  LabelModelBoxObject.h
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

#ifndef glabels_LabelModelBoxObject_h
#define glabels_LabelModelBoxObject_h


#include "LabelModelShapeObject.h"


namespace glabels
{

	///
	/// Label Model Box Object
	///
	class LabelModelBoxObject : public LabelModelShapeObject
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	public:
		LabelModelBoxObject( QObject* parent = 0 );
		virtual ~LabelModelBoxObject();


		///////////////////////////////////////////////////////////////
		// Drawing operations
		///////////////////////////////////////////////////////////////
	protected:
		virtual void drawShadow( QPainter* painter, bool inEditor, MergeRecord* record ) const;
		virtual void drawObject( QPainter* painter, bool inEditor, MergeRecord* record ) const;
		virtual QPainterPath path() const;

	};

}

#endif // glabels_LabelModelBoxObject_h
