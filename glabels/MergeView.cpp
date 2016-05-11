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
	mKeys = merge->keyList();

	recordsTable->setColumnCount( mKeys.size() + 1 );

	QTableWidgetItem* item = new QTableWidgetItem();
	item->setFlags( Qt::ItemIsEnabled );
	recordsTable->setHorizontalHeaderItem( 0, item );

	int iCol = 1;
	foreach ( QString key, mKeys )
	{
		QTableWidgetItem* item = new QTableWidgetItem( key );
		item->setFlags( Qt::ItemIsEnabled );
		recordsTable->setHorizontalHeaderItem( iCol, item );

		iCol++;
	}
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
		QTableWidgetItem* item = new QTableWidgetItem();
		item->setFlags( Qt::ItemIsEnabled | Qt::ItemIsUserCheckable );
		item->setCheckState( record->isSelected() ? Qt::Checked : Qt::Unchecked );
		recordsTable->setItem( iRow, 0, item );
		recordsTable->resizeColumnToContents( 0 );
		
		int iCol = 1;
		foreach ( QString key, mKeys )
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

		iRow++;
	}


}
