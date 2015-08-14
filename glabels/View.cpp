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

#include <algorithm>
#include <cmath>
#include <QMouseEvent>
#include <QtDebug>

#include "LabelModel.h"
#include "LabelModelObject.h"

#include "libglabels/Markup.h"
#include "libglabels/FrameRect.h"
#include "libglabels/FrameRound.h"
#include "libglabels/FrameEllipse.h"
#include "libglabels/FrameCd.h"


//
// Private Configuration Data
//
namespace
{
	const int    nZoomLevels = 14;
	const double zoomLevels[nZoomLevels] = { 8, 6, 4, 3, 2, 1.5, 1, 0.75, 0.67, 0.50, 0.33, 0.25, 0.15, 0.10 };

	const double ZOOM_TO_FIT_PAD = 16.0;

        const QColor  shadowColor( 64, 64, 64, 128 );
	const double  shadowOffsetPixels = 4;

        const QColor  labelColor( 255, 255, 255 );
        const QColor  labelOutlineColor( 0, 0, 0 );
	const double  labelOutlineWidthPixels = 1;

	const QColor  gridLineColor( 192, 192, 192 );
	const double  gridLineWidthPixels = 1;
	const double  gridSpacing = 9; // TODO: determine from locale.

	const QColor  markupLineColor( 240, 99, 99 );
	const double  markupLineWidthPixels = 1;

        const QColor  selectRegionFillColor( 192, 192, 255, 128 );
        const QColor  selectRegionOutlineColor( 0, 0, 255, 128 );
	const double  selectRegionOutlineWidthPixels = 3;
}



///
/// Constructor
///
glabels::View::View( QWidget *parent ) : QWidget(parent)
{
	mState = IdleState;

	setZoomReal( 1, false );

	mModel              = 0;
	mMarkupVisible      = true;
	mGridVisible        = true;
	mGridSpacing        = 18;
	mInObjectCreateMode = false;

	setMouseTracking( true );
}


///
/// Zoom property
///
double
glabels::View::zoom() const
{
	return mZoom;
}


///
/// Markup visible? property
///
bool
glabels::View::markupVisible() const
{
	return mMarkupVisible;
}


///
/// Grid visible? property
///
bool
glabels::View::qridVisible() const
{
	return mGridVisible;
}


///
/// Model Parameter Setter
///
void
glabels::View::setModel( LabelModel* model )
{
	mModel = model;

	if ( model )
	{
		connect( model, SIGNAL(changed()), this, SLOT(onModelChanged()) );
		connect( model, SIGNAL(selectionChanged()), this, SLOT(onModelSelectionChanged()) );
		connect( model, SIGNAL(sizeChanged()), this, SLOT(onModelSizeChanged()) );
	}
}


///
/// Grid Visibility Parameter Setter
///
void
glabels::View::setGridVisible( bool visibleFlag )
{
	mGridVisible = visibleFlag;
	update();
}


///
/// Markup Visibility Parameter Setter
///
void
glabels::View::setMarkupVisible( bool visibleFlag )
{
	mMarkupVisible = visibleFlag;
	update();
}


///
/// Zoom In "One Notch"
///
void
glabels::View::zoomIn()
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


///
/// Zoom Out "One Notch"
///
void
glabels::View::zoomOut()
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


///
/// Zoom To 1:1 Scale
///
void
glabels::View::zoom1To1()
{
	setZoomReal( 1.0, false );
}


///
/// Zoom To Fit
///
void
glabels::View::zoomToFit()
{
	using std::min;
	using std::max;

	double x_scale = (72.0/physicalDpiX()) * ( width() - ZOOM_TO_FIT_PAD ) / mModel->w();
	double y_scale = (72.0/physicalDpiY()) * ( height() - ZOOM_TO_FIT_PAD ) / mModel->h();
	double newZoom = min( x_scale, y_scale );

	// Limits
	newZoom = min( newZoom, zoomLevels[0] );
	newZoom = max( newZoom, zoomLevels[nZoomLevels-1] );

	setZoomReal( newZoom, true );
}


///
/// Is Zoom at Maximum?
///
bool
glabels::View::isZoomMax() const
{
	return ( mZoom >= zoomLevels[0] );
}


///
/// Is Zoom at Minimum?
///
bool
glabels::View::isZoomMin() const
{
	return ( mZoom <= zoomLevels[nZoomLevels-1] );
}


///
/// Set Zoom to Value
///
void
glabels::View::setZoomReal( double zoom, bool zoomToFitFlag )
{
	mZoom          = zoom;
	mZoomToFitFlag = zoomToFitFlag;

	update();

	emit zoomChanged();
}


///
/// Paint Event Handler
///
void
glabels::View::paintEvent( QPaintEvent* event )
{
	if ( mModel )
	{
		QPainter painter( this );

		painter.scale( mZoom, mZoom );

		drawBgLayer( &painter );
		drawGridLayer( &painter );
		drawMarkupLayer( &painter );
		drawObjectsLayer( &painter );
		drawFgLayer( &painter );
		drawHighlightLayer( &painter );
		drawSelectRegionLayer( &painter );
	}
}


///
/// Resize Event Handler
///
void
glabels::View::resizeEvent( QResizeEvent *event )
{
	if ( mZoomToFitFlag )
	{
		zoomToFit();
	}
	else
	{
		update();
	}
}


///
/// Mouse Movement Event Handler
///
void
glabels::View::mouseMoveEvent( QMouseEvent* event )
{
	if ( mModel )
	{
		/*
		 * Translate to label coordinates
		 */
		QTransform transform;

		transform.scale( mZoom, mZoom );

		qreal xWorld, yWorld;
		transform.inverted().map( event->x(), event->y(), &xWorld, &yWorld );

		/*
		 * Emit signal regardless of mode
		 */
		emit pointerMoved( xWorld, yWorld );


		/*
		 * Handle event as appropriate for mode
		 */
		if ( !mInObjectCreateMode )
		{
			switch (mState)
			{

			case IdleState:
				/* @TODO handle handles. */
				if ( mModel->objectAt( mZoom, xWorld, yWorld ) )
				{
					setCursor( Qt::SizeAllCursor );
				}
				else
				{
					setCursor( Qt::ArrowCursor );
				}
				break;

			case ArrowSelectRegion:
				mSelectRegion.setX2( xWorld );
				mSelectRegion.setY2( yWorld );
				update();
				break;

			case ArrowMove:
				mModel->moveSelection( (xWorld - mMoveLastX),
						       (yWorld - mMoveLastY) );
				mMoveLastX = xWorld;
				mMoveLastY = yWorld;
				break;

			case ArrowResize:
				/* @TODO handle resize motion */
				break;

			default:
				// Should not happen!
				qWarning() << "Invalid arrow state.";
				break;

			}
		}
		else
		{
			if ( mState != IdleState )
			{
				switch (mCreateObjectType)
				{
				case Box:
					// @TODO
					break;
				case Ellipse:
					// @TODO
					break;
				case Line:
					// @TODO
					break;
				case Image:
					// @TODO
					break;
				case Text:
					// @TODO
					break;
				case Barcode:
					// @TODO
					break;
				default:
					// Should not happen!
					qWarning() << "Invalid create type.";
					break;
				}
			}
		}
	}
}


///
/// Mouse Button Press Event Handler
///
void
glabels::View::mousePressEvent( QMouseEvent* event )
{
	if ( mModel )
	{
		/*
		 * Translate to label coordinates
		 */
		QTransform transform;

		transform.scale( mZoom, mZoom );

		qreal xWorld, yWorld;
		transform.inverted().map( event->x(), event->y(), &xWorld, &yWorld );


		if ( event->button() & Qt::LeftButton )
		{
			// Select Region
			if ( !(event->modifiers() & Qt::ControlModifier) )
			{
				mModel->unselectAll();
			}

			mSelectRegionVisible = true;
			mSelectRegion.setX1( xWorld );
			mSelectRegion.setY1( yWorld );
			mSelectRegion.setX2( xWorld );
			mSelectRegion.setY2( yWorld );

			mState = ArrowSelectRegion;
			update();
		}
		else
		{
		}
	}
}


///
/// Mouse Button Release Event Handler
///
void
glabels::View::mouseReleaseEvent( QMouseEvent* event )
{
	if ( mModel )
	{
		/*
		 * Translate to label coordinates
		 */
		QTransform transform;

		transform.scale( mZoom, mZoom );

		qreal xWorld, yWorld;
		transform.inverted().map( event->x(), event->y(), &xWorld, &yWorld );


		if ( event->button() & Qt::LeftButton )
		{
			switch (mState)
			{

			case IdleState:
				break;

			case ArrowSelectRegion:
				mSelectRegionVisible = false;
				mSelectRegion.setX2( xWorld );
				mSelectRegion.setY2( yWorld );

				mModel->selectRegion( mSelectRegion );

				mState = IdleState;
				update();
				break;

			default:
				// Should not happen!
				break;

			}
		}
		else
		{
		}
	}
}


///
/// Leave Event Handler
///
void
glabels::View::leaveEvent( QEvent* event )
{
	if ( mModel )
	{
		emit pointerExited();
	}
}


///
/// Draw Background Layer
///
void
glabels::View::drawBgLayer( QPainter* painter )
{
	/*
	 * Draw shadow
	 */
	painter->save();

	painter->setBrush( QBrush( shadowColor ) );
	painter->setPen( Qt::NoPen );

	painter->translate( shadowOffsetPixels/mZoom, shadowOffsetPixels/mZoom );

	if ( mModel->rotate() )
	{
		painter->rotate( -90 );
		painter->translate( -mModel->frame()->w(), 0 );
	}
	painter->drawPath( mModel->frame()->path() );

	painter->restore();


	/*
	 * Draw label
	 */
	painter->save();

	painter->setBrush( QBrush( labelColor ) );
	painter->setPen( Qt::NoPen );

	if ( mModel->rotate() )
	{
		painter->rotate( -90 );
		painter->translate( -mModel->frame()->w(), 0 );
	}
	painter->drawPath( mModel->frame()->path() );

	painter->restore();
}


///
/// Draw Grid Layer
///
void
glabels::View::drawGridLayer( QPainter* painter )
{
	if ( mGridVisible )
	{
		double w = mModel->frame()->w();
		double h = mModel->frame()->h();

		double x0, y0;
		if ( dynamic_cast<const libglabels::FrameRect*>( mModel->frame() ) )
		{
			x0 = gridSpacing;
			y0 = gridSpacing;
		}
		else
		{
			/* round labels, adjust grid to line up with center of label. */
			x0 = fmod( w/2, gridSpacing );
			y0 = fmod( h/2, gridSpacing );
		}

		painter->save();
		if ( mModel->rotate() )
		{
			painter->rotate( -90 );
			painter->translate( -mModel->frame()->w(), 0 );
		}

		painter->setClipPath( mModel->frame()->path() );

		QPen pen( gridLineColor, gridLineWidthPixels );
		pen.setCosmetic( true );
		painter->setPen( pen );

		for ( double x = x0; x < w; x += gridSpacing )
		{
			painter->drawLine( x, 0, x, h );
		}

		for ( double y = y0; y < h; y += gridSpacing )
		{
			painter->drawLine( 0, y, w, y );
		}

		painter->restore();
	}
}


///
/// Draw Markup Layer
///
void
glabels::View::drawMarkupLayer( QPainter* painter )
{
	if ( mMarkupVisible )
	{
		painter->save();

		painter->setBrush( Qt::NoBrush );
		painter->setPen( QPen( markupLineColor ) );

		if ( mModel->rotate() )
		{
			painter->rotate( -90 );
			painter->translate( -mModel->frame()->w(), 0 );
		}

		foreach( libglabels::Markup* markup, mModel->frame()->markups() )
		{
			painter->drawPath( markup->path() );
		}

		painter->restore();
	}
}


///
/// Draw Objects Layer
///
void
glabels::View::drawObjectsLayer( QPainter* painter )
{
	mModel->draw( painter );
}


///
/// Draw Foreground Layer
///
void
glabels::View::drawFgLayer( QPainter* painter )
{
	/*
	 * Draw label outline
	 */
	painter->save();

	QPen pen( labelOutlineColor, labelOutlineWidthPixels );
	pen.setCosmetic( true );
	painter->setBrush( QBrush( Qt::NoBrush ) );
	painter->setPen( pen );

	if ( mModel->rotate() )
	{
		painter->rotate( -90 );
		painter->translate( -mModel->frame()->w(), 0 );
	}
	painter->drawPath( mModel->frame()->path() );

	painter->restore();
}


///
/// Draw Highlight Layer
///
void
glabels::View::drawHighlightLayer( QPainter* painter )
{
	painter->save();

	foreach ( LabelModelObject* object, mModel->objectList() )
	{
		if ( object->isSelected() )
		{
			object->drawSelectionHighlight( painter );
		}
	}

	painter->restore();
}


///
/// Draw Select Region Layer
///
void
glabels::View::drawSelectRegionLayer( QPainter* painter )
{
	if ( mSelectRegionVisible )
	{
		painter->save();

		QPen pen( selectRegionOutlineColor, selectRegionOutlineWidthPixels );
		pen.setCosmetic( true );
		painter->setBrush( selectRegionFillColor );
		painter->setPen( pen );

		painter->drawRect( mSelectRegion.rect() );
		
		painter->restore();
	}

}
