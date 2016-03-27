/*  PropertiesView.cpp
 *
 *  Copyright (C) 2016  Jim Evins <evins@snaught.com>
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

#include "PropertiesView.h"

#include "LabelModel.h"

#include "libglabels/Db.h"
#include "SelectProductDialog.h"
#include <QtDebug>


namespace glabels
{

	///
	/// Constructor
	///
	PropertiesView::PropertiesView( QWidget *parent )
		: QWidget(parent), mModel(0)
	{
		setupUi( this );

		similarBrowser->setAttribute(Qt::WA_TranslucentBackground);
		similarBrowser->viewport()->setAutoFillBackground(false);
	}


	///
	/// Destructor
	///
	PropertiesView::~PropertiesView()
	{
	}


	///
	/// Set Model
	///
	void PropertiesView::setModel( LabelModel* model )
	{
		mModel = model;

		connect( mModel, SIGNAL(sizeChanged()), this, SLOT(onLabelSizeChanged()) );

		onLabelSizeChanged();
	}


	///
	/// Label size changed handler
	///
	void PropertiesView::onLabelSizeChanged()
	{
		const libglabels::Template *tmplate   = mModel->tmplate();
		const libglabels::Frame    *frame     = tmplate->frames().first();
		bool                        isRotated = mModel->rotate();

		preview->setTemplate( tmplate );
		preview->setRotate( isRotated );

		const libglabels::Vendor *vendor = libglabels::Db::lookupVendorFromName( tmplate->brand() );
		if ( (vendor != NULL) && (vendor->url() != NULL) )
		{
			QString markup = "<a href='" + vendor->url() + "'>" + vendor->name() + "</a>";
			vendorLabel->setText( markup );
		}
		else
		{
			vendorLabel->setText( tmplate->brand() );
		}

		if ( tmplate->productUrl() != NULL )
		{
			QString markup = "<a href='" + tmplate->productUrl() + "'>" + tmplate->part() + "</a>";
			partLabel->setText( markup );
		}
		else
		{
			partLabel->setText( tmplate->part() );
		}

		descriptionLabel->setText( tmplate->description() );

		QString pgSizeString = libglabels::Db::lookupPaperNameFromId( tmplate->paperId() );
		pageSizeLabel->setText( pgSizeString );

		QString labelSizeString = frame->sizeDescription( libglabels::Distance::Units::IN );
		labelSizeLabel->setText( labelSizeString );

		QString layoutString = frame->layoutDescription();
		layoutLabel->setText( layoutString );

		QStringList list = libglabels::Db::getNameListOfSimilarTemplates( tmplate->name() );
		if ( list.isEmpty() )
		{
			similarProductsGroupBox->hide();
			similarProductsNullBox->show();
		}
		else
		{
			similarProductsGroupBox->show();
			similarProductsNullBox->hide();

			QString similarListString;
			foreach ( QString name, list )
			{
				similarListString += name + "\n";
			}
			similarBrowser->setText( similarListString );
		}

		orientationCombo->setEnabled( frame->w() != frame->h() );
		if ( frame->w() == frame->h() )
		{
			orientationCombo->setCurrentIndex(0);
		}
		else if ( frame->w() > frame->h() )
		{
			orientationCombo->setCurrentIndex( isRotated ? 1 : 0 );
		}
		else
		{
			orientationCombo->setCurrentIndex( isRotated ? 0 : 1 );
		}
	}


	///
	/// Form changed handler
	///
	void PropertiesView::onFormChanged()
	{
		const libglabels::Template *tmplate = mModel->tmplate();
		const libglabels::Frame    *frame   = tmplate->frames().first();

		if ( frame->w() == frame->h() )
		{
			mModel->setRotate( false );
		}
		else if ( frame->w() > frame->h() )
		{
			int index = orientationCombo->currentIndex();
			mModel->setRotate( index == 1 );
		}
		else
		{
			int index = orientationCombo->currentIndex();
			mModel->setRotate( index == 0 );
		}
	}


	///
	/// Change Product Button Clicked handler
	///
	void PropertiesView::onChangeProductButtonClicked()
	{
		SelectProductDialog selectProductDialog( this );
		selectProductDialog.exec();

		const libglabels::Template* tmplate = selectProductDialog.tmplate();
		if ( tmplate )
		{
			mModel->setTmplate( tmplate );

			// Don't rotate circular or round labels
			const libglabels::Frame *frame = tmplate->frames().first();
			if ( frame->w() == frame->h() )
			{
				mModel->setRotate( false );
			}
		}
	}

}
