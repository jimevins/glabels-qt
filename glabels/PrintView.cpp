/*  PrintView.cpp
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

#include "PrintView.h"

#include "LabelModel.h"

#include <QtDebug>


namespace glabels
{

	///
	/// Constructor
	///
	PrintView::PrintView( QWidget *parent )
		: QWidget(parent), mModel(0), mBlocked(false)
	{
		setupUi( this );

		preview->setRenderer( &mRenderer );
	}


	///
	/// Set Model
	///
	void PrintView::setModel( LabelModel* model )
	{
		int nLabelsPerPage = model->frame()->nLabels();

		mModel = model;

		// TODO set visibility based on merge selection
		copiesBox->setVisible( true );
		mergeBox->setVisible( false );
		
		connect( mModel, SIGNAL(sizeChanged()), this, SLOT(onLabelSizeChanged()) );
		connect( mModel, SIGNAL(changed()), this, SLOT(onLabelChanged()) );

		onLabelSizeChanged();
		onFormChanged();
	}


	///
	/// Label size changed handler
	///
	void PrintView::onLabelSizeChanged()
	{
		preview->setModel( mModel );
		mRenderer.setModel( mModel );
	}


	///
	/// Label changed handler
	///
	void PrintView::onLabelChanged()
	{
		preview->update();
	}


	///
	/// Form changed handler
	///
	void PrintView::onFormChanged()
	{
		if ( !mBlocked )
		{
			mBlocked = true;
			
			int nLabelsPerPage = mModel->frame()->nLabels();
			copiesFromSpin->setRange( 1, nLabelsPerPage );
			copiesToSpin->setRange( copiesFromSpin->value(), nLabelsPerPage );

			// TODO select between simple and merge
			if ( copiesSheetsRadio->isChecked() )
			{
				mRenderer.setNLabels( copiesSheetsSpin->value()*nLabelsPerPage );
				mRenderer.setStartLabel( 0 );
				copiesFromSpin->setValue( 1 );
				copiesToSpin->setValue( nLabelsPerPage );
			}
			else
			{
				mRenderer.setNLabels( copiesToSpin->value() - copiesFromSpin->value() + 1 );
				mRenderer.setStartLabel( copiesFromSpin->value() - 1 );
				copiesSheetsSpin->setValue( 1 );
			}

			mRenderer.setPrintOutlines( printOutlinesCheck->isChecked() );
			mRenderer.setPrintCropMarks( printCropMarksCheck->isChecked() );
			mRenderer.setPrintReverse( printReverseCheck->isChecked() );

			pageSpin->setRange( 1, mRenderer.nPages() );
			nPagesLabel->setText( QString::number( mRenderer.nPages() ) );

			mRenderer.setIPage( pageSpin->value() - 1 );

			preview->update();

			mBlocked = false;
		}
	}


	///
	/// Print Button Clicked handler
	///
	void PrintView::onPrintButtonClicked()
	{
		qDebug() << "Print!";
	}

}
