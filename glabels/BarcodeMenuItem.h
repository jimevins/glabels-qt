/*  BarcodeMenuItem.h
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

#ifndef glabels_BarcodeMenuItem_h
#define glabels_BarcodeMenuItem_h

#include <QAction>
#include "BarcodeStyle.h"


namespace glabels
{

	///
	/// Barcode Menu Item
	///
	class BarcodeMenuItem : public QAction
	{
		Q_OBJECT

		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		BarcodeMenuItem( const BarcodeStyle* bcStyle, QObject* parent = 0 );


		/////////////////////////////////
		// Signals
		/////////////////////////////////
	signals:
		void activated( const BarcodeStyle* bcStyle );


		/////////////////////////////////
		// Properties
		/////////////////////////////////
	public:
		const BarcodeStyle* bcStyle() const;


		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:
		void onTriggered();


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		const BarcodeStyle* mBcStyle;

	};


}

#endif // glabels_BarcodeMenuItem_h
