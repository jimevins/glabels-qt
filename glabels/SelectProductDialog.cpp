/*  SelectProductDialog.cpp
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

#include "SelectProductDialog.h"


#include <QtDebug>

#include "Db.h"
#include "Settings.h"
#include "TemplatePickerItem.h"


namespace glabels
{
	
	///
	/// Constructor
	///
	SelectProductDialog::SelectProductDialog( QWidget *parent )
		: QDialog(parent), mCanceled(false)
	{
		setupUi( this );

		pageSizeIsoCheck->setChecked( Settings::searchIsoPaperSizes() );
		pageSizeUsCheck->setChecked( Settings::searchUsPaperSizes() );
		pageSizeOtherCheck->setChecked( Settings::searchOtherPaperSizes() );

		allCategoriesRadio->setChecked( Settings::searchAllCategories() );
		selectedCategoriesRadio->setChecked( !Settings::searchAllCategories() );

		categoriesCheckContainer->setEnabled( !Settings::searchAllCategories() );
		mCategoryIdList = Settings::searchCategoryList();
	
		QList<Category*> categories = Db::categories();
		foreach ( Category *category, categories )
		{
			QCheckBox* check = new QCheckBox( category->name() );
			check->setChecked( mCategoryIdList.contains( category->id() ) );
			categoriesLayout->addWidget( check );

			mCheckToCategoryMap[check] = category->id();

			connect( check, SIGNAL(clicked()), this, SLOT(onCategoryCheckClicked()) );
		}

		QList<Template*> tmplates = Db::templates();
		templatePicker->setTemplates( tmplates );

		if ( Settings::recentTemplateList().count() > 0 )
		{
			modeNotebook->setCurrentIndex(1);
		}

		onModeTabChanged();
	}

	
	///
	/// Get selected template
	///
	const Template* SelectProductDialog::tmplate() const
	{
		if ( !mCanceled )
		{
			return templatePicker->selectedTemplate();
		}
		else
		{
			return 0;
		}
	}


	///
	/// Mode Notebook Tab Changed Slot
	///
	void SelectProductDialog::onModeTabChanged()
	{
		switch (modeNotebook->currentIndex())
		{
		case 0:
			// Search Tab
			templatePicker->applyFilter( searchEntry->text(),
			                             pageSizeIsoCheck->isChecked(),
			                             pageSizeUsCheck->isChecked(),
			                             pageSizeOtherCheck->isChecked(),
			                             allCategoriesRadio->isChecked(),
			                             mCategoryIdList );
			break;
		case 1:
			// Recent Tab
			templatePicker->applyFilter( Settings::recentTemplateList() );
			break;
		default:
			qDebug() << "onModeTabChanged(): unknown tab!";
		}
	}


	///
	/// Search Entry Text Changed Slot
	///
	void SelectProductDialog::onSearchEntryTextChanged()
	{
		templatePicker->applyFilter( searchEntry->text(),
		                             pageSizeIsoCheck->isChecked(),
		                             pageSizeUsCheck->isChecked(),
		                             pageSizeOtherCheck->isChecked(),
		                             allCategoriesRadio->isChecked(),
		                             mCategoryIdList );
	}


	///
	/// Search Entry Text Changed Slot
	///
	void SelectProductDialog::onSearchClearButtonClicked()
	{
		searchEntry->setText( "" );
	}


	///
	/// Page Size Check Clicked Slot
	///
	void SelectProductDialog::onPageSizeCheckClicked()
	{
		Settings::setSearchIsoPaperSizes( pageSizeIsoCheck->isChecked() );
		Settings::setSearchUsPaperSizes( pageSizeUsCheck->isChecked() );
		Settings::setSearchOtherPaperSizes( pageSizeOtherCheck->isChecked() );

		templatePicker->applyFilter( searchEntry->text(),
		                             pageSizeIsoCheck->isChecked(),
		                             pageSizeUsCheck->isChecked(),
		                             pageSizeOtherCheck->isChecked(),
		                             allCategoriesRadio->isChecked(),
		                             mCategoryIdList );
	}


	///
	/// Category Radio Clicked Slot
	///
	void SelectProductDialog::onCategoryRadioClicked()
	{
		categoriesCheckContainer->setEnabled( selectedCategoriesRadio->isChecked() );
		loadCategoryList();

		templatePicker->applyFilter( searchEntry->text(),
		                             pageSizeIsoCheck->isChecked(),
		                             pageSizeUsCheck->isChecked(),
		                             pageSizeOtherCheck->isChecked(),
		                             allCategoriesRadio->isChecked(),
		                             mCategoryIdList );

		Settings::setSearchAllCategories( allCategoriesRadio->isChecked() );
	}


	///
	/// Category Check Clicked Slot
	///
	void SelectProductDialog::onCategoryCheckClicked()
	{
		loadCategoryList();

		templatePicker->applyFilter( searchEntry->text(),
		                             pageSizeIsoCheck->isChecked(),
		                             pageSizeUsCheck->isChecked(),
		                             pageSizeOtherCheck->isChecked(),
		                             allCategoriesRadio->isChecked(),
		                             mCategoryIdList );


		Settings::setSearchCategoryList( mCategoryIdList );
	}


	///
	/// Template Picker Selection Changed Slot
	///
	void SelectProductDialog::onTemplatePickerSelectionChanged()
	{
		// Delay close.  This should make the selection more apparent to the user.
		mTimer.start( 125, this );
	}


	///
	/// Cancel Button Clicked Slot
	///
	void SelectProductDialog::onCancelButtonClicked()
	{
		mCanceled = true;
		close();
	}


	///
	/// Cancel Button Clicked Slot
	///
	void SelectProductDialog::timerEvent( QTimerEvent *event )
	{
		mTimer.stop();
		close();
	}


	///
	/// Load category list
	///
	void SelectProductDialog::loadCategoryList()
	{
		mCategoryIdList.clear();

		foreach( QCheckBox* check, mCheckToCategoryMap.keys() )
		{
			if ( check->isChecked() )
			{
				mCategoryIdList.append( mCheckToCategoryMap[check] );
			}
		}
	}

}
