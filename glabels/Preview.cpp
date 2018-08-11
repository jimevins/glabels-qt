/*  Preview.cpp
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
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

#include "Preview.h"

#include "PreviewOverlayItem.h"
#include "RollTemplatePath.h"

#include <QGraphicsDropShadowEffect>
#include <QGraphicsRectItem>
#include <QtDebug>


namespace glabels
{

	//
	// Private
	//
	namespace
	{
		const QColor  paperColor( 242, 242, 242 );
		const QColor  paperOutlineColor( 0, 0, 0 );
		const double  paperOutlineWidthPixels = 1;

		const QColor  shadowColor( 64, 64, 64 );
		const double  shadowOffsetPixels = 3;
		const double  shadowRadiusPixels = 12;

		const QColor  labelColor( 255, 255, 255 );
		const QColor  labelOutlineColor( 128, 128, 128 );
		const double  labelOutlineWidthPixels = 2;
	}


	///
	/// Constructor
	///
	Preview::Preview( QWidget *parent )
		: QGraphicsView(parent), mModel(nullptr), mRenderer(nullptr)
	{
		mScene = new QGraphicsScene();
		setScene( mScene );

		setAttribute(Qt::WA_TranslucentBackground);
		viewport()->setAutoFillBackground(false);

		setFrameStyle( QFrame::NoFrame );
		setRenderHints( QPainter::Antialiasing );
	}


	///
	/// Set renderer
	///
	void Preview::setRenderer( const model::PageRenderer* renderer )
	{
		mRenderer = renderer;

		connect( mRenderer, SIGNAL(changed()), this, SLOT(onRendererChanged()) );
		onRendererChanged();
	}


	///
	/// Renderer changed handler
	///
	void Preview::onRendererChanged()
	{
		mModel = mRenderer->model();

		clearScene();

		if ( mModel != nullptr )
		{
			auto tmplate = mModel->tmplate();

			// For "Roll" templates, allow extra room to draw continuation break lines.
			model::Distance drawHeight = mModel->tmplate()->pageHeight();
			model::Distance drawOffset = 0;
			if ( tmplate->isRoll() )
			{
				drawHeight = 1.2 * tmplate->pageHeight();
				drawOffset = 0.1 * tmplate->pageHeight();
			}
			
			// Set scene up with a 5% margin around paper
			model::Distance x = -0.05 * tmplate->pageWidth();
			model::Distance y = -0.05 * drawHeight - drawOffset;
			model::Distance w = 1.10 * tmplate->pageWidth();
			model::Distance h = 1.10 * drawHeight;

			mScene->setSceneRect( x.pt(), y.pt(), w.pt(), h.pt() );
			fitInView( mScene->sceneRect(), Qt::KeepAspectRatio );

			drawPaper();
			drawLabels();
			drawPreviewOverlay();
		}
	}


	///
	/// Resize Event Handler
	///
	void Preview::resizeEvent( QResizeEvent* event )
	{
		fitInView( mScene->sceneRect(), Qt::KeepAspectRatio );
	}


	///
	/// Clear View
	///
	void Preview::clearScene()
	{
		foreach ( QGraphicsItem *item, mScene->items() )
		{
			mScene->removeItem( item );
			delete item;
		}
	}


	///
	/// Draw Paper
	///
	void Preview::drawPaper()
	{
		auto *shadowEffect = new QGraphicsDropShadowEffect();
		shadowEffect->setColor( shadowColor );
		shadowEffect->setOffset( shadowOffsetPixels );
		shadowEffect->setBlurRadius( shadowRadiusPixels );

		QBrush brush( paperColor );
		QPen pen( paperOutlineColor );
		pen.setCosmetic( true );
		pen.setWidthF( paperOutlineWidthPixels );

		QAbstractGraphicsShapeItem* pageItem;
		auto tmplate = mModel->tmplate();
		if ( !tmplate->isRoll() )
		{
			pageItem = new QGraphicsRectItem( 0, 0, tmplate->pageWidth().pt(), tmplate->pageHeight().pt() );
		}
		else
		{
			pageItem = new QGraphicsPathItem( RollTemplatePath( tmplate ) );
		}
		pageItem->setBrush( brush );
		pageItem->setPen( pen );
		pageItem->setGraphicsEffect( shadowEffect );
				
		mScene->addItem( pageItem );
	}


	///
	/// Draw Labels on Paper
	///
	void Preview::drawLabels()
	{
		model::Frame *frame = mModel->tmplate()->frames().first();

		foreach (model::Point origin, frame->getOrigins() )
		{
			drawLabel( origin.x(), origin.y(), frame->path() );
		}
	}


	///
	/// Draw a Single Label at x,y
	///
	void Preview::drawLabel( const model::Distance& x, const model::Distance& y, const QPainterPath& path )
	{
		QBrush brush( labelColor );
		QPen pen( labelOutlineColor );
		pen.setStyle( Qt::DotLine );
		pen.setCosmetic( true );
		pen.setWidthF( labelOutlineWidthPixels );

		auto *labelOutlineItem  = new QGraphicsPathItem( path );
		labelOutlineItem->setBrush( brush );
		labelOutlineItem->setPen( pen );
		labelOutlineItem->setPos( x.pt(), y.pt() );

		mScene->addItem( labelOutlineItem );
	}


	///
	/// Draw Preview Overlay
	///
	void Preview::drawPreviewOverlay()
	{
		if ( mRenderer )
		{
			auto* overlayItem = new PreviewOverlayItem( mRenderer );
			mScene->addItem( overlayItem );
		}
	}

} // namespace glabels
