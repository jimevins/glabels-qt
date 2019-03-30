/*  FieldCombo.h
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

#ifndef FieldCombo_h
#define FieldCombo_h


#include "model/Variables.h"
#include "merge/Merge.h"

#include <QComboBox>
#include <QString>
#include <QVector>


namespace glabels
{

	///
	/// Field Combo
	///
	class FieldCombo : public QComboBox
	{
		Q_OBJECT

		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		FieldCombo( QWidget* parent = nullptr );


		/////////////////////////////////
		// Signals
		/////////////////////////////////
	signals:
		void selectionChanged();


		/////////////////////////////////
		// Public Methods
		/////////////////////////////////
	public:
		bool isCurrentSelectionSpecial() const;
		QString currentSelection() const;
		
		void setCurrentSelectionToSpecial();
		void setCurrentSelection( const QString& key );
		
		void setSpecialSelectionText( const QString& name = "" );
		
		void setFieldSelections( const merge::Merge*     merge,
		                         const model::Variables* variables );
		
		void clearFieldSelections();


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
		QVector<QString> mFieldNames;

	};

}


#endif // FieldCombo_h
