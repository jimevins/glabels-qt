/*  FieldMenu.h
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

#ifndef FieldMenu_h
#define FieldMenu_h

#include <QMenu>
#include <QString>


///
/// Field Menu
///
class FieldMenu : public QMenu
{
	Q_OBJECT

	/////////////////////////////////
	// Life Cycle
	/////////////////////////////////
public:
	FieldMenu();


	/////////////////////////////////
	// Signals
	/////////////////////////////////
signals:
	void keySelected( const QString& key );


	/////////////////////////////////
	// Public Methods
	/////////////////////////////////
public:
	void setKeys( const QList<QString>& keyList );


	/////////////////////////////////
	// Slots
	/////////////////////////////////
private slots:
	void onMenuItemActivated( const QString& key );


	/////////////////////////////////
	// Private Data
	/////////////////////////////////
private:

};


#endif // FieldMenu_h
