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
	const qreal dashSize = 2;

	const double slopPixels = 2;
	const double outlineWidthPixels = 1;
	const QColor outlineColor1(   0,   0,   0 );
	const QColor outlineColor2( 255, 255, 255 );
}


///
/// Outline Constructor
///
glabels::Outline::Outline( LabelModelObject* owner )
	: mOwner(owner)
{
	mDashes << dashSize << dashSize;

	mPen1.setColor( outlineColor1 );
	mPen1.setWidth( outlineWidthPixels );
	mPen1.setCosmetic( true );
	mPen1.setCapStyle( Qt::FlatCap );
	mPen1.setDashPattern( mDashes );

	mPen2.setColor( outlineColor2 );
	mPen2.setWidth( outlineWidthPixels );
	mPen2.setCosmetic( true );
	mPen2.setCapStyle( Qt::FlatCap );
	mPen2.setDashPattern( mDashes );
	mPen2.setDashOffset( dashSize );
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

	painter->setBrush( Qt::NoBrush );

	painter->setPen( mPen1 );
	painter->drawRect( QRectF( 0, 0, mOwner->w(), mOwner->h() ) );

	painter->setPen( mPen2 );
	painter->drawRect( QRectF( 0, 0, mOwner->w(), mOwner->h() ) );

	painter->restore();
}


///
/// Create Outline path
///
QPainterPath glabels::Outline::path( double scale ) const
{
	double s = 1 / scale;

	QPainterPath path;

	path.addRect( -s*slopPixels, -s*slopPixels,
		      mOwner->w()+s*2*slopPixels, mOwner->h()+s*2*slopPixels );
	path.closeSubpath();
	path.addRect( s*slopPixels, s*slopPixels,
		      mOwner->w()-s*2*slopPixels, mOwner->h()-s*2*slopPixels );
	
	return path;
}


