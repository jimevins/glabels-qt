/*  FieldCombo.cpp
 *
 *  Copyright (C) 2014-2019  Jim Evins <evins@snaught.com>
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

#include "FieldCombo.h"

#include <QLineEdit>
#include <QStandardItemModel>


namespace glabels
{

	///
	/// Constructor
	///
	FieldCombo::FieldCombo( QWidget* parent )
		: QComboBox(parent)
	{
		connect( this, SIGNAL(currentIndexChanged(int)),
		         this, SLOT(onIndexChanged(int)) );
	}


	///
	/// Is current selection the alternative default selection?
	///
	bool FieldCombo::isCurrentSelectionSpecial() const
	{
		return currentIndex() == 0;
	}
	

	///
	/// Return current selection
	///
	QString FieldCombo::currentSelection() const
	{
		return mFieldNames[ currentIndex() ];
	}

	
	///
	/// Set current selection to special
	///
	void FieldCombo::setCurrentSelectionToSpecial()
	{
		setCurrentIndex( 0 );
	}

	
	///
	/// Set current selection
	///
	void FieldCombo::setCurrentSelection( const QString& key )
	{
		setCurrentText( QString( "${%1}" ).arg( key ) );
	}

	
	///
	/// Set alternative default selection
	///
	void FieldCombo::setSpecialSelectionText( const QString& name )
	{
		mName = name;
		if ( count() == 0 )
		{
			addItem( mName );
		}
		else
		{
			setItemText( 0, mName );
		}
	}


	///
	/// Set field selections
	///
	void FieldCombo::setFieldSelections( const merge::Merge*     merge,
	                                     const model::Variables* variables )
	{
		// Clear old keys
		clear();
		mFieldNames.clear();

		// Add default alt selection
		addItem( mName );
		mFieldNames.append( mName );

		// Add merge fields, if any
		for ( auto& key : merge->keys() )
		{
			addItem( QString( "${%1}" ).arg( key ) );
			mFieldNames.append( key );
		}

		// Add variables, if any
		for ( auto& key : variables->keys() )
		{
			addItem( QString( "${%1}" ).arg( key ) );
			mFieldNames.append( key );
		}
	}


	///
	/// Clear field selections
	///
	void FieldCombo::clearFieldSelections()
	{
		clear();
		mFieldNames.clear();

		addItem( mName );
		mFieldNames.append( mName );
	}


	///
	/// onMenuKeySelected slot
	///
	void FieldCombo::onIndexChanged( int index )
	{
		if ( index >= 0 )
		{
			emit selectionChanged();
		}
	}

	
} // namespace glabels
