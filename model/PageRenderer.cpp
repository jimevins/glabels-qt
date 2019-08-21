/*  PageRenderer.cpp
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

#include "PageRenderer.h"

#include "Model.h"

#include "merge/Merge.h"
#include "merge/None.h"
#include "merge/Record.h"

#include <QtDebug>


namespace glabels
{
	namespace model
	{
	
		//
		// Private
		//
		namespace
		{
			const QColor labelOutlineColor( 0, 0, 0 );
			const double labelOutlineWidth = 0.25;
			const double tickOffset = 2.25;
			const double tickLength = 18;
		}


		PageRenderer::PageRenderer( const Model* model )
			: mModel(nullptr), mMerge(nullptr), mVariables(nullptr), mNCopies(0), mStartLabel(0), mLastLabel(0),
			  mPrintOutlines(false), mPrintCropMarks(false), mPrintReverse(false),
			  mIPage(0), mIsMerge(false), mNPages(0), mNLabelsPerPage(0)
		{
			if ( model )
			{
				setModel( model );
			}
		}


		void PageRenderer::setModel( const Model* model )
		{
			mModel = model;

			connect( mModel, SIGNAL(changed()), this, SLOT(onModelChanged()) );
	
			onModelChanged();
			mVariables = mModel->variables();
		}

	
		const Model* PageRenderer::model() const
		{
			return mModel;
		}


		void PageRenderer::onModelChanged()
		{
			mMerge = mModel->merge();
			mOrigins = mModel->frame()->getOrigins();
			mNLabelsPerPage = mModel->frame()->nLabels();
			mIsMerge = ( dynamic_cast<const merge::None*>(mMerge) == nullptr );
			updateNPages();

			emit changed();
		}


		void PageRenderer::setNCopies( int nCopies )
		{
			mNCopies = nCopies;
			updateNPages();

			emit changed();
		}


		void PageRenderer::setStartLabel( int startLabel )
		{
			mStartLabel = startLabel;
			updateNPages();

			emit changed();
		}

	
		void PageRenderer::setPrintOutlines( bool printOutlinesFlag )
		{
			mPrintOutlines = printOutlinesFlag;

			emit changed();
		}

	
		void PageRenderer::setPrintCropMarks( bool printCropMarksFlag )
		{
			mPrintCropMarks = printCropMarksFlag;

			emit changed();
		}

	
		void PageRenderer::setPrintReverse( bool printReverseFlag )
		{
			mPrintReverse = printReverseFlag;

			emit changed();
		}

	
		void PageRenderer::setIPage( int iPage )
		{
			mIPage = iPage;

			emit changed();
		}

	
		int PageRenderer::nItems() const
		{
			return mLastLabel - mStartLabel;
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
				if ( mIsMerge )
				{
					mLastLabel = mStartLabel + mNCopies*mMerge->nSelectedRecords();
				}
				else
				{
					mLastLabel = mStartLabel + mNCopies;
				}
		
				mNPages = mLastLabel / mNLabelsPerPage;
				if ( mLastLabel % mNLabelsPerPage )
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
		/// Print
		///
		void PageRenderer::print( QPrinter* printer ) const
		{
			QSizeF pageSize( mModel->tmplate()->pageWidth().pt(), mModel->tmplate()->pageHeight().pt() );
			printer->setPageSize( QPageSize(pageSize, QPageSize::Point) );
			printer->setFullPage( true );
			printer->setPageMargins( 0, 0, 0, 0, QPrinter::Point );

			QPainter painter( printer );
			
			QRectF rectPx  = printer->paperRect( QPrinter::DevicePixel );
			QRectF rectPts = printer->paperRect( QPrinter::Point );
			painter.scale( rectPx.width()/rectPts.width(), rectPx.height()/rectPts.height() );


			for ( int iPage = 0; iPage < mNPages; iPage++ )
			{
				if ( iPage )
				{
					printer->newPage();
				}

				printPage( &painter, iPage );
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
				if ( mIsMerge )
				{
					printMergePage( painter, iPage );
				}
				else
				{
					printSimplePage( painter, iPage );
				}
			}
		}


		void PageRenderer::printSimplePage( QPainter* painter, int iPage ) const
		{
			printCropMarks( painter );

			int iCopy = 0;
			int iLabel = mStartLabel;
			int iCurrentPage = 0;
			mVariables->resetVariables();

			while ( (iCopy < mNCopies) && (iCurrentPage <= iPage) )
			{
				if ( iCurrentPage == iPage )
				{
					int i = iLabel % mNLabelsPerPage;
					
					painter->save();

					painter->translate( mOrigins[i].x().pt(), mOrigins[i].y().pt() );
			
					painter->save();

					clipLabel( painter );
					printLabel( painter, nullptr, mVariables );

					painter->restore();  // From before clip

					printOutline( painter );
			
					painter->restore();  // From before translation
				}

				iCopy++;
				iLabel++;
				iCurrentPage = iLabel / mNLabelsPerPage;

				mVariables->incrementVariablesOnItem();
				mVariables->incrementVariablesOnCopy();
				if ( (iLabel % mNLabelsPerPage) == 0 /* starting a new page */ )
				{
					mVariables->incrementVariablesOnPage();
				}
			}
		}

	
		void PageRenderer::printMergePage( QPainter* painter, int iPage ) const
		{
			printCropMarks( painter );

			int iCopy = 0;
			int iLabel = mStartLabel;
			int iCurrentPage = 0;

			const QList<merge::Record*> records = mMerge->selectedRecords();
			int iRecord = 0;
			int nRecords = records.size();

			if ( nRecords == 0 )
			{
				return;
			}
			
			mVariables->resetVariables();

			while ( (iCopy < mNCopies) && (iCurrentPage <= iPage) )
			{
				if ( iCurrentPage == iPage )
				{
					int i = iLabel % mNLabelsPerPage;
					
					painter->save();

					painter->translate( mOrigins[i].x().pt(), mOrigins[i].y().pt() );
			
					painter->save();

					clipLabel( painter );
					printLabel( painter, records[iRecord], mVariables );

					painter->restore();  // From before clip

					printOutline( painter );
			
					painter->restore();  // From before translation
				}

				iRecord = (iRecord + 1) % nRecords;
				if ( iRecord == 0 )
				{
					iCopy++;
				}
				iLabel++;
				iCurrentPage = iLabel / mNLabelsPerPage;

				mVariables->incrementVariablesOnItem();
				if ( iRecord == 0 )
				{
					mVariables->incrementVariablesOnCopy();
				}
				if ( (iLabel % mNLabelsPerPage) == 0 /* starting a new page */ )
				{
					mVariables->incrementVariablesOnPage();
				}
			}
		}
	
	
		void PageRenderer::printCropMarks( QPainter* painter ) const
		{
			if ( mPrintCropMarks )
			{
				painter->save();

				painter->setBrush( QBrush( Qt::NoBrush ) );
				painter->setPen( QPen( labelOutlineColor, labelOutlineWidth ) );

				Distance w = mModel->frame()->w();
				Distance h = mModel->frame()->h();

				foreach ( const Layout& layout, mModel->frame()->layouts() )
				{
					Distance xMin = layout.x0();
					Distance yMin = layout.y0();
					Distance xMax = layout.x0() + layout.dx()*(layout.nx()-1) + w;
					Distance yMax = layout.y0() + layout.dy()*(layout.ny()-1) + h;

					for ( int ix = 0; ix < layout.nx(); ix++ )
					{
						Distance x1 = xMin + ix*layout.dx();
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

					for ( int iy = 0; iy < layout.ny(); iy++ )
					{
						Distance y1 = yMin + iy*layout.dy();
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

	
		void PageRenderer::printLabel( QPainter*      painter,
		                               merge::Record* record,
		                               Variables*     variables ) const
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

			mModel->draw( painter, false, record, variables );

			painter->restore();
		}

	}
}
