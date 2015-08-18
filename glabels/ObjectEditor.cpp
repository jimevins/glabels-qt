/*  ObjectEditor.cpp
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
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

#include "ObjectEditor.h"


#include "LabelModel.h"
#include "LabelModelObject.h"
#include "LabelModelBoxObject.h"

#include <QtDebug>


namespace glabels
{

	///
	/// Constructor
	///
	ObjectEditor::ObjectEditor( QWidget *parent )
		: mModel(0), mObject(0)
	{
		setupUi( this );

		lineColorButton->init( "No line", QColor(0,0,0,0), QColor(0,0,0,255) );
		fillColorButton->init( "No fill", QColor(0,0,0,0), QColor(0,0,0,255) );

		setEnabled( false );
		hidePages();
	}

	
	void ObjectEditor::setModel( LabelModel* model )
	{
		mModel = model;

		connect( mModel, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()) );

		onSelectionChanged();
	}

	
	void ObjectEditor::hidePages()
	{
		notebook->removeTab( notebook->indexOf(textPage) );
		notebook->removeTab( notebook->indexOf(barcodePage) );
		notebook->removeTab( notebook->indexOf(imagePage) );
		notebook->removeTab( notebook->indexOf(lineFillPage) );
		notebook->removeTab( notebook->indexOf(posSizePage) );
		notebook->removeTab( notebook->indexOf(shadowPage) );
	}


	void ObjectEditor::loadLineFillPage()
	{
		lineWidthSpin->setValue( mObject->lineWidth() );
		lineColorButton->setColorNode( mObject->lineColorNode() );
		fillColorButton->setColorNode( mObject->fillColorNode() );
	}


	void ObjectEditor::onSelectionChanged()
	{
		if ( mObject )
		{
			disconnect( mObject, 0, this, 0 );
		}

		hidePages();

		if ( mModel->isSelectionAtomic() )
		{
			mObject = mModel->getFirstSelectedObject();

			if ( dynamic_cast<LabelModelBoxObject*>(mObject) )
			{
				titleImageLabel->setPixmap( QPixmap(":icons/24x24/actions/glabels-box.png") );
				titleLabel->setText( "Box object properties" );

				notebook->addTab( lineFillPage, "line/fill" );
				notebook->addTab( posSizePage, "position/size" );
				notebook->addTab( shadowPage, "shadow" );

				sizeRectFrame->setVisible( true );
				sizeResetImageButton->setVisible( false );
				sizeLineFrame->setVisible( false );

				loadLineFillPage();
				
				setEnabled( true );
			}
			else
			{
				Q_ASSERT_X( false, "ObjectEditor::onSelectionChanged", "Invalid object" );
			}

			connect( mObject, SIGNAL(changed()), this, SLOT(onObjectChanged()) );
			connect( mObject, SIGNAL(moved()), this, SLOT(onObjectMoved()) );
		}
		else
		{
			mObject = 0;

			titleImageLabel->setPixmap( QPixmap(":icons/24x24/actions/glabels-object-properties.png") );
			titleLabel->setText( "Object properties" );
			setEnabled( false );
		}
	}

	
	void ObjectEditor::onObjectChanged()
	{
		qDebug() << "Object changed.";
	}

	
	void ObjectEditor::onObjectMoved()
	{
		qDebug() << "Object moved.";
	}

	
	void ObjectEditor::onLineControlsChanged()
	{
		mObject->setLineWidth( lineWidthSpin->value() );
	}

	
	void ObjectEditor::onFillControlsChanged()
	{
	}


	void ObjectEditor::onChanged()
	{
		qDebug() << "Form changed.";
	}

}
