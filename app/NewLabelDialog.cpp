/*  NewLabelDialog.cpp
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

#include "NewLabelDialog.h"

#include "libglabels/Db.h"
#include "TemplatePickerItem.h"


namespace gLabels
{

	NewLabelDialog::NewLabelDialog( QWidget *parent = 0 )
	{
		setupUi( this );

		// TODO: Set default based on locale
		pageSizeIsoRadio->setChecked( true );

		QList<libglabels::Template*> tmplates = libglabels::Db::templates();
		templatePicker->setTemplates( tmplates );

		templatePicker->applyFilter( searchEntry->text(),
					     pageSizeIsoRadio->isChecked(),
					     pageSizeUsRadio->isChecked(),
					     pageSizeOtherRadio->isChecked() );

		similarBrowser->setAttribute(Qt::WA_TranslucentBackground);
		similarBrowser->viewport()->setAutoFillBackground(false);

		selectionStackedWidget->setCurrentIndex( 0 );

		connect( searchEntry, SIGNAL(textChanged(const QString &)),
			 this, SLOT(searchEntryTextChanged(const QString &)) );

		connect( pageSizeIsoRadio, SIGNAL(toggled(bool)), this, SLOT(pageSizeRadioToggled(bool)) );
		connect( pageSizeUsRadio, SIGNAL(toggled(bool)), this, SLOT(pageSizeRadioToggled(bool)) );
		connect( pageSizeOtherRadio, SIGNAL(toggled(bool)), this, SLOT(pageSizeRadioToggled(bool)) );

		connect( templatePicker, SIGNAL(itemSelectionChanged()), this, SLOT(templatePickerSelectionChanged()) );
	}


	void NewLabelDialog::searchEntryTextChanged( const QString &text )
	{
		templatePicker->applyFilter( text,
					     pageSizeIsoRadio->isChecked(),
					     pageSizeUsRadio->isChecked(),
					     pageSizeOtherRadio->isChecked() );
	}


	void NewLabelDialog::pageSizeRadioToggled( bool checked )
	{
		if ( checked )
		{
			templatePicker->applyFilter( searchEntry->text(),
						     pageSizeIsoRadio->isChecked(),
						     pageSizeUsRadio->isChecked(),
						     pageSizeOtherRadio->isChecked() );
		}
	}


	void NewLabelDialog::templatePickerSelectionChanged()
	{
		QList<QListWidgetItem *> selectedItems = templatePicker->selectedItems();

		if ( selectedItems.isEmpty() )
		{
			selectionStackedWidget->setCurrentIndex( 0 );
		}
		else
		{
			selectionStackedWidget->setCurrentIndex( 1 );

			// Set template to preview
			TemplatePickerItem *tItem = dynamic_cast<TemplatePickerItem*>(selectedItems.first());
			const libglabels::Template *tmplate = tItem->tmplate();
			const libglabels::Frame *frame = tmplate->frames().first();

			simplePreview->setTemplate( tmplate );

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

			QString labelSizeString = frame->sizeDescription( libglabels::Units::inch() );
			labelSizeLabel->setText( labelSizeString );

			QString layoutString = frame->layoutDescription();
			layoutLabel->setText( layoutString );

			QStringList list = libglabels::Db::getNameListOfSimilarTemplates( tmplate->name() );
			if ( list.isEmpty() )
			{
				similarLabel->hide();
				similarBrowser->hide();
			}
			else
			{
				similarLabel->show();
				similarBrowser->show();

				QString similarListString;
				foreach ( QString name, list )
				{
					similarListString += name + "\n";
				}
				similarBrowser->setText( similarListString );
			}
		}
	}

}
