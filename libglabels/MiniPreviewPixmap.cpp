/*  MiniPreviewPixmap.cpp
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

#include "MiniPreviewPixmap.h"

#include "Template.h"


namespace
{
	const QColor paperColor( 217, 217, 217 );
	const QColor paperOutlineColor( 0, 0, 0 );
	const double paperOutlineWidthPixels = 1.0;

	const QColor labelColor( 242, 242, 242 );
	const QColor labelOutlineColor( 64, 64, 64 );
	const double labelOutlineWidthPixels = 1.0;
}


namespace libglabels
{

	void MiniPreviewPixmap::draw( const Template *tmplate, int width, int height )
	{
		fill( Qt::transparent );

		QPainter painter( this );

		painter.setBackgroundMode( Qt::TransparentMode );
		painter.setRenderHint( QPainter::Antialiasing, true );

		double w = width - 1;
		double h = height - 1;
		double scale;
		if ( (w/tmplate->pageWidth()) > (h/tmplate->pageHeight()) )
		{
			scale = h / tmplate->pageHeight();
		}
		else
		{
			scale = w / tmplate->pageWidth();
		}
		painter.scale( scale, scale );

		double xOffset = ( width/scale - tmplate->pageWidth() ) / 2;
		double yOffset = ( height/scale - tmplate->pageHeight() ) / 2;
		painter.translate( xOffset, yOffset );

		drawPaper( painter, tmplate, scale );
		drawLabelOutlines( painter, tmplate, scale );
	}


	void MiniPreviewPixmap::drawPaper( QPainter &painter, const Template *tmplate, double scale )
	{
		QBrush brush( paperColor );
		QPen pen( paperOutlineColor );
		pen.setWidth( paperOutlineWidthPixels/scale );

		painter.save();

		painter.setBrush( brush );
		painter.setPen( pen );
		painter.drawRect( 0, 0, tmplate->pageWidth(), tmplate->pageHeight() );

		painter.restore();
	}


	void MiniPreviewPixmap::drawLabelOutlines( QPainter &painter, const Template *tmplate, double scale )
	{
		QBrush brush( labelColor );
		QPen pen( labelOutlineColor );
		pen.setWidth( labelOutlineWidthPixels/scale );

		painter.save();

		painter.setBrush( brush );
		painter.setPen( pen );

		Frame *frame = tmplate->frames().first();
		QVector<Point> origins = frame->getOrigins();

		foreach ( Point point, origins )
		{
			drawLabelOutline( painter, frame, point.x(), point.y() );
		}

		painter.restore();
	}


	void MiniPreviewPixmap::drawLabelOutline( QPainter &painter, const Frame *frame, double x0, double y0 )
	{
		painter.save();

		painter.translate( x0, y0 );
		painter.drawPath( frame->path() );
		
		painter.restore();
	}

}

