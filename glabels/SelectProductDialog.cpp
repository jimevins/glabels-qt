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

#include <iostream>

#include "libglabels/Db.h"
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

		// TODO: Set default based on locale and/or saved preferences
		//       Perhaps move to checkboxes
		pageSizeIsoCheck->setChecked( false );
		pageSizeUsCheck->setChecked( true );
		pageSizeOtherCheck->setChecked( true );

		QList<libglabels::Template*> tmplates = libglabels::Db::templates();
		templatePicker->setTemplates( tmplates );

		templatePicker->applyFilter( searchEntry->text(),
					     pageSizeIsoCheck->isChecked(),
					     pageSizeUsCheck->isChecked(),
					     pageSizeOtherCheck->isChecked() );
	}

	///
	/// Get selected template
	///
	const libglabels::Template* SelectProductDialog::tmplate() const
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
	/// Search Entry Text Changed Slot
	///
	void SelectProductDialog::onSearchEntryTextChanged()
	{
		templatePicker->applyFilter( searchEntry->text(),
					     pageSizeIsoCheck->isChecked(),
					     pageSizeUsCheck->isChecked(),
					     pageSizeOtherCheck->isChecked() );
	}


        ///
	/// Search Entry Text Changed Slot
	///
	void SelectProductDialog::onSearchClearButtonClicked()
	{
		searchEntry->setText( "" );
	}


	///
	/// Page Size Check Toggled Slot
	///
	void SelectProductDialog::onPageSizeCheckToggled()
	{
		templatePicker->applyFilter( searchEntry->text(),
					     pageSizeIsoCheck->isChecked(),
					     pageSizeUsCheck->isChecked(),
					     pageSizeOtherCheck->isChecked() );
	}


	///
	/// Template Picker Selection Changed Slot
	///
	void SelectProductDialog::onTemplatePickerSelectionChanged()
	{
		const libglabels::Template *tmplate = templatePicker->selectedTemplate();

		selectButton->setEnabled( tmplate != NULL );
	}


	///
	/// Select Button Clicked Slot
	///
	void SelectProductDialog::onSelectButtonClicked()
	{
		close();
	}


	///
	/// Cancel Button Clicked Slot
	///
	void SelectProductDialog::onCancelButtonClicked()
	{
		mCanceled = true;
		close();
	}

}
