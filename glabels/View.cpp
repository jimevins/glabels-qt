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
#include "LabelModelBoxObject.h"
#include "Cursors.h"

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
	const int     nZoomLevels = 14;
	const double  zoomLevels[nZoomLevels] = { 8, 6, 4, 3, 2, 1.5, 1, 0.75, 0.67, 0.50, 0.33, 0.25, 0.15, 0.10 };

	const double  PTS_PER_INCH = 72.0;
	const double  ZOOM_TO_FIT_PAD = 16.0;

        const QColor  backgroundColor( 192, 192, 192 );

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

	mModel              = 0;
	mMarkupVisible      = true;
	mGridVisible        = true;
	mGridSpacing        = 18;
	mInObjectCreateMode = false;

	setMouseTracking( true );

	setMinimumSize( 640, 450 );
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
		setZoomReal( 1, false );

		connect( model, SIGNAL(changed()), this, SLOT(update()) );
		connect( model, SIGNAL(selectionChanged()), this, SLOT(update()) );
		connect( model, SIGNAL(sizeChanged()), this, SLOT(update()) );

		update();
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

	double x_scale = ( width() - ZOOM_TO_FIT_PAD ) / mModel->w();
	double y_scale = ( height() - ZOOM_TO_FIT_PAD ) / mModel->h();
	double newZoom = min( x_scale, y_scale ) * PTS_PER_INCH / physicalDpiX();

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

	/* Actual scale depends on DPI of display (assume DpiX == DpiY). */
	mScale = zoom * physicalDpiX() / PTS_PER_INCH;

	/* Adjust origin to center label in widget. */
	mX0 = (width()/mScale - mModel->w()) / 2;
	mY0 = (height()/mScale - mModel->h()) / 2;

	update();

	emit zoomChanged();
}


///
/// Arrow mode (normal mode)
///
void
glabels::View::arrowMode()
{
	setCursor( Qt::ArrowCursor );

	mInObjectCreateMode = false;
	mState = IdleState;
}


///
/// Create box mode
///
void
glabels::View::createBoxMode()
{
	setCursor( Cursors::Box() );

	mInObjectCreateMode = true;
	mCreateObjectType = Box;
	mState = IdleState;
}


///
/// Resize Event Handler
///
void
glabels::View::resizeEvent( QResizeEvent *event )
{
	if ( mModel )
	{
		if ( mZoomToFitFlag )
		{
			zoomToFit();
		}
		else
		{
			/* Re-adjust origin to center label in widget. */
			mX0 = (width()/mScale - mModel->w()) / 2;
			mY0 = (height()/mScale - mModel->h()) / 2;

			update();
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
		 * Transform to label coordinates
		 */
		QTransform transform;

		transform.scale( mScale, mScale );
		transform.translate( mX0, mY0 );

		QPointF pWorld = transform.inverted().map( event->posF() );
		double xWorld = pWorld.x();
		double yWorld = pWorld.y();

		
		if ( event->button() & Qt::LeftButton )
		{
			//
			// LEFT BUTTON
			//

			if ( !mInObjectCreateMode )
			{
				//
				// NORMAL MODE
				//
				
				LabelModelObject* object = 0;
				Handle* handle = 0;
				if ( mModel->isSelectionAtomic() &&
				     (handle = mModel->handleAt( mScale, xWorld, yWorld )) != 0 )
				{
					//
					// Start an object resize
					//
					mResizeObject = handle->owner();
					mResizeHandle = handle;
					mResizeHonorAspect = event->modifiers() & Qt::ControlModifier;

					mState = ArrowResize;
				}
				else if ( (object = mModel->objectAt( mScale, xWorld, yWorld )) != 0 )
				{
					//
					// Start a Move Selection (adjusting selection if necessary)
					//
					if ( event->modifiers() & Qt::ControlModifier )
					{
						if ( object->isSelected() )
						{
							// Un-selecting a selected item
							mModel->unselectObject( object );
						}
						else
						{
							// Add to current selection
							mModel->selectObject( object );
						}
					}
					else
					{
						if ( !object->isSelected() )
						{
							// Replace current selection with this object
							mModel->unselectAll();
							mModel->selectObject( object );
						}
					}

					mMoveLastX = xWorld;
					mMoveLastY = yWorld;

					mState = ArrowMove;
				}
				else
				{
					//
					// Start a Select Region
					//
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
			}
			else
			{
				//
				// OBJECT CREATION MODE
				//
				
				if ( mState == IdleState )
				{
					switch ( mCreateObjectType )
					{
					case Box:
						mCreateObject = new LabelModelBoxObject();
						break;
					case Ellipse:
						// mCreateObject = new LabelModelEllipseObject();
						break;
					case Line: 
						// mCreateObject = new LabelModelLineObject();
						break;
					case Image:
						// mCreateObject = new LabelModelImageObject();
						break;
					case Text:
						// mCreateObject = new LabelModelTextObject();
						break;
					case Barcode:
						// mCreateObject = new LabelModelBarcodeObject();
						break;
					default:
						Q_ASSERT_X( false, "View::::mousePressEvent", "Invalid creation type" );
						break;
					}

					mCreateObject->setPosition( xWorld, yWorld );
					mCreateObject->setSize( 0, 0 );
					mModel->addObject( mCreateObject );

					mModel->unselectAll();
					mModel->selectObject( mCreateObject );

					mCreateX0 = xWorld;
					mCreateY0 = yWorld;

					mState = CreateDrag;
				}
	
			}

		}
		else if ( event->button() & Qt::RightButton )
		{
			//
			// RIGHT BUTTON
			//

		}
	}
}


///
/// Mouse Movement Event Handler
///
void
glabels::View::mouseMoveEvent( QMouseEvent* event )
{
	using std::min;
	using std::max;

	if ( mModel )
	{
		/*
		 * Transform to label coordinates
		 */
		QTransform transform;

		transform.scale( mScale, mScale );
		transform.translate( mX0, mY0 );

		QPointF pWorld = transform.inverted().map( event->posF() );
		double xWorld = pWorld.x();
		double yWorld = pWorld.y();

		
		/*
		 * Emit signal regardless of mode
		 */
		emit pointerMoved( xWorld, yWorld );


		/*
		 * Handle event as appropriate for mode
		 */
		if ( !mInObjectCreateMode )
		{
			///
			/// NORMAL MODE
			///

			switch (mState)
			{

			case IdleState:
				if ( mModel->isSelectionAtomic() &&
				     mModel->handleAt( mScale, xWorld, yWorld ) )
				{
					setCursor( Qt::CrossCursor );
				}
				else if ( mModel->objectAt( mScale, xWorld, yWorld ) )
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
				handleResizeMotion( xWorld, yWorld );
				break;

			default:
				// Should not happen!
				Q_ASSERT_X( false, "View::::mouseMoveEvent", "Invalid state" );
				break;

			}
		}
		else
		{
			//
			// OBJECT CREATION MODE
			//
				
			if ( mState != IdleState )
			{
				switch (mCreateObjectType)
				{
				case Box:
				case Ellipse:
				case Image:
				case Text:
				case Barcode:
					mCreateObject->setPosition( min( xWorld, mCreateX0 ),
								    min( yWorld, mCreateY0 ) );
					mCreateObject->setSize( max(xWorld,mCreateX0) - min(xWorld,mCreateX0),
								max(yWorld,mCreateY0) - min(yWorld,mCreateY0) );
								
					break;
				case Line:
					mCreateObject->setSize( xWorld - mCreateX0, yWorld - mCreateY0 );
					break;
				default:
					// Should not happen!
					Q_ASSERT_X( false, "View::::mouseMoveEvent", "Invalid creation mode" );
					break;
				}
			}
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
		 * Transform to label coordinates
		 */
		QTransform transform;

		transform.scale( mScale, mScale );
		transform.translate( mX0, mY0 );

		QPointF pWorld = transform.inverted().map( event->posF() );
		double xWorld = pWorld.x();
		double yWorld = pWorld.y();

		
		if ( event->button() & Qt::LeftButton )
		{
			//
			// LEFT BUTTON Release
			//
			
			if ( !mInObjectCreateMode )
			{
				///
				/// NORMAL MODE
				///
				
				switch (mState)
				{

				case ArrowResize:
					mState = IdleState;
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
					mState = IdleState;
					break;

				}
				
			}
			else
			{
				//
				// OBJECT CREATION MODE
				//

				if ( (fabs(mCreateObject->w()) < 4) && (fabs(mCreateObject->h()) < 4) )
				{
					switch (mCreateObjectType)
					{
					case Text:
						mCreateObject->setSize( 0, 0 );
						break;
					case Line:
						mCreateObject->setSize( 72, 0 );
						break;
					default:
						mCreateObject->setSize( 72, 72 );
						break;
					}
				}
				
				arrowMode();
			}
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
/// Handle resize motion
///
void
glabels::View::handleResizeMotion( double xWorld, double yWorld )
{
	QPointF p( xWorld, yWorld );
	Handle::Location location = mResizeHandle->location();
	
	/*
	 * Change to item relative coordinates
	 */
	p -= QPointF( mResizeObject->x0(), mResizeObject->y0() );
	p = mResizeObject->matrix().map( p );

	/*
	 * Initialize origin and 2 corners in object relative coordinates.
	 */
	double x0 = 0.0;
	double y0 = 0.0;

	double x1 = 0.0;
	double y1 = 0.0;

	double x2 = mResizeObject->w();
	double y2 = mResizeObject->h();

	/*
	 * Calculate new size
	 */
	double w, h;
	switch ( location )
	{
	case Handle::NW:
		w = std::max( x2 - p.x(), 0.0 );
		h = std::max( y2 - p.y(), 0.0 );
		break;
	case Handle::N:
		w = x2 - x1;
		h = std::max( y2 - p.y(), 0.0 );
		break;
	case Handle::NE:
		w = std::max( p.x() - x1, 0.0 );
		h = std::max( y2 - p.y(), 0.0 );
		break;
	case Handle::E:
		w = std::max( p.x() - x1, 0.0 );
		h = y2 - y1;
		break;
	case Handle::SE:
		w = std::max( p.x() - x1, 0.0 );
		h = std::max( p.y() - y1, 0.0 );
		break;
	case Handle::S:
		w = x2 - x1;
		h = std::max( p.y() - y1, 0.0 );
		break;
	case Handle::SW:
		w = std::max( x2 - p.x(), 0.0 );
		h = std::max( p.y() - y1, 0.0 );
		break;
	case Handle::W:
		w = std::max( x2 - p.x(), 0.0 );
		h = y2 - y1;
		break;
	case Handle::P1:
		x1 = p.x();
		y1 = p.y();
		w  = x2 - p.x();
		h  = y2 - p.y();
		x0 = x0 + x1;
		y0 = y0 + y1;
		break;
	case Handle::P2:
		w  = p.x() - x1;
		h  = p.y() - y1;
		x0 = x0 + x1;
		y0 = y0 + y1;
		break;
	default:
		Q_ASSERT_X( false, "View::handleResizeMotion", "Invalid Handle Location" );
	}

	/*
	 * Set size
	 */
	if ( !(location == Handle::P1) && !(location == Handle::P2) )
	{
		if ( mResizeHonorAspect )
		{
			mResizeObject->setSizeHonorAspect( w, h );
		}
		else
		{
			mResizeObject->setSize( w, h );
		}

		/*
		 * Adjust origin, if needed.
		 */
		switch ( location )
		{
		case Handle::NW:
			x0 += x2 - mResizeObject->w();
			y0 += y2 - mResizeObject->h();
			break;
		case Handle::N:
		case Handle::NE:
			y0 += y2 - mResizeObject->h();
			break;
		case Handle::W:
		case Handle::SW:
			x0 += x2 - mResizeObject->w();
			break;
		defaule:
			break;
		}
	}
	else
	{
		mResizeObject->setSize( w, h );
	}

	/*
	 * Put new origin back into world coordinates and set.
	 */
	QTransform inverseMatrix = mResizeObject->matrix().inverted();
	QPointF p0( x0, y0 );
	p0 = inverseMatrix.map( p0 );
	p0 += QPointF( mResizeObject->x0(), mResizeObject->y0() );
	mResizeObject->setPosition( p0.x(), p0.y() );
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

		painter.setRenderHint( QPainter::Antialiasing, true );
		painter.setRenderHint( QPainter::TextAntialiasing, true );
		painter.setRenderHint( QPainter::SmoothPixmapTransform, true );
		
		/* Fill background before any transformations */
		painter.setBrush( QBrush( backgroundColor ) );
		painter.setPen( Qt::NoPen );
		painter.drawRect( rect() );

		/* Transform. */
		painter.scale( mScale, mScale );
		painter.translate( mX0, mY0 );

		/* Now draw from the bottom layer up. */
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

	painter->translate( shadowOffsetPixels/mScale, shadowOffsetPixels/mScale );

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
