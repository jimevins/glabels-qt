/*  EditVariableDialog.cpp
 *
 *  Copyright (C) 2019  Jim Evins <evins@snaught.com>
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

#include "EditVariableDialog.h"

#include "model/Settings.h"


namespace glabels
{

	///
	/// Constructor
	///
	EditVariableDialog::EditVariableDialog( QWidget *parent )
		: QDialog(parent)
	{
		setupUi( this );
	}


	///
	/// Set variable
	///
	void EditVariableDialog::setVariable( const model::Variable& variable )
	{
		typeCombo->setCurrentIndex( static_cast<int>(variable.type()) );
		nameEdit->setText( variable.name() );
		valueEdit->setText( variable.value() );
		incrementCombo->setCurrentIndex( static_cast<int>(variable.increment()) );
		stepSizeEdit->setText( variable.stepSize() );

		updateControls();
	}


	///
	/// Get variable
	///
	model::Variable EditVariableDialog::variable() const
	{
		return model::Variable( static_cast<model::Variable::Type>(typeCombo->currentIndex()),
		                        nameEdit->text(),
		                        valueEdit->text(),
		                        static_cast<model::Variable::Increment>(incrementCombo->currentIndex()),
		                        stepSizeEdit->text() );
	}


	///
	/// typeCombo Changed
	///
	void EditVariableDialog::onTypeComboChanged()
	{
		updateControls();
	}

	
	///
	/// valueEdit Changed
	///
	void EditVariableDialog::onValueEditChanged()
	{
	}

	
	///
	/// incrementCombo Changed
	///
	void EditVariableDialog::onIncrementComboChanged()
	{
		updateControls();
	}

	
	///
	/// stepSizeEdit Changed
	///
	void EditVariableDialog::onStepSizeEditChanged()
	{
	}


	///
	/// update controls
	///
	void EditVariableDialog::updateControls()
	{
		model::Variable::Type type = static_cast<model::Variable::Type>(typeCombo->currentIndex());
		model::Variable::Increment increment = static_cast<model::Variable::Increment>(incrementCombo->currentIndex());

		if ( type != model::Variable::Type::NUMERIC )
		{
			incrementCombo->setCurrentIndex( static_cast<int>(model::Variable::Increment::NEVER) );
		}

		if ( increment == model::Variable::Increment::NEVER )
		{
			stepSizeEdit->setText( "0" );
		}
		
		incrementLabel->setEnabled( type == model::Variable::Type::NUMERIC );
		incrementCombo->setEnabled( type == model::Variable::Type::NUMERIC );
		stepSizeLabel->setEnabled( (type == model::Variable::Type::NUMERIC) &&
		                           (increment != model::Variable::Increment::NEVER) );
		stepSizeEdit->setEnabled( (type == model::Variable::Type::NUMERIC) &&
		                          (increment != model::Variable::Increment::NEVER) );
	}
	

} // namespace glabels
