/*  VariablesView.cpp
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

#include "VariablesView.h"

#include "EditVariableDialog.h"

#include <QtDebug>


namespace glabels
{

	///
	/// Constructor
	///
	VariablesView::VariablesView( QWidget *parent )
		: QWidget(parent), mModel(nullptr), mUndoRedoModel(nullptr)
	{
		setupUi( this );

		titleLabel->setText( QString( "<span style='font-size:18pt;'>%1</span>" ).arg( tr("Variables") ) );
	}


	///
	/// Destructor
	///
	VariablesView::~VariablesView()
	{
		// empty
	}


	///
	/// Set Model
	///
	void VariablesView::setModel( model::Model* model, UndoRedoModel* undoRedoModel )
	{
		mModel = model;
		mUndoRedoModel = undoRedoModel;

		updateControls();
		
		//connect( mModel, SIGNAL(variablesChanged()), this, SLOT(onVariablesChanged()) );
	}


	///
	/// table Selection Changed
	///
	void VariablesView::onTableSelectionChanged()
	{
		updateControls();
	}


	///
	/// addButton Clicked
	///
	void VariablesView::onAddButtonClicked()
	{
		EditVariableDialog dialog( this );

		model::Variable v( model::Variable::TYPE_NUMERIC,
		                   "x",
		                   "0",
		                   model::Variable::INCREMENT_NEVER,
		                   "0" );
		dialog.setVariable( v );

		if ( dialog.exec() == QDialog::Accepted )
		{
			qDebug() << "Add OK.";
		}
	}


	///
	/// editButton Clicked
	///
	void VariablesView::onEditButtonClicked()
	{
	}


	///
	/// deleteButton Clicked
	///
	void VariablesView::onDeleteButtonClicked()
	{
	}


	///
	/// update controls
	///
	void VariablesView::updateControls()
	{
		bool hasSelection = !table->selectedItems().isEmpty();

		editButton->setEnabled( hasSelection );
		deleteButton->setEnabled( hasSelection );
	}


} // namespace glabels
