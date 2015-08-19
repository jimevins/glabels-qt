/*  ColorPaletteButtonItem.cpp
 *
 *  Copyright (C) 2014  Jim Evins <evins@snaught.com>
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

#include "ColorPaletteButtonItem.h"


#include <QPainter>


//
// Private Configuration Data
//
namespace
{
	const int     border = 4;
	const int     hBox = 25;
        const QColor  hoverOutlineColor( 89, 130, 182 );
        const QColor  hoverGradientColor0( 164, 195, 232 );
        const QColor  hoverGradientColor1( 147, 181, 224 );
	const int     outlineWidthPixels = 1;
        const QColor  textColor( 0, 0, 0 );
        const QColor  hoverTextColor( 255, 255, 255 );
}


namespace glabels
{

	///
	/// Constructor From Data
	///
	ColorPaletteButtonItem::ColorPaletteButtonItem( const QString& text, QWidget* parent )
		: QWidget(parent), mText(text), mHover(false)
	{
		setSizePolicy( QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed ) );
		setMinimumSize( hBox+2*border+1, hBox+2*border+1 );
	}


	///
	/// Paint Event
	///
	void ColorPaletteButtonItem::paintEvent( QPaintEvent* event )
	{
		QPainter painter(this);

		//
		// Draw background
		//
		if ( mHover )
		{
			QLinearGradient gradient( 0, 0, 0, height() );
			gradient.setColorAt( 0, hoverGradientColor0 );
			gradient.setColorAt( 1, hoverGradientColor1 );
			painter.setBrush( QBrush( gradient ) );

			QPen pen( hoverOutlineColor );
			pen.setWidth( outlineWidthPixels );
			painter.setPen( pen );

			painter.drawRect( 0, 0, width()-1, height()-1 );
		}

		//
		// Draw text
		//
		painter.setBrush( QBrush( Qt::NoBrush ) );

		if ( mHover )
		{
			painter.setPen( QPen( hoverTextColor ) );
		}
		else
		{
			painter.setPen( QPen( textColor ) );
		}

		QRect textRect( border, border, width()-2*border, hBox );

		painter.drawText( textRect, Qt::AlignLeft|Qt::AlignVCenter, mText );
	}


	///
	/// Enter Event
	///
	void ColorPaletteButtonItem::enterEvent( QEvent* event )
	{
		mHover = true;
		update();
	}


	///
	/// Leave Event
	///
	void ColorPaletteButtonItem::leaveEvent( QEvent* event )
	{
		mHover = false;
		update();
	}

	
	///
	/// Mouse Press Event
	///
	void ColorPaletteButtonItem::mousePressEvent( QMouseEvent* event )
	{
		emit activated();
	}

}

