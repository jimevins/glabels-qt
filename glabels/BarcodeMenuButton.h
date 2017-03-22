/*  BarcodeMenuButton.h
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

#ifndef BarcodeMenuButton_h
#define BarcodeMenuButton_h


#include <QPushButton>

#include "BarcodeMenu.h"
#include "BarcodeStyle.h"


namespace glabels
{
	
	///
	/// Barcode Menu Button
	///
	class BarcodeMenuButton : public QPushButton
	{
		Q_OBJECT

		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		BarcodeMenuButton( QWidget* parent = nullptr );


		/////////////////////////////////
		// Signals
		/////////////////////////////////
	signals:
		void styleChanged();


		/////////////////////////////////
		// Properties
		/////////////////////////////////
	public:
		const BarcodeStyle* bcStyle() const;


		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:
		void onMenuStyleChanged();


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		BarcodeMenu*  mMenu;
		const BarcodeStyle* mBcStyle;

	};

}


#endif // BarcodeMenuButton_h
