/*  PreferencesDialog.cpp
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

#include "PreferencesDialog.h"

#include "Settings.h"


namespace glabels
{

	///
	/// Constructor
	///
	PreferencesDialog::PreferencesDialog( QWidget *parent )
		: QDialog(parent)
	{
		setupUi( this );

		switch ( Settings::units().toEnum() )
		{
		case Units::IN:
			unitsInchesRadio->setChecked( true );
			break;
		case Units::MM:
			unitsMillimetersRadio->setChecked( true );
			break;
		case Units::CM:
			unitsCentimetersRadio->setChecked( true );
			break;
		case Units::PC:
			unitsPicasRadio->setChecked( true );
			break;
		default:
			unitsPointsRadio->setChecked( true );
			break;
		}
	}


	///
	/// Units Radios Changed
	///
	void PreferencesDialog::onUnitsRadiosChanged()
	{
		if ( unitsInchesRadio->isChecked() )
		{
			Settings::setUnits( Units::in() );
		}
		else if ( unitsMillimetersRadio->isChecked() )
		{
			Settings::setUnits( Units::mm() );
		}
		else if ( unitsCentimetersRadio->isChecked() )
		{
			Settings::setUnits( Units::cm() );
		}
		else if ( unitsPicasRadio->isChecked() )
		{
			Settings::setUnits( Units::pc() );
		}
		else
		{
			Settings::setUnits( Units::pt() );
		}
	}

} // namespace glabels
