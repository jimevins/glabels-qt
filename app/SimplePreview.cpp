/*  SimplePreview.cpp
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

#include "SimplePreview.h"

#include <QGraphicsRectItem>
#include <QGraphicsDropShadowEffect>
#include <iostream>


namespace
{
        const QColor paperColor( 255, 255, 255 );
        const QColor paperOutlineColor( 0, 0, 0 );

        const QColor shadowColor( 64, 64, 64 );
	const double shadowOffset = 3;
	const double shadowRadius = 12;

        const QColor labelColor( 242, 242, 242 );
        const QColor labelOutlineColor( 64, 64, 64 );
}


namespace gLabels
{

	SimplePreview::SimplePreview( QWidget *parent = 0 ) : QGraphicsView(parent)
	{
		mScene = new QGraphicsScene();
		setScene( mScene );

		setAttribute(Qt::WA_TranslucentBackground);
		viewport()->setAutoFillBackground(false);

		setFrameStyle( QFrame::NoFrame );
	}


	void SimplePreview::setTemplate( const libglabels::Template *tmplate )
	{
		clearScene();

		if ( tmplate != NULL )
		{
			// Set scene up with a 5% margin around paper
			double x = -0.05 * tmplate->pageWidth();
			double y = -0.05 * tmplate->pageHeight();
			double w = 1.10 * tmplate->pageWidth();
			double h = 1.10 * tmplate->pageHeight();

			mScene->setSceneRect( x, y, w, h );
			fitInView( x, y, w, h, Qt::KeepAspectRatio );

			drawPaper( tmplate->pageWidth(), tmplate->pageHeight() );
			drawLabels( tmplate );
		}
	}


	void SimplePreview::clearScene()
	{
		foreach ( QGraphicsItem *item, mScene->items() )
		{
			mScene->removeItem( item );
			delete item;
		}
	}


	void SimplePreview::drawPaper( double pw, double ph )
	{
		QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
		shadowEffect->setColor( shadowColor );
		shadowEffect->setOffset( shadowOffset );
		shadowEffect->setBlurRadius( shadowRadius );

		QBrush brush( paperColor );
		QPen pen( paperOutlineColor );

		QGraphicsRectItem *pageItem = new QGraphicsRectItem( 0, 0, pw, ph );
		pageItem->setBrush( brush );
		pageItem->setPen( pen );
		pageItem->setGraphicsEffect( shadowEffect );
				
		mScene->addItem( pageItem );
	}


	void SimplePreview::drawLabels( const libglabels::Template *tmplate )
	{
		libglabels::Frame *frame = tmplate->frames().first();

		foreach (libglabels::Point origin, frame->getOrigins() )
		{
			drawLabel( origin.x(), origin.y(), frame->path() );
		}
	}


	void SimplePreview::drawLabel( double x, double y, const QPainterPath &path )
	{
		QBrush brush( labelColor );
		QPen pen( labelOutlineColor );

		QGraphicsPathItem *labelItem  = new QGraphicsPathItem( path );
		labelItem->setBrush( brush );
		labelItem->setPen( pen );
		labelItem->setPos( x, y );

		mScene->addItem( labelItem );
	}

}
