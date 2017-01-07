/*  PrintView.cpp
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

#include "PrintView.h"


#include <QPrintDialog>
#include <QtDebug>

#include "LabelModel.h"


///
/// Constructor
///
PrintView::PrintView( QWidget *parent )
	: QWidget(parent), mModel(0), mBlocked(false)
{
	setupUi( this );
	preview->setRenderer( &mRenderer );

	mPrinter = new QPrinter( QPrinter::HighResolution );
}


///
/// Destructor
///
PrintView::~PrintView()
{
	delete mPrinter;
}


///
/// Set Model
///
void PrintView::setModel( LabelModel* model )
{
	mModel = model;
	mRenderer.setModel( mModel );

	connect( mModel, SIGNAL(changed()), this, SLOT(onModelChanged()) );

	onFormChanged();
}


///
/// Model changed handler
///
void PrintView::onModelChanged()
{
	updateView();
}


///
/// Update view
///
void PrintView::updateView()
{
	copiesStartSpin->setRange( 1, mModel->frame()->nLabels() );

	copiesDescriptionLabel->setText( tr("(Will print a total of %1 items on %2 pages.)")
					 .arg(mRenderer.nItems()).arg(mRenderer.nPages()) );

	pageSpin->setRange( 1, mRenderer.nPages() );
	nPagesLabel->setText( QString::number( mRenderer.nPages() ) );
}


///
/// Form changed handler
///
void PrintView::onFormChanged()
{
	if ( !mBlocked )
	{
		mBlocked = true;
			
		mRenderer.setNCopies( copiesSpin->value() );
		mRenderer.setStartLabel( copiesStartSpin->value() - 1 );

		mRenderer.setPrintOutlines( printOutlinesCheck->isChecked() );
		mRenderer.setPrintCropMarks( printCropMarksCheck->isChecked() );
		mRenderer.setPrintReverse( printReverseCheck->isChecked() );

		mRenderer.setIPage( pageSpin->value() - 1 );

		updateView();
		
		mBlocked = false;
	}
}


///
/// Print Button Clicked handler
///
void PrintView::onPrintButtonClicked()
{
	QSizeF pageSize( mModel->tmplate()->pageWidth().pt(), mModel->tmplate()->pageHeight().pt() );
	mPrinter->setPaperSize( pageSize, QPrinter::Point );
	mPrinter->setFullPage( true );
	mPrinter->setPageMargins( 0, 0, 0, 0, QPrinter::Point );

	QPrintDialog printDialog( mPrinter, this );

	printDialog.setOption( QAbstractPrintDialog::PrintToFile,        true );
	printDialog.setOption( QAbstractPrintDialog::PrintSelection,     false );
	printDialog.setOption( QAbstractPrintDialog::PrintPageRange,     false );
	printDialog.setOption( QAbstractPrintDialog::PrintShowPageSize,  true );
	printDialog.setOption( QAbstractPrintDialog::PrintCollateCopies, false );
	printDialog.setOption( QAbstractPrintDialog::PrintCurrentPage,   false );

	if ( printDialog.exec() == QDialog::Accepted )
	{
		QPainter painter( mPrinter );
			
		QSizeF sizePx  = mPrinter->paperSize( QPrinter::DevicePixel );
		QSizeF sizePts = mPrinter->paperSize( QPrinter::Point );
		painter.scale( sizePx.width()/sizePts.width(), sizePx.height()/sizePts.height() );

		for ( int iPage = 0; iPage < mRenderer.nPages(); iPage++ )
		{
			if ( iPage )
			{
				mPrinter->newPage();
			}

			mRenderer.printPage( &painter, iPage );
		}
	}
}
