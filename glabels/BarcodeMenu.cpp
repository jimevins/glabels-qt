/*  BarcodeMenu.cpp
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

#include "BarcodeMenu.h"

#include "BarcodeMenuItem.h"

#include "barcode/Backends.h"

#include <QtDebug>


namespace glabels
{
	
	///
	/// Constructor
	///
	BarcodeMenu::BarcodeMenu()
	{
		mGroup = new QActionGroup( this );
		mBackendGroup = new QActionGroup( this );

		// Use dummy action for non-backend menu items to get exclusive checking with submenu items
		mDummyBackendAction = new QAction( this );
		mDummyBackendAction->setCheckable(true);
		mBackendGroup->addAction( mDummyBackendAction );

		foreach ( const barcode::Style& bcStyle, barcode::Backends::styleList() )
		{
			if ( bcStyle.backendId() == "" )
			{
				auto* bcMenuItem = new BarcodeMenuItem( bcStyle, this );
				mGroup->addAction( bcMenuItem );
				connect( bcMenuItem, SIGNAL(activated(const barcode::Style&)),
				         this, SLOT(onMenuItemActivated(const barcode::Style&)) );

				addAction( bcMenuItem );
			}
		}

		foreach ( const QString& backendId, barcode::Backends::backendList() )
		{
			QMenu* subMenu = addMenu( barcode::Backends::backendName( backendId ) );
			subMenu->setObjectName( backendId );
			subMenu->menuAction()->setCheckable( true );
			mBackendGroup->addAction( subMenu->menuAction() );

			foreach ( const barcode::Style& bcStyle, barcode::Backends::styleList() )
			{
				if ( bcStyle.backendId() == backendId )
				{
					auto* bcMenuItem = new BarcodeMenuItem( bcStyle, subMenu );
					mGroup->addAction( bcMenuItem );
					connect( bcMenuItem, SIGNAL(activated(const barcode::Style&)),
					         this, SLOT(onMenuItemActivated(const barcode::Style&)) );

					subMenu->addAction( bcMenuItem );
				}
			}
		}
	}


	///
	/// Destructor
	///
	BarcodeMenu::~BarcodeMenu()
	{
		qDeleteAll( mGroup->actions() ); // addAction(QAction*) does not pass ownership so manually delete menu items
		delete mGroup;
		delete mBackendGroup; // addMenu() does pass ownership so no need to delete submenus
		delete mDummyBackendAction;
	}


	///
	/// bcStyle getter
	///
	barcode::Style BarcodeMenu::bcStyle() const
	{
		return mBcStyle;
	}


	///
	/// bcStyle setter
	///
	void BarcodeMenu::setBcStyle( const barcode::Style& bcStyle )
	{
		mBcStyle = bcStyle;

		BarcodeMenuItem* menuItem = findChild<BarcodeMenuItem*>( mBcStyle.fullId() );
		if ( menuItem && !menuItem->isChecked() ) // Only need to check on initial setting
		{
			menuItem->setChecked( true );
		}

		if ( mBcStyle.backendId().isEmpty() )
		{
			mDummyBackendAction->setChecked( true );
		}
		else
		{
			QMenu* subMenu = findChild<QMenu*>( mBcStyle.backendId() );
			if ( subMenu )
			{
				subMenu->menuAction()->setChecked( true );
			}
		}
	}


	///
	/// onMenuItemActivated slot
	///
	void BarcodeMenu::onMenuItemActivated( const barcode::Style& bcStyle )
	{
		setBcStyle( bcStyle );

		emit selectionChanged();
	}

} // namespace glabels
