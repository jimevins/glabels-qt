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
	LabelModelBoxObject::LabelModelBoxObject( QObject* parent ) : LabelModelObject(parent)
	{
		/* TODO: initialize default line and fill poperties.  */
	}


	///
	/// Destructor
	///
	LabelModelBoxObject::~LabelModelBoxObject()
	{
	}


	///
	/// Line Width Property Getter
	///
	double LabelModelBoxObject::lineWidth( void ) const
	{
		return mLineWidth;
	}


	///
	/// Line Width Property Setter
	///
	void LabelModelBoxObject::setLineWidth( double value )
	{
		if ( mLineWidth != value )
		{
			mLineWidth = value;
			emit changed();
		}
	}


	///
	/// Line Color Node Property Getter
	///
	ColorNode LabelModelBoxObject::lineColorNode( void ) const
	{
		return mLineColorNode;
	}


	///
	/// Line Color Node Property Setter
	///
	void LabelModelBoxObject::setLineColorNode( const ColorNode& value )
	{
		if ( mLineColorNode != value )
		{
			mLineColorNode = value;
			emit changed();
		}
	}
		

	///
	/// Fill Color Node Property Getter
	///
	ColorNode LabelModelBoxObject::fillColorNode( void ) const
	{
		return mFillColorNode;
	}


	///
	/// Fill Color Node Property Setter
	///
	void LabelModelBoxObject::setFillColorNode( const ColorNode& value )
	{
		if ( mFillColorNode != value )
		{
			mFillColorNode = value;
			emit changed();
		}
	}
		

	///
	/// Can Fill Capability Implementation
	///
	bool LabelModelBoxObject::canFill()
	{
		return true;
	}


	///
	/// Can Line Color Capability Implementation
	///
	bool LabelModelBoxObject::canLineColor()
	{
		return true;
	}


	///
	/// Can Line Width Capability Implementation
	///
	bool LabelModelBoxObject::canLineWidth()
	{
		return true;
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

}
