/*  LabelModelBoxObject.cpp
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

#include "LabelModelBoxObject.h"

#include <QBrush>
#include <QPen>


namespace glabels
{

	///
	/// Constructor
	///
	LabelModelBoxObject::LabelModelBoxObject( QObject* parent ) : LabelModelShapeObject(parent)
	{
	}


	///
	/// Destructor
	///
	LabelModelBoxObject::~LabelModelBoxObject()
	{
	}


	///
	/// Draw shadow of object
	///
	void LabelModelBoxObject::drawShadow( QPainter* painter, bool inEditor, MergeRecord* record ) const
	{
		/// TODO expand colors based on record
		
		QColor lineColor = mLineColorNode.color();
		QColor fillColor = mFillColorNode.color();
		QColor shadowColor = mShadowColorNode.color();

		shadowColor.setAlphaF( mShadowOpacity );

		if ( fillColor.alpha() )
		{
			painter->setPen( Qt::NoPen );
			painter->setBrush( shadowColor );

			if ( lineColor.alpha() )
			{
				/* Has FILL and OUTLINE: adjust size to account for line width. */
				painter->drawRect( -mLineWidth/2, -mLineWidth/2, mW+mLineWidth, mH+mLineWidth );
			}
			else
			{
				/* Has FILL, but no OUTLINE. */
				painter->drawRect( 0, 0, mW, mH );
			}
		}
		else
		{
			if ( lineColor.alpha() )
			{
				/* Has only OUTLINE. */
				painter->setPen( QPen( shadowColor, mLineWidth ) );
				painter->setBrush( Qt::NoBrush );

				painter->drawRect( 0, 0, mW, mH );
			}
		}
		
	}

	
	///
	/// Draw object itself
	///
	void LabelModelBoxObject::drawObject( QPainter* painter, bool inEditor, MergeRecord* record ) const
	{
		/// TODO expand colors based on record
		
		QColor lineColor = mLineColorNode.color();
		QColor fillColor = mFillColorNode.color();

		painter->setPen( QPen( lineColor, mLineWidth ) );
		painter->setBrush( fillColor );
		painter->drawRect( 0, 0, mW, mH );
	}


	///
	/// Path representing object
	///
	QPainterPath LabelModelBoxObject::path() const
	{
		QPainterPath path;
		path.addRect( 0, 0, mW, mH );

		return path;
	}
}
