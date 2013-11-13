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

		connect( searchEntry, SIGNAL(textChanged(const QString &)),
			 this, SLOT(searchEntryTextChanged(const QString &)) );

		connect( pageSizeIsoRadio, SIGNAL(toggled(bool)), this, SLOT(pageSizeRadioToggled(bool)) );
		connect( pageSizeUsRadio, SIGNAL(toggled(bool)), this, SLOT(pageSizeRadioToggled(bool)) );
		connect( pageSizeOtherRadio, SIGNAL(toggled(bool)), this, SLOT(pageSizeRadioToggled(bool)) );

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

}
