/*  LabelModelEllipseObject.h
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
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

#ifndef LabelModelEllipseObject_h
#define LabelModelEllipseObject_h


#include "LabelModelShapeObject.h"


namespace glabels
{

	///
	/// Label Model Ellipse Object
	///
	class LabelModelEllipseObject : public LabelModelShapeObject
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	public:
		LabelModelEllipseObject();
		LabelModelEllipseObject( const LabelModelEllipseObject* object );
		~LabelModelEllipseObject() override;

	
		///////////////////////////////////////////////////////////////
		// Object duplication
		///////////////////////////////////////////////////////////////
		LabelModelEllipseObject* clone() const override;


		///////////////////////////////////////////////////////////////
		// Drawing operations
		///////////////////////////////////////////////////////////////
	protected:
		void drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const override;
		void drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const override;
		QPainterPath hoverPath( double scale ) const override;

	};

}


#endif // LabelModelEllipseObject_h
