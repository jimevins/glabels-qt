/*  ColorPaletteDialog.cpp
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

#include "ColorPaletteDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QColorDialog>
#include <QComboBox>
#include <QStandardItemModel>
#include <QtDebug>


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
					const QColor&  defaultColor,
					const QColor&  color,
					QWidget*       parent )
	: QDialog( parent )
{
	mColorHistory = ColorHistory::instance();
	connect( mColorHistory, SIGNAL(changed()), this, SLOT(onColorHistoryChanged()) );

	mDefaultColor = defaultColor;
	mColorNode = ColorNode( color );

	setStyleSheet( ".glabels--ColorPaletteDialog {background: white; border: 1px solid black}" );
	setWindowFlags( Qt::Popup | Qt::FramelessWindowHint );

	QVBoxLayout* vLayout = new QVBoxLayout();
	vLayout->setContentsMargins( 0, 0, 0, 0 );
	vLayout->setSpacing( 0 );

	ColorPaletteButtonItem* defaultButton = new ColorPaletteButtonItem( defaultLabel );
	connect( defaultButton, SIGNAL(activated()), this, SLOT(onDefaultItemActivated()) );
	vLayout->addWidget( defaultButton );
		
	QFrame* hline1 = new QFrame;
	hline1->setFrameStyle( QFrame::HLine | QFrame::Plain );
	hline1->setLineWidth( 1 );
	vLayout->addWidget( hline1 );

	QGridLayout* mainPaletteLayout = new QGridLayout();
	mainPaletteLayout->setSpacing( 0 );
	for ( int iRow = 0; iRow < PALETTE_ROWS; iRow++ )
	{
		for ( int iCol = 0; iCol < PALETTE_COLS; iCol++ )
		{
			int i = iRow*PALETTE_COLS + iCol;

			ColorPaletteItem* item = new ColorPaletteItem( i,
								       QColor( mColorTable[i].colorSpec ),
								       mColorTable[i].name );
			connect( item, SIGNAL(activated(int)), this, SLOT(onPaletteItemActivated(int)) );

			mainPaletteLayout->addWidget( item, iRow, iCol );
		}
	}
	vLayout->addLayout( mainPaletteLayout );

	QFrame* hline2 = new QFrame;
	hline2->setFrameStyle( QFrame::HLine | QFrame::Plain );
	hline2->setLineWidth( 1 );
	vLayout->addWidget( hline2 );

	QHBoxLayout* customPaletteLayout = new QHBoxLayout();
	customPaletteLayout->setSpacing( 0 );
	for ( int iCol = 0; iCol < PALETTE_COLS; iCol++ )
	{
		mHistoryItem[iCol] = new ColorPaletteItem( iCol, QColor(0,0,0,0), "" );
		mHistoryItem[iCol]->setEnabled( false );
		connect( mHistoryItem[iCol], SIGNAL(activated(int)), this, SLOT(onHistoryItemActivated(int)) );

		customPaletteLayout->addWidget( mHistoryItem[iCol] );
	}
	vLayout->addLayout( customPaletteLayout );


	QFrame* hline3 = new QFrame;
	hline3->setFrameStyle( QFrame::HLine | QFrame::Plain );
	hline3->setLineWidth( 1 );
	vLayout->addWidget( hline3 );

	ColorPaletteButtonItem* customColorButton = new ColorPaletteButtonItem( tr("Custom color...") );
	connect( customColorButton, SIGNAL(activated()), this, SLOT(onCustomColorItemActivated()) );
	vLayout->addWidget( customColorButton );

	QFrame* hline4 = new QFrame;
	hline4->setFrameStyle( QFrame::HLine | QFrame::Plain );
	hline4->setLineWidth( 1 );
	vLayout->addWidget( hline4 );

	mMergeFieldCombo = new QComboBox();
	mMergeFieldCombo->addItem( tr("Merge key...") );
	mMergeFieldCombo->setMinimumSize( 34, 34 );
	mMergeFieldCombo->setFrame( false );
	mMergeFieldCombo->setEnabled( false );
	connect( mMergeFieldCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboIndexChanged(int)) );
	vLayout->addWidget( mMergeFieldCombo );

	// Item 0 is the ComboBox title, not an item intended for selection. So disable it.
	const QStandardItemModel* model = qobject_cast<const QStandardItemModel*>(mMergeFieldCombo->model());
	QStandardItem* item = model->item(0);
	item->setFlags( item->flags() & ~(Qt::ItemIsSelectable|Qt::ItemIsEnabled) );
	
	setLayout( vLayout );

	loadCustomColorHistory();
}


void ColorPaletteDialog::setColorNode( const ColorNode& colorNode )
{
	mColorNode = colorNode;
}


void ColorPaletteDialog::setKeys( const QStringList& keyList )
{
	mKeys = keyList;
	
	// Clear old keys, (all entries, except item 0)
	for ( int index = mMergeFieldCombo->count()-1; index > 0; index-- )
	{
		mMergeFieldCombo->removeItem( index );
	}

	// Add new keys
	if ( keyList.size() > 0 )
	{
		mMergeFieldCombo->addItems( keyList );
		mMergeFieldCombo->setEnabled( true );
	}
	else
	{
		mMergeFieldCombo->setEnabled( false );
	}
}


void ColorPaletteDialog::clearKeys()
{
	
	for ( int index = mMergeFieldCombo->count()-1; index > 0; index-- )
	{
		mMergeFieldCombo->removeItem( index );
	}
	mMergeFieldCombo->setEnabled( false );
}


void ColorPaletteDialog::onDefaultItemActivated()
{
	mColorNode.setFieldFlag( false );
	mColorNode.setColor( mDefaultColor );
	mColorNode.setKey( "" );

	emit colorChanged( mColorNode, true );
	accept();
}


void ColorPaletteDialog::onPaletteItemActivated( int id )
{
	mColorNode.setFieldFlag( false );
	mColorNode.setColor( QColor( mColorTable[id].colorSpec ) );
	mColorNode.setKey( "" );

	emit colorChanged( mColorNode, false );
	accept();
}


void ColorPaletteDialog::onHistoryItemActivated( int id )
{
	mColorNode.setFieldFlag( false );
	mColorNode.setColor( mColorHistory->getColors()[id] );
	mColorNode.setKey( "" );

	emit colorChanged( mColorNode, false );
	accept();
}


void ColorPaletteDialog::onCustomColorItemActivated()
{
	QColorDialog dlg( mColorNode.color(), this );
	dlg.setWindowTitle( tr("Custom Color") );

	if ( dlg.exec() )
	{
		ColorNode newColorNode;

		newColorNode.setFieldFlag( false );
		newColorNode.setColor( dlg.currentColor() );
		newColorNode.setKey( "" );

		if ( newColorNode != mColorNode )
		{
			mColorNode = newColorNode;
			
			mColorHistory->addColor( mColorNode.color() );

			emit colorChanged( mColorNode, false );
			accept();
		}
	}
}


void ColorPaletteDialog::onColorHistoryChanged()
{
	loadCustomColorHistory();
}


void ColorPaletteDialog::loadCustomColorHistory()
{
	QList<QColor> colorList = mColorHistory->getColors();
	
	int id = 0;
	foreach ( QColor color, colorList )
	{
		mHistoryItem[id]->setColor( id, color, QString(tr("Custom color #%1").arg(id+1) ) );
		mHistoryItem[id]->setEnabled( true );
		id++;
	}

	while ( id < PALETTE_ROWS )
	{
		mHistoryItem[id]->setEnabled( false );
		id++;
	}
}


void ColorPaletteDialog::onComboIndexChanged( int index )
{
	if ( index != 0 )
	{
		mColorNode.setFieldFlag( true );
		mColorNode.setColor( QColor("#eeeeec") );
		mColorNode.setKey( mKeys[index-1] );

		emit colorChanged( mColorNode, false );
		accept();
	}
}


void ColorPaletteDialog::showEvent( QShowEvent* event )
{
	mMergeFieldCombo->setCurrentIndex( 0 );

	QDialog::showEvent( event );
}
