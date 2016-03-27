/*  StartupWizard.h
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

#ifndef StartupWizard_h
#define StartupWizard_h

#include "ui_StartupWizard.h"


///
/// Startup Wizard Dialog Widget
///
class StartupWizard : public QDialog, public Ui_StartupWizard
{
	Q_OBJECT


	/////////////////////////////////
	// Life Cycle
	/////////////////////////////////
public:
	StartupWizard( QWidget *parent = 0 );


	/////////////////////////////////
	// Slots
	/////////////////////////////////
private slots:
	void onNewProjectButtonClicked();
	void onOpenProjectButtonClicked();

};


#endif // StartupWizard_h
