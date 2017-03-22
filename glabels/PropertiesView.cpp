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


#include <QStyledItemDelegate>
#include <QtDebug>

#include "Db.h"
#include "LabelModel.h"
#include "SelectProductDialog.h"
#include "Settings.h"
#include "UndoRedoModel.h"


namespace glabels
{

	///
	/// Constructor
	///
	PropertiesView::PropertiesView( QWidget *parent )
		: QWidget(parent), mModel(nullptr)
	{
		setupUi( this );

		titleLabel->setText( QString( "<span style='font-size:18pt;'>%1</span>" ).arg( tr("Properties") ) );

		// Hack to get orientationCombo item height to follow icon size plus padding 
		QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
		orientationCombo->setItemDelegate( itemDelegate );
		orientationCombo->setStyleSheet( "* QAbstractItemView::item { padding: 8px; }" );

		similarBrowser->setAttribute(Qt::WA_TranslucentBackground);
		similarBrowser->viewport()->setAutoFillBackground(false);

		connect( Settings::instance(), SIGNAL(changed()),
		         this, SLOT(onSettingsChanged()) );
		
		onSettingsChanged();
	}


	///
	/// Destructor
	///
	PropertiesView::~PropertiesView()
	{
		// empty
	}


	///
	/// Set Model
	///
	void PropertiesView::setModel( LabelModel* model, UndoRedoModel* undoRedoModel )
	{
		mModel = model;
		mUndoRedoModel = undoRedoModel;

		connect( mModel, SIGNAL(sizeChanged()), this, SLOT(onLabelSizeChanged()) );

		onLabelSizeChanged();
	}


	///
	/// Settings changed handler
	///
	void PropertiesView::onSettingsChanged()
	{
		mUnits = Settings::units();
		if (mModel)
		{
			onLabelSizeChanged();
		}
	}


	///
	/// Label size changed handler
	///
	void PropertiesView::onLabelSizeChanged()
	{
		const Template *tmplate   = mModel->tmplate();
		const Frame    *frame     = tmplate->frames().first();
		bool            isRotated = mModel->rotate();

		preview->setTemplate( tmplate );
		preview->setRotate( isRotated );

		const Vendor *vendor = Db::lookupVendorFromName( tmplate->brand() );
		if ( (vendor != nullptr) && (vendor->url() != nullptr) )
		{
			QString markup = QString( "<a href='%1'>%2</a>" )
				.arg( vendor->url() ).arg( vendor->name() );
			vendorLabel->setText( markup );
		}
		else
		{
			vendorLabel->setText( tmplate->brand() );
		}

		if ( tmplate->productUrl() != nullptr )
		{
			QString markup = QString( "<a href='%1'>%2</a>" )
				.arg( tmplate->productUrl() ).arg( tmplate->part() );
			partLabel->setText( markup );
		}
		else
		{
			partLabel->setText( tmplate->part() );
		}

		descriptionLabel->setText( tmplate->description() );

		QString pgSizeString = Db::lookupPaperNameFromId( tmplate->paperId() );
		pageSizeLabel->setText( pgSizeString );

		QString labelSizeString = frame->sizeDescription( mUnits );
		labelSizeLabel->setText( labelSizeString );

		QString layoutString = frame->layoutDescription();
		layoutLabel->setText( layoutString );

		QStringList list = Db::getNameListOfSimilarTemplates( tmplate->name() );
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
		mOldOrientationIndex = orientationCombo->currentIndex();
	}


	///
	/// Orientation combo box changed handler
	///
	void PropertiesView::onOrientationActivated()
	{
		const Template *tmplate = mModel->tmplate();
		const Frame    *frame   = tmplate->frames().first();

		// Make sure index actually changed.
		int index = orientationCombo->currentIndex();
		if ( index != mOldOrientationIndex )
		{
			mOldOrientationIndex = index;

			mUndoRedoModel->checkpoint( tr("Product Rotate") );

			if ( frame->w() == frame->h() )
			{
				mModel->setRotate( false );
			}
			else if ( frame->w() > frame->h() )
			{
				mModel->setRotate( index == 1 );
			}
			else
			{
				mModel->setRotate( index == 0 );
			}
		}
	}


	///
	/// Change Product Button Clicked handler
	///
	void PropertiesView::onChangeProductButtonClicked()
	{
		SelectProductDialog selectProductDialog( this );
		selectProductDialog.exec();

		const Template* tmplate = selectProductDialog.tmplate();
		if ( tmplate )
		{
			mUndoRedoModel->checkpoint( tr("Change Product") );

			mModel->setTmplate( tmplate );

			// Don't rotate circular or round labels
			const Frame *frame = tmplate->frames().first();
			if ( frame->w() == frame->h() )
			{
				mModel->setRotate( false );
			}
		}
	}

}
