/*  PageRenderer.cpp
 *
 *  Copyright (C) 2013-2014  Jim Evins <evins@snaught.com>
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

#include "PageRenderer.h"

#include "LabelModel.h"
#include "MergeRecord.h"

#include <QPainter>
#include <QtDebug>


namespace
{
	const QColor labelOutlineColor( 0, 0, 0 );
	const double labelOutlineWidth = 0.25;
	const double tickOffset = 2.25;
	const double tickLength = 18;
}


PageRenderer::PageRenderer()
	: mModel(0), mNLabels(0), mStartLabel(0),
	  mPrintOutlines(false), mPrintCropMarks(false), mPrintReverse(false),
	  mIPage(0), mNPages(0)
{
}


void PageRenderer::setModel( const LabelModel* model )
{
	mModel = model;
	mOrigins = mModel->frame()->getOrigins();
	mNLabelsPerPage = mModel->frame()->nLabels();
	updateNPages();
}

	
void PageRenderer::setNLabels( int nLabels )
{
	mNLabels = nLabels;
	updateNPages();
}

	
void PageRenderer::setStartLabel( int startLabel )
{
	mStartLabel = startLabel;
	updateNPages();
}

	
void PageRenderer::setPrintOutlines( bool printOutlinesFlag )
{
	mPrintOutlines = printOutlinesFlag;
}

	
void PageRenderer::setPrintCropMarks( bool printCropMarksFlag )
{
	mPrintCropMarks = printCropMarksFlag;
}

	
void PageRenderer::setPrintReverse( bool printReverseFlag )
{
	mPrintReverse = printReverseFlag;
}

	
void PageRenderer::setIPage( int iPage )
{
	mIPage = iPage;
}

	
int PageRenderer::nPages() const
{
	return mNPages;
}
			
	
QRectF PageRenderer::pageRect() const
{
	if ( mModel )
	{
		return QRectF( 0, 0, mModel->tmplate()->pageWidth().pt(), mModel->tmplate()->pageHeight().pt() );
	}
	else
	{
		return QRectF( 0, 0, 0, 0 );
	}
}
			
	
void PageRenderer::updateNPages()
{
	if ( mModel )
	{
		/// @TODO merge case
			
		int lastLabel = mStartLabel + mNLabels;
			
		mNPages = lastLabel / mNLabelsPerPage;
		if ( lastLabel % mNLabelsPerPage )
		{
			mNPages++;
		}
	}
	else
	{
		mNPages = 0;
	}
}

	
///
/// Print page using persistent page number
///
void PageRenderer::printPage( QPainter* painter ) const
{
	printPage( painter, mIPage );
}


///
/// Print page
///
void PageRenderer::printPage( QPainter* painter, int iPage ) const
{
	if ( mModel )
	{
		/// @TODO merge case
		
		printSimplePage( painter, iPage );
	}
}


void PageRenderer::printSimplePage( QPainter* painter, int iPage ) const
{
	int iStart = 0;
	int iEnd = mNLabelsPerPage;

	if ( iPage == 0 )
	{
		iStart = mStartLabel;
	}

	int lastLabel = mStartLabel + mNLabels;
	if ( (lastLabel / mNLabelsPerPage) == iPage )
	{
		iEnd = lastLabel % mNLabelsPerPage;
	}

	printCropMarks( painter );

	for ( int i = iStart; i < iEnd; i++ )
	{
		painter->save();

		painter->translate( mOrigins[i].x().pt(), mOrigins[i].y().pt() );
			
		painter->save();

		clipLabel( painter );
		printLabel( painter, 0 );

		painter->restore();  // From before clip

		printOutline( painter );
			
		painter->restore();  // From before translation
	}
}

	
void PageRenderer::printMergePage( QPainter* painter, int iPage ) const
{
	/// @TODO merge case
}
	
	
void PageRenderer::printCropMarks( QPainter* painter ) const
{
	using namespace glabels;
	
	if ( mPrintCropMarks )
	{
		painter->save();

		painter->setBrush( QBrush( Qt::NoBrush ) );
		painter->setPen( QPen( labelOutlineColor, labelOutlineWidth ) );

		Distance w = mModel->frame()->w();
		Distance h = mModel->frame()->h();

		foreach ( Layout* layout, mModel->frame()->layouts() )
		{
			Distance xMin = layout->x0();
			Distance yMin = layout->y0();
			Distance xMax = layout->x0() + layout->dx()*(layout->nx()-1) + w;
			Distance yMax = layout->y0() + layout->dy()*(layout->ny()-1) + h;

			for ( int ix = 0; ix < layout->nx(); ix++ )
			{
				Distance x1 = xMin + ix*layout->dx();
				Distance x2 = x1 + w;

				Distance y1 = max( yMin-tickOffset, Distance::pt(0) );
				Distance y2 = max( y1-tickLength, Distance::pt(0) );

				Distance y3 = min( yMax+tickOffset, mModel->tmplate()->pageHeight() );
				Distance y4 = min( y3+tickLength, mModel->tmplate()->pageHeight() );

				painter->drawLine( x1.pt(), y1.pt(), x1.pt(), y2.pt() );
				painter->drawLine( x2.pt(), y1.pt(), x2.pt(), y2.pt() );
				painter->drawLine( x1.pt(), y3.pt(), x1.pt(), y4.pt() );
				painter->drawLine( x2.pt(), y3.pt(), x2.pt(), y4.pt() );
			}

			for ( int iy = 0; iy < layout->ny(); iy++ )
			{
				Distance y1 = yMin + iy*layout->dy();
				Distance y2 = y1 + h;

				Distance x1 = max( xMin-tickOffset, Distance::pt(0) );
				Distance x2 = max( x1-tickLength, Distance::pt(0) );

				Distance x3 = min( xMax+tickOffset, mModel->tmplate()->pageWidth() );
				Distance x4 = min( x3+tickLength, mModel->tmplate()->pageWidth() );

				painter->drawLine( x1.pt(), y1.pt(), x2.pt(), y1.pt() );
				painter->drawLine( x1.pt(), y2.pt(), x2.pt(), y2.pt() );
				painter->drawLine( x3.pt(), y1.pt(), x4.pt(), y1.pt() );
				painter->drawLine( x3.pt(), y2.pt(), x4.pt(), y2.pt() );
			}
		}

		painter->restore();
	}
}

	
void PageRenderer::printOutline( QPainter* painter ) const
{
	if ( mPrintOutlines )
	{
		painter->save();

		painter->setBrush( QBrush( Qt::NoBrush ) );
		painter->setPen( QPen( labelOutlineColor, labelOutlineWidth ) );

		painter->drawPath( mModel->frame()->path() );
			
		painter->restore();
	}
}

	
void PageRenderer::clipLabel( QPainter* painter ) const
{
	painter->setClipPath( mModel->frame()->clipPath() );
}

	
void PageRenderer::printLabel( QPainter* painter, MergeRecord* record ) const
{
	painter->save();

	if ( mModel->rotate() )
	{
		painter->rotate( -90.0 );
		painter->translate( -mModel->w().pt(), 0 );
	}

	if ( mPrintReverse )
	{
		painter->translate( mModel->w().pt(), 0 );
		painter->scale( -1, 1 );
	}

	mModel->draw( painter, false, record );

	painter->restore();
}
