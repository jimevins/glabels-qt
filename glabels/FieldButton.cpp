/*  FieldButton.cpp
 *
 *  Copyright (C) 2014  Jim Evins <evins@snaught.com>
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


namespace glabels
{

	///
	/// Constructor
	///
	FieldButton::FieldButton( QWidget* parent )
		: QPushButton(parent)
	{
		setEnabled( false );

		mMenu = new FieldMenu();
		setMenu( mMenu );

		connect( mMenu, SIGNAL(keySelected(const QString&)), this, SLOT(onMenuKeySelected(const QString&)) );
	}


	void FieldButton::setName( const QString& name )
	{
		if ( name.isNull() || name.isEmpty() )
		{
			setText( tr("(None)") );
			mLabelIsKey = false;
		}
		else
		{
			setText( name );
			mLabelIsKey = true;
		}
	}


	void FieldButton::setKeys( const QList<QString>& keyList )
	{
		mMenu->setKeys( keyList );

		if ( keyList.length() > 0 )
		{
			mKey = keyList.first();

			if ( mLabelIsKey )
			{
				setText( mKey );
			}
			else
			{
				setText( tr("(None)") );
			}

			setEnabled( true );
		}
		else
		{
			setEnabled( false );
		}
	}


	void FieldButton::clearKeys()
	{
		if ( !mLabelIsKey )
		{
			setText( tr("(None)") );
		}

		setEnabled( false );
	}



	///
	/// key getter
	///
	QString FieldButton::key() const
	{
		return mKey;
	}


	///
	/// onMenuKeySelected slot
	///
	void FieldButton::onMenuKeySelected( const QString& key )
	{
		mKey = key;

		if ( mLabelIsKey )
		{
			setText( key );
		}

		emit keySelected( key );
	}


}

