/*  LabelModelLineObject.cpp
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

#include "LabelModelLineObject.h"

#include <QBrush>
#include <QPen>


namespace
{
	const double slopPixels = 2;
}


///
/// Constructor
///
LabelModelLineObject::LabelModelLineObject()
{
	mOutline = 0;

	mHandles << new HandleP1( this );
	mHandles << new HandleP2( this );

	mLineWidth       = 1.0;
	mLineColorNode   = ColorNode( QColor( 0, 0, 0 ) );
}


///
/// Copy constructor
///
LabelModelLineObject::LabelModelLineObject( const LabelModelLineObject* object ) : LabelModelObject(object)
{
	mLineWidth       = object->mLineWidth;
	mLineColorNode   = object->mLineColorNode;
}


///
/// Destructor
///
LabelModelLineObject::~LabelModelLineObject()
{
	foreach( Handle* handle, mHandles )
	{
		delete handle;
	}
	mHandles.clear();
}


///
/// Clone
///
LabelModelLineObject* LabelModelLineObject::clone() const
{
	return new LabelModelLineObject( this );
}


///
/// Line Width Property Getter
///
glabels::Distance LabelModelLineObject::lineWidth( void ) const
{
	return mLineWidth;
}


///
/// Line Width Property Setter
///
void LabelModelLineObject::setLineWidth( const glabels::Distance& value )
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
ColorNode LabelModelLineObject::lineColorNode( void ) const
{
	return mLineColorNode;
}


///
/// Line Color Node Property Setter
///
void LabelModelLineObject::setLineColorNode( const ColorNode& value )
{
	if ( mLineColorNode != value )
	{
		mLineColorNode = value;
		emit changed();
	}
}
		

///
/// Can Line Color Capability Implementation
///
bool LabelModelLineObject::canLineColor()
{
	return true;
}


///
/// Can Line Width Capability Implementation
///
bool LabelModelLineObject::canLineWidth()
{
	return true;
}


///
/// Draw shadow of object
///
void LabelModelLineObject::drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const
{
	QColor lineColor = mLineColorNode.color( record );
	QColor shadowColor = mShadowColorNode.color( record );

	shadowColor.setAlphaF( mShadowOpacity );

	if ( lineColor.alpha() )
	{
		painter->setPen( QPen( shadowColor, mLineWidth.pt() ) );
		painter->drawLine( 0, 0, mW.pt(), mH.pt() );
	}
}

	
///
/// Draw object itself
///
void LabelModelLineObject::drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const
{
	QColor lineColor = mLineColorNode.color( record );

	painter->setPen( QPen( lineColor, mLineWidth.pt() ) );
	painter->drawLine( 0, 0, mW.pt(), mH.pt() );
}


///
/// Path to test for hover condition
///
QPainterPath LabelModelLineObject::hoverPath( double scale ) const
{
	QPainterPath path;

	if ( mLineColorNode.color().alpha() )
	{
		//
		// Build a thin rectangle representing line
		//
		double rPts = mLineWidth.pt()/2 + slopPixels / scale;

		double lengthPts = sqrt( mW.pt()*mW.pt() + mH.pt()*mH.pt() );
		double dx = mH.pt() / lengthPts; // horizontal pitch of perpendicular line
		double dy = mW.pt() / lengthPts; // vertical pitch of perpendicular line
	
		path.moveTo(           rPts*dx,         - rPts*dy );
		path.lineTo( mW.pt() + rPts*dx, mH.pt() - rPts*dy );
		path.lineTo( mW.pt() - rPts*dx, mH.pt() + rPts*dy );
		path.lineTo(         - rPts*dx,           rPts*dy );
		
		path.closeSubpath();
	}

	return path;
}
