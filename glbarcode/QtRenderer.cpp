/*  QtRenderer.cpp
 *
 *  Copyright (C) 2017  Jim Evins <evins@snaught.com>
 *
 *  This file is part of glbarcode++.
 *
 *  glbarcode++ is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  glbarcode++ is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with glbarcode++.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "QtRenderer.h"

#include <QFont>
#include <QFontMetrics>
#include <QString>


namespace glbarcode
{

	struct QtRenderer::PrivateData
	{
		QPainter* painter;
		QColor    color;
	};


	QtRenderer::QtRenderer()
	{
		d = new QtRenderer::PrivateData;

		d->painter = nullptr;
	}


	QtRenderer::QtRenderer( QPainter* painter )
	{
		d = new QtRenderer::PrivateData;

		setPainter( painter );
	}


	QtRenderer::QtRenderer( const QtRenderer& from )
	{
		d = new QtRenderer::PrivateData;

		*d = *from.d;
	}


	QtRenderer::~QtRenderer()
	{
		delete d;
	}


	QtRenderer& QtRenderer::operator=( const QtRenderer& from )
	{
		*d = *from.d;

		return *this;
	}


	QPainter* QtRenderer::painter( void ) const
	{
		return d->painter;
	}


	QtRenderer& QtRenderer::setPainter( QPainter* painter )
	{
		d->painter = painter;

		return *this;
	}


	void QtRenderer::drawBegin( double w, double h )
	{
		if ( d->painter )
		{
			d->painter->save();
			d->color = d->painter->pen().color(); // Get current pen color
		}
	}


	void QtRenderer::drawEnd( void )
	{
		if ( d->painter )
		{
			d->painter->restore();
		}
	}


	void QtRenderer::drawLine( double x, double y, double w, double h )
	{
		if ( d->painter )
		{
			double x = x + w/2; // Offset line origin by 1/2 line width.

			d->painter->setPen( QPen( d->color, w ) );
			d->painter->drawLine( QPointF(x, y), QPointF(x, y+h) );
		}
	}


	void QtRenderer::drawBox( double x, double y, double w, double h )
	{
		if ( d->painter )
		{
			d->painter->setPen( QPen( Qt::NoPen ) );
			d->painter->setBrush( QBrush( d->color ) );
		
			d->painter->drawRect( QRectF(x, y, w, h) );
		}
	}


	void QtRenderer::drawText( double x, double y, double size, const std::string& text )
	{
		if ( d->painter )
		{
			d->painter->setPen( QPen( d->color ) );

			QFont font = d->painter->font();
			font.setStyleHint( QFont::Monospace );
			font.setPointSizeF( size );
			d->painter->setFont( font );

			QFontMetrics fm( font );
			QRect rect = fm.boundingRect( QString::fromStdString(text) );

			double xCorner = x - rect.width()/2.0;
			double yCorner = y - rect.height() + fm.descent();
		
			d->painter->drawText( QPointF(xCorner, yCorner), QString::fromStdString(text) );
		}
	}


	void QtRenderer::drawRing( double x, double y, double r, double w )
	{
		if ( d->painter )
		{
			d->painter->setPen( QPen( d->color, w ) );
			d->painter->setBrush( Qt::NoBrush );
		
			d->painter->drawEllipse( QPointF(x, y), r, r );
		}
	}


	void QtRenderer::drawHexagon( double x, double y, double h )
	{
		if ( d->painter )
		{
			d->painter->setPen( QPen( Qt::NoPen ) );
			d->painter->setBrush( QBrush( d->color ) );
		
			QPolygonF hexagon;
			hexagon << QPointF( x,           y          )
			        << QPointF( x + 0.433*h, y + 0.25*h )
			        << QPointF( x + 0.433*h, y + 0.75*h )
			        << QPointF( x,           y +      h )
			        << QPointF( x - 0.433*h, y + 0.75*h )
			        << QPointF( x - 0.433*h, y + 0.25*h );

			d->painter->drawPolygon( hexagon );
		}
	}


}
