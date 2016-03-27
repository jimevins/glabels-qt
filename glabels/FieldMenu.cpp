/*  FieldMenu.cpp
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

#include "FieldMenu.h"

#include "FieldMenuItem.h"


///
/// Constructor
///
FieldMenu::FieldMenu()
{
}


///
/// set keys
///
void FieldMenu::setKeys( const QList<QString>& keyList )
{
	clear();

	foreach ( QString key, keyList )
	{
		FieldMenuItem* menuItem = new FieldMenuItem( key );
		connect( menuItem, SIGNAL(activated()), this, SLOT(onMenuItemActivated) );

		addAction( menuItem );
	}
}


///
/// onMenuItemActivated slot
///
void FieldMenu::onMenuItemActivated( const QString& key )
{
	emit keySelected( key );
}
