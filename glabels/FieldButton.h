/*  FieldButton.h
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

#ifndef FieldButton_h
#define FieldButton_h


#include <QComboBox>
#include <QString>


namespace glabels
{

	///
	/// Field Button
	///
	class FieldButton : public QComboBox
	{
		Q_OBJECT

		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		FieldButton( QWidget* parent = 0 );


		/////////////////////////////////
		// Signals
		/////////////////////////////////
	signals:
		void keySelected( QString key );


		/////////////////////////////////
		// Public Methods
		/////////////////////////////////
	public:
		void setName( const QString& name = "" );
		void setKeys( const QStringList& keyList );
		void clearKeys();


		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:
		void onIndexChanged( int index );


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		QString mName;

	};

}


#endif // FieldButton_h
