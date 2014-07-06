/*  ColorSwatch.cpp
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

#include "ColorSwatch.h"

#include <QGraphicsRectItem>
#include <QGraphicsDropShadowEffect>
#include <iostream>


//
// Private Configuration Data
//
namespace
{
        const QColor  outlineColor( 0, 0, 0 );
	const double  outlineWidthPixels = 1;
}


namespace glabels
{

	///
	/// Constructor
	///
	ColorSwatch::ColorSwatch( int w, int h, QColor& color, QWidget *parent )
		: mW(w), mH(h), mColor(color), QGraphicsView(parent)
	{
		setAttribute(Qt::WA_TranslucentBackground);
		viewport()->setAutoFillBackground(false);
		setFrameStyle( QFrame::NoFrame );
		setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
		resize( mW, mH );
		fitInView( 0, 0, mW, mH, Qt::KeepAspectRatio );

		mScene = new QGraphicsScene();
		setScene( mScene );

		mScene->setSceneRect( 0, 0, mW, mH );

		QBrush brush( mColor );
		QPen pen( outlineColor );
		pen.setWidthF( outlineWidthPixels );

		mSwatchItem = new QGraphicsRectItem( 1, 1, mW-2, mH-2 );
		mSwatchItem->setBrush( brush );
		mSwatchItem->setPen( pen );
				
		mScene->addItem( mSwatchItem );
	}


	///
	/// Color Property Setter
	///
	void ColorSwatch::setColor( QColor& color )
	{
		mColor = color;

		QBrush brush( mColor );
		mSwatchItem->setBrush( brush );
	}


}
