/*  View.cpp
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

#include "View.h"

#include <QMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsDropShadowEffect>
#include <cmath>
#include <iostream>

#include "libglabels/Markup.h"
#include "libglabels/FrameRect.h"
#include "libglabels/FrameRound.h"
#include "libglabels/FrameEllipse.h"
#include "libglabels/FrameCd.h"


namespace
{
	const int    nZoomLevels = 14;
	const double zoomLevels[nZoomLevels] = { 8, 6, 4, 3, 2, 1.5, 1, 0.75, 0.67, 0.50, 0.33, 0.25, 0.15, 0.10 };

	const double ZOOM_TO_FIT_PAD = 16.0;

        const QColor  shadowColor( 64, 64, 64 );
	const double  shadowOffsetPixels = 3;
	const double  shadowRadiusPixels = 12;

        const QColor  labelColor( 255, 255, 255 );
        const QColor  labelOutlineColor( 0, 0, 0 );
	const double  labelOutlineWidthPixels = 1;

	const QColor  gridLineColor( 192, 192, 192 );
	const double  gridLineWidthPixels = 1;
	const double  gridSpacing = 9; // TODO: determine from locale.

	const QColor  markupLineColor( 240, 99, 99 );
	const double  markupLineWidthPixels = 1;
}


namespace glabels
{

	View::View( QWidget *parent ) : QGraphicsView(parent)
	{
		setZoomReal( 1, false );
		mModel         = 0;

		setMouseTracking( true );

		setAttribute( Qt::WA_TranslucentBackground );
		viewport()->setAutoFillBackground( false );

		mScene = new QGraphicsScene();
		setScene( mScene );

		mScene->addItem( mLabelLayer      = new QGraphicsItemGroup() );
		mScene->addItem( mGridLayer       = new QGraphicsItemGroup() );
		mScene->addItem( mMarkupLayer     = new QGraphicsItemGroup() );
		mScene->addItem( mObjectLayer     = new QGraphicsItemGroup() );
		mScene->addItem( mForegroundLayer = new QGraphicsItemGroup() );
	}


	void View::setModel( LabelModel* model )
	{
		mModel = model;

		createLabelLayer();
		createGridLayer();
		createMarkupLayer();

		foreach (LabelModelObject* object, model->objectList() )
		{
			addObjectToObjectLayer( object );
		}

		createForegroundLayer();
	}


	void View::setGridVisible( bool visibleFlag )
	{
		mGridLayer->setVisible( visibleFlag );
	}


	void View::setMarkupVisible( bool visibleFlag )
	{
		mMarkupLayer->setVisible( visibleFlag );
	}


	void View::zoomIn()
	{
		// Find closest standard zoom level to our current zoom
		// Start with 2nd largest scale
		int i_min = 1;
		double dist_min = fabs( zoomLevels[1] - mZoom );

		for ( int i = 2; i < nZoomLevels; i++ )
		{
			double dist = fabs( zoomLevels[i] - mZoom );
			if ( dist < dist_min )
			{
				i_min = i;
				dist_min = dist;
			}
		}

		// Zoom in one notch
		setZoomReal( zoomLevels[i_min-1], false );
	}


	void View::zoomOut()
	{
		// Find closest standard zoom level to our current zoom
		// Start with largest scale, end on 2nd smallest
		int i_min = 0;
		double dist_min = fabs( zoomLevels[0] - mZoom );

		for ( int i = 1; i < (nZoomLevels-1); i++ )
		{
			double dist = fabs( zoomLevels[i] - mZoom );
			if ( dist < dist_min )
			{
				i_min = i;
				dist_min = dist;
			}
		}

		// Zoom out one notch
		setZoomReal( zoomLevels[i_min+1], false );
	}


	void View::zoom1To1()
	{
		setZoomReal( 1.0, false );
	}


	void View::zoomToFit()
	{
		double x_scale = (72.0/physicalDpiX()) * ( width() - ZOOM_TO_FIT_PAD ) / mModel->w();
		double y_scale = (72.0/physicalDpiY()) * ( height() - ZOOM_TO_FIT_PAD ) / mModel->h();
		double newZoom = min( x_scale, y_scale );

		// Limits
		newZoom = min( newZoom, zoomLevels[0] );
		newZoom = max( newZoom, zoomLevels[nZoomLevels-1] );

		setZoomReal( newZoom, true );
	}


	bool View::isZoomMax() const
	{
		return ( mZoom >= zoomLevels[0] );
	}


	bool View::isZoomMin() const
	{
		return ( mZoom <= zoomLevels[nZoomLevels-1] );
	}


	void View::setZoomReal( double zoom, bool zoomToFitFlag )
	{
		mZoom          = zoom;
		mZoomToFitFlag = zoomToFitFlag;

		resetTransform();
		scale( mZoom*physicalDpiX()/72.0, mZoom*physicalDpiY()/72.0 );

		emit zoomChanged();
	}


	void View::resizeEvent( QResizeEvent *event )
	{
		if ( mZoomToFitFlag )
		{
			zoomToFit();
		}
		else
		{
			// Refresh to keep view location relative to window
			resetTransform();
			scale( mZoom*physicalDpiX()/72.0, mZoom*physicalDpiY()/72.0 );
		}
	}


	void View::mouseMoveEvent( QMouseEvent* event )
	{
		QPointF pointer = mapToScene( event->x(), event->y() );
		emit pointerMoved( pointer.x(), pointer.y() );
	}


	void View::leaveEvent( QEvent* event )
	{
		emit pointerExited();
	}


	void View::clearLayer( QGraphicsItemGroup* layer )
	{
		foreach( QGraphicsItem* item, layer->childItems() )
		{
			layer->removeFromGroup( item );
		}
	}


	void View::createLabelLayer()
	{
		clearLayer( mLabelLayer );

                QGraphicsPathItem *labelItem  = new QGraphicsPathItem( mModel->frame()->path() );

                QBrush brush( labelColor );
                labelItem->setBrush( brush );

                QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
                shadowEffect->setColor( shadowColor );
                shadowEffect->setOffset( shadowOffsetPixels );
                shadowEffect->setBlurRadius( shadowRadiusPixels );
		labelItem->setGraphicsEffect( shadowEffect );

                mLabelLayer->addToGroup( labelItem );
	}


	void View::createGridLayer()
	{
		clearLayer( mGridLayer );

                QGraphicsPathItem *clipItem  = new QGraphicsPathItem( mModel->frame()->path() );
		clipItem->setFlag( QGraphicsItem::ItemClipsChildrenToShape );

                QPen pen( gridLineColor );
		pen.setCosmetic( true );
                pen.setWidthF( gridLineWidthPixels );

		double w = mModel->w();
		double h = mModel->h();
		double x0;
		double y0;
		if ( dynamic_cast<const libglabels::FrameRect*>( mModel->frame() ) )
		{
			x0 = gridSpacing;
			y0 = gridSpacing;
		}
		else
		{
			/* round labels, align grid with center of label. */
			x0 = fmod( w/2, gridSpacing );
			y0 = fmod( h/2, gridSpacing );
		}

		for ( double x = x0; x < w; x += gridSpacing )
		{
			QGraphicsLineItem* lineItem = new QGraphicsLineItem( x, 0, x, h, clipItem );
			lineItem->setPen( pen );
		}

		for ( double y = y0; y < h; y += gridSpacing )
		{
			QGraphicsLineItem* lineItem = new QGraphicsLineItem( 0, y, w, y, clipItem );
			lineItem->setPen( pen );
		}

                mGridLayer->addToGroup( clipItem );
	}


	void View::createMarkupLayer()
	{
		clearLayer( mMarkupLayer );

                QPen pen( markupLineColor );
		pen.setCosmetic( true );
                pen.setWidthF( markupLineWidthPixels );

		const libglabels::Frame* frame = mModel->frame();

		foreach (libglabels::Markup* markup, frame->markups() )
		{
			QGraphicsItem* markupItem = markup->createGraphicsItem( frame, pen );

			mMarkupLayer->addToGroup( markupItem );
		}
	}


	void View::addObjectToObjectLayer( LabelModelObject* object )
	{
		QGraphicsItem* item = object->createGraphicsItem();
		mObjectLayer->addToGroup( item );
	}


	void View::createForegroundLayer()
	{
		clearLayer( mForegroundLayer );

                QGraphicsPathItem *outlineItem  = new QGraphicsPathItem( mModel->frame()->path() );

                QPen pen( labelOutlineColor );
		pen.setJoinStyle( Qt::MiterJoin );
		pen.setCosmetic( true );
                pen.setWidthF( labelOutlineWidthPixels );
                outlineItem->setPen( pen );

                mForegroundLayer->addToGroup( outlineItem );
	}

}
