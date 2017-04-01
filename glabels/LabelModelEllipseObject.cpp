/*  LabelModelEllipseObject.cpp
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

#include "LabelModelEllipseObject.h"

#include <QBrush>
#include <QPen>


namespace glabels
{

	//
	// Private
	//
	namespace
	{
		const double slopPixels = 2;
	}


	///
	/// Constructor
	///
	LabelModelEllipseObject::LabelModelEllipseObject()
	{
		// empty
	}


	///
	/// Copy constructor
	///
	LabelModelEllipseObject::LabelModelEllipseObject( const LabelModelEllipseObject* object )
		: LabelModelShapeObject( object )
	{
		// empty
	}


	///
	/// Destructor
	///
	LabelModelEllipseObject::~LabelModelEllipseObject()
	{
		// empty
	}


	///
	/// Clone
	///
	LabelModelEllipseObject* LabelModelEllipseObject::clone() const
	{
		return new LabelModelEllipseObject( this );
	}


	///
	/// Draw shadow of object
	///
	void LabelModelEllipseObject::drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const
	{
		QColor lineColor = mLineColorNode.color( record );
		QColor fillColor = mFillColorNode.color( record );
		QColor shadowColor = mShadowColorNode.color( record );

		shadowColor.setAlphaF( mShadowOpacity );

		if ( fillColor.alpha() )
		{
			painter->setPen( Qt::NoPen );
			painter->setBrush( shadowColor );

			if ( lineColor.alpha() )
			{
				/* Has FILL and OUTLINE: adjust size to account for line width. */
				painter->drawEllipse( QRectF( -mLineWidth.pt()/2,
				                              -mLineWidth.pt()/2,
				                              (mW + mLineWidth).pt(),
				                              (mH + mLineWidth).pt() ) );
			}
			else
			{
				/* Has FILL, but no OUTLINE. */
				painter->drawEllipse( QRectF( 0, 0, mW.pt(), mH.pt() ) );
			}
		}
		else
		{
			if ( lineColor.alpha() )
			{
				/* Has only OUTLINE. */
				painter->setPen( QPen( shadowColor, mLineWidth.pt() ) );
				painter->setBrush( Qt::NoBrush );

				painter->drawEllipse( QRectF( 0, 0, mW.pt(), mH.pt() ) );
			}
		}
		
	}

	
	///
	/// Draw object itself
	///
	void LabelModelEllipseObject::drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const
	{
		QColor lineColor = mLineColorNode.color( record );
		QColor fillColor = mFillColorNode.color( record );

		painter->setPen( QPen( lineColor, mLineWidth.pt() ) );
		painter->setBrush( fillColor );

		painter->drawEllipse( QRectF( 0, 0, mW.pt(), mH.pt() ) );
	}


	///
	/// Path to test for hover condition
	///
	QPainterPath LabelModelEllipseObject::hoverPath( double scale ) const
	{
		double s = 1 / scale;

		QPainterPath path;

		if ( mFillColorNode.color().alpha() && mLineColorNode.color().alpha() )
		{
			path.addEllipse( -mLineWidth.pt()/2, -mLineWidth.pt()/2, (mW+mLineWidth).pt(), (mH+mLineWidth).pt() );
		}
		else if ( mFillColorNode.color().alpha() && !(mLineColorNode.color().alpha()) )
		{
			path.addEllipse( 0, 0, mW.pt(), mH.pt() );
		}
		else if ( mLineColorNode.color().alpha() )
		{
			path.addEllipse( (-mLineWidth.pt()/2) - s*slopPixels,
			                 (-mLineWidth.pt()/2) - s*slopPixels,
			                 (mW + mLineWidth).pt() + s*2*slopPixels,
			                 (mH + mLineWidth).pt() + s*2*slopPixels );
			path.closeSubpath();
			path.addEllipse( mLineWidth.pt()/2 + s*slopPixels,
			                 mLineWidth.pt()/2 + s*slopPixels,
			                 (mW - mLineWidth).pt() - s*2*slopPixels,
			                 (mH - mLineWidth).pt() - s*2*slopPixels );
		}

		return path;
	}

} // namespace glabels
