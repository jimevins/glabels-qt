/*  SelectProductDialog.h
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

#ifndef SelectProductDialog_h
#define SelectProductDialog_h

#include "ui_SelectProductDialog.h"


///
/// New Label Dialog Widget
///
class SelectProductDialog : public QDialog, public Ui_SelectProductDialog
{
	Q_OBJECT


	/////////////////////////////////
	// Life Cycle
	/////////////////////////////////
public:
	SelectProductDialog( QWidget *parent = 0 );


	/////////////////////////////////
	// Accessors
	/////////////////////////////////
	const glabels::Template* tmplate() const;


	/////////////////////////////////
	// Slots
	/////////////////////////////////
private slots:
	void onSearchEntryTextChanged();
	void onSearchClearButtonClicked();
	void onPageSizeCheckToggled();
	void onTemplatePickerSelectionChanged();
	void onSelectButtonClicked();
	void onCancelButtonClicked();

		
	/////////////////////////////////
	// Private data
	/////////////////////////////////
private:
	bool mCanceled;

};


#endif // SelectProductDialog_h
