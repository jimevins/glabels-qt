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

#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QtDebug>


namespace glabels
{

	//
	// Static data
	//
	ColorPaletteDialog::ColorTableEntry ColorPaletteDialog::mColorTable[] = {

		{ "#ef2929", QT_TRANSLATE_NOOP("Color name", "Light Scarlet Red") },
		{ "#fcaf3e", QT_TRANSLATE_NOOP("Color name", "Light Orange")      },
		{ "#fce94f", QT_TRANSLATE_NOOP("Color name", "Light Butter")      },
		{ "#8ae234", QT_TRANSLATE_NOOP("Color name", "Light Chameleon")   },
		{ "#729fcf", QT_TRANSLATE_NOOP("Color name", "Light Sky Blue")    },
		{ "#ad7fa8", QT_TRANSLATE_NOOP("Color name", "Light Plum")        },
		{ "#e9b96e", QT_TRANSLATE_NOOP("Color name", "Light Chocolate")   },
		{ "#888a85", QT_TRANSLATE_NOOP("Color name", "Light Aluminum 1")  },
		{ "#eeeeec", QT_TRANSLATE_NOOP("Color name", "Light Aluminum 2")  },

		{ "#cc0000", QT_TRANSLATE_NOOP("Color name", "Scarlet Red")       },
		{ "#f57900", QT_TRANSLATE_NOOP("Color name", "Orange")            },
		{ "#edd400", QT_TRANSLATE_NOOP("Color name", "Butter")            },
		{ "#73d216", QT_TRANSLATE_NOOP("Color name", "Chameleon")         },
		{ "#3465a4", QT_TRANSLATE_NOOP("Color name", "Sky Blue")          },
		{ "#75507b", QT_TRANSLATE_NOOP("Color name", "Plum")              },
		{ "#c17d11", QT_TRANSLATE_NOOP("Color name", "Chocolate")         },
		{ "#555753", QT_TRANSLATE_NOOP("Color name", "Aluminum 1")        },
		{ "#d3d7cf", QT_TRANSLATE_NOOP("Color name", "Aluminum 2")        },

		{ "#a40000", QT_TRANSLATE_NOOP("Color name", "Dark Scarlet Red")  },
		{ "#ce5c00", QT_TRANSLATE_NOOP("Color name", "Dark Orange")       },
		{ "#c4a000", QT_TRANSLATE_NOOP("Color name", "Dark Butter")       },
		{ "#4e9a06", QT_TRANSLATE_NOOP("Color name", "Dark Chameleon")    },
		{ "#204a87", QT_TRANSLATE_NOOP("Color name", "Dark Sky Blue")     },
		{ "#5c3566", QT_TRANSLATE_NOOP("Color name", "Dark Plum")         },
		{ "#8f5902", QT_TRANSLATE_NOOP("Color name", "Dark Chocolate")    },
		{ "#2e3436", QT_TRANSLATE_NOOP("Color name", "Dark Aluminum 1")   },
		{ "#babdb6", QT_TRANSLATE_NOOP("Color name", "Dark Aluminum 2")   },

		{ "#000000", QT_TRANSLATE_NOOP("Color name", "Black")             },
		{ "#2e3436", QT_TRANSLATE_NOOP("Color name", "Very Dark Gray")    },
		{ "#555753", QT_TRANSLATE_NOOP("Color name", "Darker Gray")       },
		{ "#888a85", QT_TRANSLATE_NOOP("Color name", "Dark Gray")         },
		{ "#babdb6", QT_TRANSLATE_NOOP("Color name", "Medium Gray")       },
		{ "#d3d7cf", QT_TRANSLATE_NOOP("Color name", "Light Gray")        },
		{ "#eeeeec", QT_TRANSLATE_NOOP("Color name", "Lighter Gray")      },
		{ "#f3f3f3", QT_TRANSLATE_NOOP("Color name", "Very Light Gray")   },
		{ "#ffffff", QT_TRANSLATE_NOOP("Color name", "White")             }

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
		mColorNode = model::ColorNode( color );

		setStyleSheet( ".glabels--ColorPaletteDialog {background: white; border: 1px solid black}" );
		setWindowFlags( Qt::Popup | Qt::FramelessWindowHint );

		auto* vLayout = new QVBoxLayout();
		vLayout->setContentsMargins( 0, 0, 0, 0 );
		vLayout->setSpacing( 0 );

		auto* defaultButton = new ColorPaletteButtonItem( defaultLabel );
		connect( defaultButton, SIGNAL(activated()), this, SLOT(onDefaultItemActivated()) );
		vLayout->addWidget( defaultButton );
		
		QFrame* hline1 = new QFrame;
		hline1->setFrameStyle( QFrame::HLine | QFrame::Plain );
		hline1->setLineWidth( 1 );
		vLayout->addWidget( hline1 );

		auto* mainPaletteLayout = new QGridLayout();
		mainPaletteLayout->setSpacing( 0 );
		for ( int iRow = 0; iRow < PALETTE_ROWS; iRow++ )
		{
			for ( int iCol = 0; iCol < PALETTE_COLS; iCol++ )
			{
				int i = iRow*PALETTE_COLS + iCol;

				ColorPaletteItem* item = new ColorPaletteItem( i,
				                                               QColor( mColorTable[i].colorSpec ),
				                                               tr(mColorTable[i].trname) );
				connect( item, SIGNAL(activated(int)), this, SLOT(onPaletteItemActivated(int)) );

				mainPaletteLayout->addWidget( item, iRow, iCol );
			}
		}
		vLayout->addLayout( mainPaletteLayout );

		QFrame* hline2 = new QFrame;
		hline2->setFrameStyle( QFrame::HLine | QFrame::Plain );
		hline2->setLineWidth( 1 );
		vLayout->addWidget( hline2 );

		auto* customPaletteLayout = new QHBoxLayout();
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
		const auto* model = qobject_cast<const QStandardItemModel*>(mMergeFieldCombo->model());
		QStandardItem* item = model->item(0);
		item->setFlags( item->flags() & ~(Qt::ItemIsSelectable|Qt::ItemIsEnabled) );
	
		setLayout( vLayout );

		loadCustomColorHistory();
	}


	void ColorPaletteDialog::setColorNode( const model::ColorNode& colorNode )
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
		mColorNode.setField( false );
		mColorNode.setColor( mDefaultColor );
		mColorNode.setKey( "" );

		emit colorChanged( mColorNode, true );
		accept();
	}


	void ColorPaletteDialog::onPaletteItemActivated( int id )
	{
		mColorNode.setField( false );
		mColorNode.setColor( QColor( mColorTable[id].colorSpec ) );
		mColorNode.setKey( "" );

		emit colorChanged( mColorNode, false );
		accept();
	}


	void ColorPaletteDialog::onHistoryItemActivated( int id )
	{
		mColorNode.setField( false );
		mColorNode.setColor( mColorHistory->getColor(id) );
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
			model::ColorNode newColorNode;

			newColorNode.setField( false );
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
			mColorNode.setField( true );
			mColorNode.setColor( QColor( 0xee, 0xee, 0xec ) );
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

} // namespace glabels
