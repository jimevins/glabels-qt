/*  FieldButton.cpp
 *
 *  Copyright (C) 2014-2016  Jim Evins <evins@snaught.com>
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

#include "FieldButton.h"

#include <QLineEdit>
#include <QStandardItemModel>


namespace glabels
{

	///
	/// Constructor
	///
	FieldButton::FieldButton( QWidget* parent )
		: QComboBox(parent)
	{
		setEnabled( false );

		connect( this, SIGNAL(currentIndexChanged(int)), this, SLOT(onIndexChanged(int)) );
	}


	void FieldButton::setName( const QString& name )
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

		// Item 0 is the ComboBox title, not an item intended for selection. So disable it.
		const auto* itemModel = qobject_cast<const QStandardItemModel*>(model());
		QStandardItem* item = itemModel->item(0);
		item->setFlags( item->flags() & ~(Qt::ItemIsSelectable|Qt::ItemIsEnabled) );
	}


	void FieldButton::setKeys( const QStringList& keyList )
	{
		// Clear old keys
		clear();
		addItem( mName );

		// Item 0 is the ComboBox title, not an item intended for selection. So disable it.
		const auto* itemModel = qobject_cast<const QStandardItemModel*>(model());
		QStandardItem* item = itemModel->item(0);
		item->setFlags( item->flags() & ~(Qt::ItemIsSelectable|Qt::ItemIsEnabled) );
	
		// Add new keys
		if ( keyList.size() > 0 )
		{
			addItems( keyList );
			setEnabled( true );
		}
		else
		{
			setEnabled( false );
		}
	}


	void FieldButton::clearKeys()
	{
		clear();
		addItem( mName );
	
		setEnabled( false );
	}



	///
	/// onMenuKeySelected slot
	///
	void FieldButton::onIndexChanged( int index )
	{
		if ( index > 0 )
		{
			emit keySelected( itemText(index) );

			setCurrentIndex( 0 );
		}
	}

} // namespace glabels
