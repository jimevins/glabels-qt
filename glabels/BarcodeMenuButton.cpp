/*  BarcodeMenuButton.cpp
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

#include "BarcodeMenuButton.h"

#include "BarcodeMenuItem.h"

#include "barcode/Backends.h"

#include <QtDebug>


namespace glabels
{
	
	///
	/// Constructor
	///
	BarcodeMenuButton::BarcodeMenuButton( QWidget* parent )
		: QPushButton(parent)
	{
		mMenu = new BarcodeMenu();
		setMenu( mMenu );

		mBcStyle = barcode::Backends::defaultStyle();
		setText( mBcStyle.name() );

		connect( mMenu, SIGNAL(selectionChanged()), this, SLOT(onMenuSelectionChanged()) );
	}


	///
	/// Destructor
	///
	BarcodeMenuButton::~BarcodeMenuButton()
	{
		delete mMenu;
	}


	///
	/// bcStyle getter
	///
	barcode::Style BarcodeMenuButton::bcStyle() const
	{
		return mBcStyle;
	}


	///
	/// bcStyle setter
	///
	void BarcodeMenuButton::setBcStyle( const barcode::Style& bcStyle )
	{
		mBcStyle = bcStyle;
		if ( mBcStyle.backendId().isEmpty() )
		{
			setText( mBcStyle.name() );
		}
		else
		{
			/*
			 * Translators: %1 = name of barcode package ("GNU Barcode", "QREncode", or "Zint")
			 *              %2 = name of barcode ("Code 39", "EAN-13", "Data Matrix", "QR Code" etc)
			 */
			setText( tr("%1 - %2").arg( barcode::Backends::backendName( mBcStyle.backendId() ), mBcStyle.name() ) );
		}
	}


	///
	/// Set menu item active
	///
	void BarcodeMenuButton::setMenuItemActive()
	{
		mMenu->setBcStyle( mBcStyle );
	}


	///
	/// onMenuStyleChanged slot
	///
	void BarcodeMenuButton::onMenuSelectionChanged()
	{
		setBcStyle( mMenu->bcStyle() );

		emit selectionChanged();
	}

} // namespace glabels
