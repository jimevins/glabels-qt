/*  ColorPaletteDialog.cpp
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

#include "ColorPaletteDialog.h"

#include <QGridLayout>
#include <QPushButton>


namespace glabels
{

	ColorPaletteDialog::ColorTableEntry ColorPaletteDialog::mColorTable[] = {

		{ "#ef2929", tr("Light Scarlet Red", "Color name") },
		{ "#fcaf3e", tr("Light Orange", "Color name")      },
		{ "#fce94f", tr("Light Butter", "Color name")      },
		{ "#8ae234", tr("Light Chameleon", "Color name")   },
		{ "#729fcf", tr("Light Sky Blue", "Color name")    },
		{ "#ad7fa8", tr("Light Plum", "Color name")        },
		{ "#e9b96e", tr("Light Chocolate", "Color name")   },
		{ "#888a85", tr("Light Aluminum 1", "Color name")  },
		{ "#eeeeec", tr("Light Aluminum 2", "Color name")  },

		{ "#cc0000", tr("Scarlet Red", "Color name")       },
		{ "#f57900", tr("Orange", "Color name")            },
		{ "#edd400", tr("Butter", "Color name")            },
		{ "#73d216", tr("Chameleon", "Color name")         },
		{ "#3465a4", tr("Sky Blue", "Color name")          },
		{ "#75507b", tr("Plum", "Color name")              },
		{ "#c17d11", tr("Chocolate", "Color name")         },
		{ "#555753", tr("Aluminum 1", "Color name")        },
		{ "#d3d7cf", tr("Aluminum 2", "Color name")        },

		{ "#a40000", tr("Dark Scarlet Red", "Color name")  },
		{ "#ce5c00", tr("Dark Orange", "Color name")       },
		{ "#c4a000", tr("Dark Butter", "Color name")       },
		{ "#4e9a06", tr("Dark Chameleon", "Color name")    },
		{ "#204a87", tr("Dark Sky Blue", "Color name")     },
		{ "#5c3566", tr("Dark Plum", "Color name")         },
		{ "#8f5902", tr("Dark Chocolate", "Color name")    },
		{ "#2e3436", tr("Dark Aluminum 1", "Color name")   },
		{ "#babdb6", tr("Dark Aluminum 2", "Color name")   },

		{ "#000000", tr("Black", "Color name")             },
		{ "#2e3436", tr("Very Dark Gray", "Color name")    },
		{ "#555753", tr("Darker Gray", "Color name")       },
		{ "#888a85", tr("Dark Gray", "Color name")         },
		{ "#babdb6", tr("Medium Gray", "Color name")       },
		{ "#d3d7cf", tr("Light Gray", "Color name")        },
		{ "#eeeeec", tr("Lighter Gray", "Color name")      },
		{ "#f3f3f3", tr("Very Light Gray", "Color name")   },
		{ "#ffffff", tr("White", "Color name")             }
	};


	ColorPaletteDialog::ColorPaletteDialog( const QString& defaultLabel,
						QColor         defaultColor,
						QColor         color,
						QWidget*       parent )
		: QDialog( parent )
	{
		mColorHistory = ColorHistory::instance();
		connect( mColorHistory, SIGNAL(changed()), this, SLOT(onColorHistoryChanged()) );

		QGridLayout* layout = new QGridLayout();
		int iAbsRow = 0;

		QPushButton* defaultButton = new QPushButton( defaultLabel );
		layout->addWidget( defaultButton, iAbsRow, 0, 1, PALETTE_COLS );
		iAbsRow++;


		for ( int iRow = 0; iRow < PALETTE_ROWS; iRow++ )
		{
			for ( int iCol = 0; iCol < PALETTE_COLS; iCol++ )
			{
				int i = iRow*PALETTE_COLS + iCol;

				ColorPaletteItem* item = new ColorPaletteItem( i,
									       QColor( mColorTable[i].colorSpec ),
									       mColorTable[i].name );
				connect( item, SIGNAL(activated(int)), this, SLOT(onPaletteItemActivated(int)) );

				layout->addWidget( item, iAbsRow, iCol );
			}
			iAbsRow++;
		}


		for ( int iCol = 0; iCol < PALETTE_COLS; iCol++ )
		{
			mHistoryItem[iCol] = new ColorPaletteItem( iCol,
								   QColor(0,0,0,0),
								   "" );
			mHistoryItem[iCol]->setEnabled( false );
			connect( mHistoryItem[iCol], SIGNAL(activated(int)), this, SLOT(onHistoryItemActivated(int)) );

			layout->addWidget( mHistoryItem[iCol], iAbsRow, iCol );
		}
		iAbsRow++;


		QPushButton* customColorButton = new QPushButton( tr("Custom color") );
		layout->addWidget( customColorButton, iAbsRow, 0, 1, PALETTE_COLS );
		iAbsRow++;

		QPushButton* mergeFieldButton = new QPushButton( "TODO: Field Button" );
		layout->addWidget( mergeFieldButton, iAbsRow, 0, 1, PALETTE_COLS );

		loadCustomColorHistory();
	}


	void ColorPaletteDialog::setKeys( const QList<QString> keyList )
	{
		// TODO
	}


	void ColorPaletteDialog::clearKeys()
	{
		// TODO
	}


	void ColorPaletteDialog::onDefaultButtonClicked()
	{
		mColorNode.setFieldFlag( false );
		mColorNode.setColor( mDefaultColor );
		mColorNode.setKey( "" );

		emit colorChanged( mColorNode, true );
	}


	void ColorPaletteDialog::onPaletteItemActivated( int id )
	{
		mColorNode.setFieldFlag( false );
		mColorNode.setColor( QColor( mColorTable[id].colorSpec ) );
		mColorNode.setKey( "" );

		emit colorChanged( mColorNode, false );
	}


	void ColorPaletteDialog::onHistoryItemActivated( int id )
	{
		mColorNode.setFieldFlag( false );
		mColorNode.setColor( mColorHistory->getColor( id ) );
		mColorNode.setKey( "" );

		emit colorChanged( mColorNode, false );
	}


	void ColorPaletteDialog::onCustomColorButtonClicked()
	{
		// TODO
	}


	void ColorPaletteDialog::onColorHistoryChanged()
	{
		loadCustomColorHistory();
	}


	void ColorPaletteDialog::loadCustomColorHistory()
	{
		for ( int i; i < PALETTE_COLS; i++ )
		{
			QColor color = mColorHistory->getColor( i );

			if ( color.alpha() != 0 )
			{
				mHistoryItem[i]->setColor( i, color, QString(tr("Custom color #%d").arg(i) ) );
				mHistoryItem[i]->setEnabled( true );
			}
		}
	}

}
