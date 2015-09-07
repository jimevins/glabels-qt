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
#include <QtDebug>


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
glabels::Handle::Handle( LabelModelObject* owner, Location location )
	: mOwner(owner), mLocation(location)
{
}


///
/// Handle Destructor
///
glabels::Handle::~Handle()
{
}


///
/// Handle owner
///
glabels::LabelModelObject* glabels::Handle::owner() const
{
	return mOwner;
}


///
/// Handle location
///
glabels::Handle::Location glabels::Handle::location() const
{
	return mLocation;
}


///
/// Draw Handle at x,y
///
void glabels::Handle::drawAt( QPainter* painter, double scale, double x, double y ) const
{
	painter->save();

	painter->translate( x, y );

	double s = 1.0 / scale;

	QPen pen( handleOutlineColor );
	pen.setCosmetic( true );
	pen.setWidth( handleOutlineWidthPixels );

	painter->setPen( pen );
	painter->setBrush( handleFillColor );

	painter->drawRect( QRectF( -s*handlePixels/2.0, -s*handlePixels/2.0, s*handlePixels, s*handlePixels ) );

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
/// HandleNorthWest Constructor
///
glabels::HandleNorthWest::HandleNorthWest( LabelModelObject* owner )
	: Handle( owner, NW )
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
void glabels::HandleNorthWest::draw( QPainter* painter, double scale ) const
{
	drawAt( painter, scale, 0, 0 );
}


///
/// HandleNorthWest Path
///
QPainterPath glabels::HandleNorthWest::path( double scale ) const
{
	return pathAt( scale, 0, 0 );
}


///
/// HandleNorth Constructor
///
glabels::HandleNorth::HandleNorth( LabelModelObject* owner )
	: Handle( owner, N )
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
void glabels::HandleNorth::draw( QPainter* painter, double scale ) const
{
	drawAt( painter, scale, mOwner->w()/2, 0 );
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
	: Handle( owner, NE )
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
void glabels::HandleNorthEast::draw( QPainter* painter, double scale ) const
{
	drawAt( painter, scale, mOwner->w(), 0 );
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
	: Handle( owner, E )
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
void glabels::HandleEast::draw( QPainter* painter, double scale ) const
{
	drawAt( painter, scale, mOwner->w(), mOwner->h()/2 );
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
	: Handle( owner, SE )
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
void glabels::HandleSouthEast::draw( QPainter* painter, double scale ) const
{
	drawAt( painter, scale, mOwner->w(), mOwner->h() );
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
	: Handle( owner, S )
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
void glabels::HandleSouth::draw( QPainter* painter, double scale ) const
{
	drawAt( painter, scale, mOwner->w()/2, mOwner->h() );
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
	: Handle( owner, SW )
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
void glabels::HandleSouthWest::draw( QPainter* painter, double scale ) const
{
	drawAt( painter, scale, 0, mOwner->h() );
}


///
/// HandleSouthWest Path
///
QPainterPath glabels::HandleSouthWest::path( double scale ) const
{
	return pathAt( scale, 0, mOwner->h() );
}


///
/// HandleWest Constructor
///
glabels::HandleWest::HandleWest( LabelModelObject* owner )
	: Handle( owner, W )
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
void glabels::HandleWest::draw( QPainter* painter, double scale ) const
{
	drawAt( painter, scale, 0, mOwner->h()/2 );
}


///
/// HandleWest Path
///
QPainterPath glabels::HandleWest::path( double scale ) const
{
	return pathAt( scale, 0, mOwner->h()/2 );
}


///
/// HandleP1 Constructor
///
glabels::HandleP1::HandleP1( LabelModelObject* owner )
	: Handle( owner, P1 )
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
void glabels::HandleP1::draw( QPainter* painter, double scale ) const
{
	drawAt( painter, scale, 0, 0 );
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
	: Handle( owner, P2 )
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
void glabels::HandleP2::draw( QPainter* painter, double scale ) const
{
	drawAt( painter, scale, mOwner->w(), mOwner->h() );
}


///
/// HandleP2 Path
///
QPainterPath glabels::HandleP2::path( double scale ) const
{
	return pathAt( scale, mOwner->w(), mOwner->h() );
}
