/*  ColorPalletteItem.cpp
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

#include "ColorPalletteItem.h"

#include "ColorSwatch.h"


//
// Private Configuration Data
//
namespace
{
	const double  wSwatch = 20;
	const double  hSwatch = 20;
}


namespace glabels
{

	///
	/// Constructor From Data
	///
	ColorPalletteItem::ColorPalletteItem( int            id,
					      const QColor&  color,
					      const QString& tip,
					      QWidget*       parent )
		: QPushButton(parent), mId(id), mColor(color), mTip(tip)
	{
		setIcon( QIcon( ColorSwatch( wSwatch, hSwatch, color ) ) );
		setToolTip( tip );

		connect( this, SIGNAL(clicked()), this, SLOT(onClicked()) );
	}


	///
	/// Color Property Setter
	///
	void ColorPalletteItem::setColor( int            id,
					  const QColor&  color,
					  const QString& tip )
	{
		mId    = id;
		mColor = color;
		mTip   = tip;

		setIcon( QIcon( ColorSwatch( wSwatch, hSwatch, color ) ) );
		setToolTip( tip );
	}


	///
	/// onClicked slot
	///
	void ColorPalletteItem::onClicked()
	{
		emit activated( mId );
	}

}

