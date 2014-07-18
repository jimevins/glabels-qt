/*  ColorButton.cpp
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

#include "ColorButton.h"

#include "ColorSwatch.h"
#include <QIcon>


namespace
{
	const int SWATCH_W = 100;
	const int SWATCH_H =  24;
}


namespace glabels
{

	ColorButton::ColorButton( const QString& defaultLabel,
				  const QColor&  defaultColor,
				  const QColor&  color,
				  QWidget*       parent )
		: QPushButton( parent )
	{
		mDefaultColor = defaultColor;
		mColorNode = ColorNode( color );

		setIcon( QIcon( ColorSwatch( SWATCH_W, SWATCH_H, color ) ) );
		setText( "" );

		mDialog = new ColorPaletteDialog( defaultLabel, defaultColor, color );
		mDialog->setModal( true );

		connect( this, SIGNAL(pressed()), this, SLOT(onButtonPressed()) );
		connect( mDialog, SIGNAL(changed(colorNode,bool)), this, SLOT(onColorPaletteDialogChanged(colorNode,bool)) );
	}


	void ColorButton::setColorNode( ColorNode colorNode )
	{
		mIsDefault = false;

		mColorNode = colorNode;

		if ( colorNode.fieldFlag() )
		{
			setIcon( QIcon() );
			setText( colorNode.key() );
		}
		else
		{
			setIcon( QIcon( ColorSwatch( SWATCH_W, SWATCH_H, colorNode.color() ) ) );
			setText( "" );
		}
	}


	void ColorButton::setColor( QColor color )
	{
		mIsDefault = false;

		mColorNode.setFieldFlag( false );
		mColorNode.setColor( color );
		mColorNode.setKey( "" );

		setIcon( QIcon( ColorSwatch( SWATCH_W, SWATCH_H, color ) ) );
		setText( "" );
	}


	void ColorButton::setToDefault()
	{
		mIsDefault = true;

		mColorNode.setFieldFlag( false );
		mColorNode.setColor( mDefaultColor );
		mColorNode.setKey( "" );

		setIcon( QIcon(ColorSwatch( SWATCH_W, SWATCH_H, mDefaultColor ) ) );
		setText( "" );
	}


	ColorNode ColorButton::getColorNode( bool& isDefault )
	{
		isDefault = mIsDefault;
		return mColorNode;
	}


	void ColorButton::setKeys( const QList<QString> keyList )
	{
		mDialog->setKeys( keyList );
	}


	void ColorButton::clearKeys()
	{
		mDialog->clearKeys();
	}


	void ColorButton::onButtonPressed()
	{
		setDown( true );
		// TODO: move dialog -- see menu_position_function is VALA version
		mDialog->show();
	}


	void ColorButton::onPaletteDialogChanged( ColorNode colorNode, bool isDefault )
	{
		mColorNode = colorNode;
		mIsDefault = isDefault;

		emit colorChanged( colorNode, isDefault );
	}


}
