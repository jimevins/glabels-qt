/*  Outline.cpp
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

#include "Outline.h"


#include "LabelModelObject.h"

#include <QColor>


namespace
{
	const double outlineWidthPixels = 2;
	const QColor outlineColor( 0,  0,   0,  192 );
}


///
/// Outline Constructor
///
glabels::Outline::Outline( LabelModelObject* owner )
	: mOwner(owner)
{
}


///
/// Outline Destructor
///
glabels::Outline::~Outline()
{
}


///
/// Draw Outline
///
void glabels::Outline::draw( QPainter* painter ) const
{
	painter->save();

	QPen pen( outlineColor, outlineWidthPixels, Qt::DotLine );
	pen.setCosmetic( true );
	painter->setPen( pen );
	painter->setBrush( Qt::NoBrush );

	painter->drawRect( 0, 0, mOwner->w(), mOwner->h() );

	painter->restore();
}


///
/// Create Outline path
///
QPainterPath glabels::Outline::path( QPainter *painter ) const
{
	QPainterPath path;

	path.addRect( 0, 0, mOwner->w(), mOwner->h() );
	
	return path;
}


