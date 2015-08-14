/*  Handles.cpp
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

#include "Handles.h"


#include "LabelModelObject.h"

#include <QColor>


namespace
{
	const double handlePixels             = 7;
	const double handleOutlineWidthPixels = 1;

	const QColor handleFillColor( 0,  192,  0,  96 );
	const QColor handleOutlineColor( 0,  0,   0,  192 );
}


///
/// Handle Constructor
///
glabels::Handle::Handle( LabelModelObject* owner )
	: mOwner(owner)
{
}


///
/// Handle Destructor
///
glabels::Handle::~Handle()
{
}


///
/// Draw Handle at x,y
///
void glabels::Handle::drawAt( QPainter* painter, double x, double y ) const
{
	painter->save();

	painter->translate( x, y );

	/* Render at a scale of 1:1 in pixels, while preserving translations and rotations. */
	QTransform t = painter->transform();
	painter->setTransform( QTransform( 1,       t.m12(), t.m13(),
					   t.m21(), 1,       t.m23(),
					   t.m31(), t.m32(), t.m33() ) );

	painter->setPen( QPen( handleOutlineColor, handleOutlineWidthPixels ) );
	painter->setBrush( handleFillColor );

	painter->drawRect( -handlePixels/2, -handlePixels/2, handlePixels, handlePixels );

	painter->restore();
}


///
/// Create Handle path at x,y
///
QPainterPath glabels::Handle::pathAt( double scale, double x, double y ) const
{
	QPainterPath path;

	double s = 1/scale;

	path.addRect( -s*handlePixels/2, -s*handlePixels/2, s*handlePixels, s*handlePixels );
	path.translate( x, y );
	
	return path;
}


///
/// HandleNorth Constructor
///
glabels::HandleNorth::HandleNorth( LabelModelObject* owner )
	: Handle(owner)
{
}


///
/// HandleNorth Destructor
///
glabels::HandleNorth::~HandleNorth()
{
}


///
/// Draw HandleNorth
///
void glabels::HandleNorth::draw( QPainter* painter ) const
{
	drawAt( painter, mOwner->w()/2, 0 );
}


///
/// HandleNorth Path
///
QPainterPath glabels::HandleNorth::path( double scale ) const
{
	return pathAt( scale, mOwner->w()/2, 0 );
}


///
/// HandleNorthEast Constructor
///
glabels::HandleNorthEast::HandleNorthEast( LabelModelObject* owner )
	: Handle(owner)
{
}


///
/// HandleNorthEast Destructor
///
glabels::HandleNorthEast::~HandleNorthEast()
{
}


///
/// Draw HandleNorthEast
///
void glabels::HandleNorthEast::draw( QPainter* painter ) const
{
	drawAt( painter, mOwner->w(), 0 );
}


///
/// HandleNorthEast Path
///
QPainterPath glabels::HandleNorthEast::path( double scale ) const
{
	return pathAt( scale, mOwner->w(), 0 );
}


///
/// HandleEast Constructor
///
glabels::HandleEast::HandleEast( LabelModelObject* owner )
	: Handle(owner)
{
}


///
/// HandleEast Destructor
///
glabels::HandleEast::~HandleEast()
{
}


///
/// Draw HandleEast
///
void glabels::HandleEast::draw( QPainter* painter ) const
{
	drawAt( painter, mOwner->w(), mOwner->h()/2 );
}


///
/// HandleEast Path
///
QPainterPath glabels::HandleEast::path( double scale ) const
{
	return pathAt( scale, mOwner->w(), mOwner->h()/2 );
}


///
/// HandleSouthEast Constructor
///
glabels::HandleSouthEast::HandleSouthEast( LabelModelObject* owner )
	: Handle(owner)
{
}


///
/// HandleSouthEast Destructor
///
glabels::HandleSouthEast::~HandleSouthEast()
{
}


///
/// Draw HandleSouthEast
///
void glabels::HandleSouthEast::draw( QPainter* painter ) const
{
	drawAt( painter, mOwner->w(), mOwner->h() );
}


///
/// HandleSouthEast Path
///
QPainterPath glabels::HandleSouthEast::path( double scale ) const
{
	return pathAt( scale, mOwner->w(), mOwner->h() );
}


///
/// HandleSouth Constructor
///
glabels::HandleSouth::HandleSouth( LabelModelObject* owner )
	: Handle(owner)
{
}


///
/// HandleSouth Destructor
///
glabels::HandleSouth::~HandleSouth()
{
}


///
/// Draw HandleSouth
///
void glabels::HandleSouth::draw( QPainter* painter ) const
{
	drawAt( painter, mOwner->w()/2, mOwner->h() );
}


///
/// HandleSouth Path
///
QPainterPath glabels::HandleSouth::path( double scale ) const
{
	return pathAt( scale, mOwner->w()/2, mOwner->h() );
}


///
/// HandleSouthWest Constructor
///
glabels::HandleSouthWest::HandleSouthWest( LabelModelObject* owner )
	: Handle(owner)
{
}


///
/// HandleSouthWest Destructor
///
glabels::HandleSouthWest::~HandleSouthWest()
{
}


///
/// Draw HandleSouthWest
///
void glabels::HandleSouthWest::draw( QPainter* painter ) const
{
	drawAt( painter, 0, mOwner->h() );
}


///
/// HandleSouthWest Path
///
QPainterPath glabels::HandleSouthWest::path( double scale ) const
{
	return pathAt( scale, 0, mOwner->w() );
}


///
/// HandleWest Constructor
///
glabels::HandleWest::HandleWest( LabelModelObject* owner )
	: Handle(owner)
{
}


///
/// HandleWest Destructor
///
glabels::HandleWest::~HandleWest()
{
}


///
/// Draw HandleWest
///
void glabels::HandleWest::draw( QPainter* painter ) const
{
	drawAt( painter, 0, mOwner->h()/2 );
}


///
/// HandleWest Path
///
QPainterPath glabels::HandleWest::path( double scale ) const
{
	return pathAt( scale, 0, mOwner->h()/2 );
}


///
/// HandleNorthWest Constructor
///
glabels::HandleNorthWest::HandleNorthWest( LabelModelObject* owner )
	: Handle(owner)
{
}


///
/// HandleNorthWest Destructor
///
glabels::HandleNorthWest::~HandleNorthWest()
{
}


///
/// Draw HandleNorthWest
///
void glabels::HandleNorthWest::draw( QPainter* painter ) const
{
	drawAt( painter, 0, 0 );
}


///
/// HandleNorthWest Path
///
QPainterPath glabels::HandleNorthWest::path( double scale ) const
{
	return pathAt( scale, 0, 0 );
}


///
/// HandleP1 Constructor
///
glabels::HandleP1::HandleP1( LabelModelObject* owner )
	: Handle(owner)
{
}


///
/// HandleP1 Destructor
///
glabels::HandleP1::~HandleP1()
{
}


///
/// Draw HandleP1
///
void glabels::HandleP1::draw( QPainter* painter ) const
{
	drawAt( painter, 0, 0 );
}


///
/// HandleP1 Path
///
QPainterPath glabels::HandleP1::path( double scale ) const
{
	return pathAt( scale, 0, 0 );
}


///
/// HandleP2 Constructor
///
glabels::HandleP2::HandleP2( LabelModelObject* owner )
	: Handle(owner)
{
}


///
/// HandleP2 Destructor
///
glabels::HandleP2::~HandleP2()
{
}


///
/// Draw HandleP2
///
void glabels::HandleP2::draw( QPainter* painter ) const
{
	drawAt( painter, mOwner->w(), mOwner->h() );
}


///
/// HandleP2 Path
///
QPainterPath glabels::HandleP2::path( double scale ) const
{
	return pathAt( scale, mOwner->w(), mOwner->h() );
}
