/*  MergeView.cpp
 *
 *  Copyright (C) 2016  Jim Evins <evins@snaught.com>
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

#include "MergeView.h"

#include "LabelModel.h"
#include "MergeFactory.h"
#include <QtDebug>


///
/// Constructor
///
MergeView::MergeView( QWidget *parent )
	: QWidget(parent), mModel(0)
{
	setupUi( this );

	mMergeFormatNames = MergeFactory::nameList();
	formatCombo->addItems( mMergeFormatNames );
}


///
/// Destructor
///
MergeView::~MergeView()
{
}


///
/// Set Model
///
void MergeView::setModel( LabelModel* model, UndoRedoModel* undoRedoModel )
{
	mModel = model;
	mUndoRedoModel = undoRedoModel;

	onMergeChanged();
	connect( mModel, SIGNAL(changed()), this, SLOT(onMergeChanged()) );
}


///
/// Merge changed handler
///
void MergeView::onMergeChanged()
{
	int index = mMergeFormatNames.indexOf( MergeFactory::idToName( mModel->merge()->id() ) );
	formatCombo->setCurrentIndex( index );

	switch ( MergeFactory::idToType( mModel->merge()->id() ) )
	{
	case MergeFactory::NONE:
	case MergeFactory::FIXED:
		locationLabel->setEnabled( false );
		locationButton->setEnabled( false );
		locationButton->setText( "" );
		break;

	case MergeFactory::FILE:
		locationLabel->setEnabled( true );
		locationButton->setEnabled( true );
		if ( mModel->merge()->source().isEmpty() )
		{
			locationButton->setText( "" );
		}
		else
		{
			locationButton->setText( mModel->merge()->source() );
		}
		break;

	default:
		qWarning( "MergeView::onMergeChanged()::Should not be reached!" );
		break;
	}

	loadHeaders( mModel->merge() );
	loadTable( mModel->merge() );
}


///
/// Load headers
///
void MergeView::loadHeaders( Merge* merge )
{
	mPrimaryKey = merge->primaryKey();
	mKeys = merge->keyList();

	recordsTable->setColumnCount( mKeys.size() + 1 );  // Include extra column

	// First column = primay Key
	QTableWidgetItem* item = new QTableWidgetItem( mPrimaryKey );
	item->setFlags( Qt::ItemIsEnabled );
	recordsTable->setHorizontalHeaderItem( 0, item );

	// Starting on second column, one column per key, skip primary Key
	int iCol = 1;
	foreach ( QString key, mKeys )
	{
		if ( key != mPrimaryKey )
		{
			QTableWidgetItem* item = new QTableWidgetItem( key );
			item->setFlags( Qt::ItemIsEnabled );
			recordsTable->setHorizontalHeaderItem( iCol, item );

			iCol++;
		}

	}

	// Extra dummy column to fill any extra horizontal space
	QTableWidgetItem* fillItem = new QTableWidgetItem();
	fillItem->setFlags( Qt::NoItemFlags );
	recordsTable->setHorizontalHeaderItem( iCol, fillItem );
	recordsTable->horizontalHeader()->setStretchLastSection( true );
}


///
/// Load table
///
void MergeView::loadTable( Merge* merge )
{
	const QList<MergeRecord*>& records = merge->recordList();
	recordsTable->setRowCount( records.size() );

	int iRow = 0;
	foreach ( MergeRecord* record, records )
	{
		// First column for primay field
		QTableWidgetItem* item = new QTableWidgetItem();
		if ( record->contains( mPrimaryKey ) )
		{
			item->setText( (*record)[mPrimaryKey] );
		}
		item->setFlags( Qt::ItemIsEnabled | Qt::ItemIsUserCheckable );
		item->setCheckState( record->isSelected() ? Qt::Checked : Qt::Unchecked );
		recordsTable->setItem( iRow, 0, item );
		recordsTable->resizeColumnToContents( 0 );

		// Starting on second column, one column per field (even if empty), skip primary field
		int iCol = 1;
		foreach ( QString key, mKeys )
		{
			if ( key != mPrimaryKey )
			{
				if ( record->contains( key ) )
				{
					QTableWidgetItem* item = new QTableWidgetItem( (*record)[key] );
					item->setFlags( Qt::ItemIsEnabled );
					recordsTable->setItem( iRow, iCol, item );
					recordsTable->resizeColumnToContents( iCol );
				}

				iCol++;
			}
		}

		// Extra dummy column to fill any extra horizontal space
		QTableWidgetItem* fillItem = new QTableWidgetItem();
		fillItem->setFlags( Qt::NoItemFlags );
		recordsTable->setItem( iRow, iCol, fillItem );

		iRow++;
	}


}
