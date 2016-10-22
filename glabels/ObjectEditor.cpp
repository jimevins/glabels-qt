/*  ObjectEditor.cpp
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
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
#include "LabelModelEllipseObject.h"
#include "LabelModelImageObject.h"
#include "LabelModelLineObject.h"
#include "UndoRedoModel.h"

#include "Merge/Merge.h"

#include "Settings.h"

#include <QFileDialog>
#include <cmath>
#include <QtDebug>


///
/// Constructor
///
ObjectEditor::ObjectEditor( QWidget *parent )
	: mModel(0), mObject(0), mBlocked(false)
{
	setupUi( this );

	lineColorButton->init( "No line", QColor(0,0,0,0), QColor(0,0,0,255) );
	fillColorButton->init( "No fill", QColor(0,0,0,0), QColor(0,0,0,255) );
	shadowColorButton->init( "Default", QColor(0,0,0,255), QColor(0,0,0,255) );

	imageFieldCombo->setName( "Key" );

	setEnabled( false );
	hidePages();

	connect( Settings::instance(), SIGNAL(changed()), this, SLOT(onSettingsChanged()) );
	onSettingsChanged();
}

	
void ObjectEditor::setModel( LabelModel* model, UndoRedoModel* undoRedoModel )
{
	mModel = model;
	mUndoRedoModel = undoRedoModel;

	connect( mModel, SIGNAL(sizeChanged()), this, SLOT(onLabelSizeChanged()) );
	connect( mModel, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()) );
	connect( mModel, SIGNAL(mergeSourceChanged()), this, SLOT(onMergeSourceChanged()) );

	onLabelSizeChanged();
	onSelectionChanged();
	onMergeSourceChanged();
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


void ObjectEditor::loadImagePage()
{
	if ( mObject )
	{
		mBlocked = true;

		TextNode filenameNode = mObject->filenameNode();

		if ( filenameNode.isField() )
		{
			imageFilenameLineEdit->setText( QString("${%1}").arg( filenameNode.data() ) );
		}
		else
		{
			imageFilenameLineEdit->setText( filenameNode.data() );
		}

		mBlocked = false;			
	}
}


void ObjectEditor::loadLineFillPage()
{
	if ( mObject )
	{
		mBlocked = true;
			
		lineWidthSpin->setValue( mObject->lineWidth().pt() );
		lineColorButton->setColorNode( mObject->lineColorNode() );
		fillColorButton->setColorNode( mObject->fillColorNode() );

		mBlocked = false;			
	}
}


void ObjectEditor::loadPositionPage()
{
	if ( mObject )
	{
		mBlocked = true;
			
		posXSpin->setDecimals( mSpinDigits );
		posXSpin->setSingleStep( mSpinStep );
		posXSpin->setSuffix( " " + mUnits.toIdString() );

		posYSpin->setDecimals( mSpinDigits );
		posYSpin->setSingleStep( mSpinStep );
		posYSpin->setSuffix( " " + mUnits.toIdString() );

		posXSpin->setValue( mObject->x0().inUnits(mUnits) );
		posYSpin->setValue( mObject->y0().inUnits(mUnits) );

		mBlocked = false;			
	}
}


void ObjectEditor::loadRectSizePage()
{
	if ( mObject )
	{
		mBlocked = true;
			
		sizeWSpin->setDecimals( mSpinDigits );
		sizeWSpin->setSingleStep( mSpinStep );
		sizeWSpin->setSuffix( " " + mUnits.toIdString() );

		sizeHSpin->setDecimals( mSpinDigits );
		sizeHSpin->setSingleStep( mSpinStep );
		sizeHSpin->setSuffix( " " + mUnits.toIdString() );

		sizeWSpin->setValue( mObject->w().inUnits(mUnits) );
		sizeHSpin->setValue( mObject->h().inUnits(mUnits) );

		mBlocked = false;			
	}
}


void ObjectEditor::loadLineSizePage()
{
	if ( mObject )
	{
		mBlocked = true;
			
		sizeLineLengthSpin->setDecimals( mSpinDigits );
		sizeLineLengthSpin->setSingleStep( mSpinStep );
		sizeLineLengthSpin->setSuffix( " " + mUnits.toIdString() );

		double w = mObject->w().inUnits(mUnits);
		double h = mObject->h().inUnits(mUnits);
		sizeLineLengthSpin->setValue( sqrt( w*w + h*h ) );
		sizeLineAngleSpin->setValue( (180/M_PI)*atan2( h, w ) );

		mBlocked = false;			
	}
}


void ObjectEditor::loadShadowPage()
{
	if ( mObject )
	{
		mBlocked = true;
			
		shadowXSpin->setDecimals( mSpinDigits );
		shadowXSpin->setSingleStep( mSpinStep );
		shadowXSpin->setSuffix( " " + mUnits.toIdString() );

		shadowYSpin->setDecimals( mSpinDigits );
		shadowYSpin->setSingleStep( mSpinStep );
		shadowYSpin->setSuffix( " " + mUnits.toIdString() );

		shadowEnableCheck->setChecked( mObject->shadow() );
		shadowXSpin->setValue( mObject->shadowX().inUnits(mUnits) );
		shadowYSpin->setValue( mObject->shadowY().inUnits(mUnits) );
		shadowColorButton->setColorNode( mObject->shadowColorNode() );
		shadowOpacitySpin->setValue( 100*mObject->shadowOpacity() );

		mBlocked = false;			
	}
}


void ObjectEditor::onSettingsChanged()
{
	mUnits = Settings::units();
	mSpinDigits = mUnits.resolutionDigits();
	mSpinStep = mUnits.resolution();

	/* Must now update limits and reload any active pages with appropriate units . */
	onLabelSizeChanged();
	onSelectionChanged();
}


void ObjectEditor::onLabelSizeChanged()
{
	if ( mModel )
	{
		mBlocked = true;

		glabels::Distance whMax = std::max( mModel->w(), mModel->h() );
			
		posXSpin->setRange( -whMax.inUnits(mUnits), 2*whMax.inUnits(mUnits) );
		posYSpin->setRange( -whMax.inUnits(mUnits), 2*whMax.inUnits(mUnits) );
		sizeWSpin->setRange( 0, 2*whMax.inUnits(mUnits) );
		sizeHSpin->setRange( 0, 2*whMax.inUnits(mUnits) );
			
		mBlocked = false;			
	}
}
	

void ObjectEditor::onSelectionChanged()
{
	if ( mModel )
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
				titleLabel->setText( tr("Box object properties") );

				notebook->addTab( lineFillPage, "line/fill" );
				notebook->addTab( posSizePage, "position/size" );
				notebook->addTab( shadowPage, "shadow" );

				fillFrame->setVisible( true );
				sizeRectFrame->setVisible( true );
				sizeResetImageButton->setVisible( false );
				sizeLineFrame->setVisible( false );

				loadLineFillPage();
				loadPositionPage();
				loadRectSizePage();
				loadShadowPage();
				
				setEnabled( true );
			}
			else if ( dynamic_cast<LabelModelEllipseObject*>(mObject) )
			{
				titleImageLabel->setPixmap( QPixmap(":icons/24x24/actions/glabels-ellipse.png") );
				titleLabel->setText( tr("Ellipse object properties") );

				notebook->addTab( lineFillPage, "line/fill" );
				notebook->addTab( posSizePage, "position/size" );
				notebook->addTab( shadowPage, "shadow" );

				fillFrame->setVisible( true );
				sizeRectFrame->setVisible( true );
				sizeResetImageButton->setVisible( false );
				sizeLineFrame->setVisible( false );

				loadLineFillPage();
				loadPositionPage();
				loadRectSizePage();
				loadShadowPage();
				
				setEnabled( true );
			}
			else if ( dynamic_cast<LabelModelImageObject*>(mObject) )
			{
				titleImageLabel->setPixmap( QPixmap(":icons/24x24/actions/glabels-image.png") );
				titleLabel->setText( tr("Image object properties") );

				notebook->addTab( imagePage, "image" );
				notebook->addTab( posSizePage, "position/size" );
				notebook->addTab( shadowPage, "shadow" );

				sizeRectFrame->setVisible( true );
				sizeResetImageButton->setVisible( true );
				sizeLineFrame->setVisible( false );

				loadImagePage();
				loadPositionPage();
				loadShadowPage();
				
				setEnabled( true );
			}
			else if ( dynamic_cast<LabelModelLineObject*>(mObject) )
			{
				titleImageLabel->setPixmap( QPixmap(":icons/24x24/actions/glabels-line.png") );
				titleLabel->setText( tr("Line object properties") );

				notebook->addTab( lineFillPage, "line/fill" );
				notebook->addTab( posSizePage, "position/size" );
				notebook->addTab( shadowPage, "shadow" );

				fillFrame->setVisible( false );
				sizeRectFrame->setVisible( false );
				sizeResetImageButton->setVisible( false );
				sizeLineFrame->setVisible( true );

				loadLineFillPage();
				loadPositionPage();
				loadLineSizePage();
				loadShadowPage();
				
				setEnabled( true );
			}
			else
			{
				Q_ASSERT_X( false, "ObjectEditor::onSelectionChanged", "Invalid object" );
			}

			connect( mObject, SIGNAL(changed()), this, SLOT(onObjectChanged()) );
			connect( mObject, SIGNAL(moved()), this, SLOT(onObjectMoved()) );
			connect( mObject, SIGNAL(destroyed(QObject*)), this, SLOT(onObjectDestroyed()) );
		}
		else
		{
			mObject = 0;

			titleImageLabel->setPixmap( QPixmap(":icons/24x24/actions/glabels-object-properties.png") );
			titleLabel->setText( "Object properties" );
			setEnabled( false );
		}
	}
}

	
void ObjectEditor::onMergeSourceChanged()
{
	if ( !mBlocked )
	{
		QStringList keys = mModel->merge()->keys();
		lineColorButton->setKeys( keys );
		fillColorButton->setKeys( keys );
		imageFieldCombo->setKeys( keys );
		shadowColorButton->setKeys( keys );
	}
}


void ObjectEditor::onObjectChanged()
{
	if ( !mBlocked )
	{
		loadLineFillPage();
		loadRectSizePage();
		loadLineSizePage();
		loadImagePage();
		loadShadowPage();
	}
}

	
void ObjectEditor::onObjectMoved()
{
	if ( !mBlocked )
	{
		loadPositionPage();
	}
}


void ObjectEditor::onObjectDestroyed()
{
	disconnect( mObject, 0, this, 0 );
	mObject = 0;
}
	
	
void ObjectEditor::onLineControlsChanged()
{
	if ( !mBlocked )
	{
		mBlocked = true;

		mUndoRedoModel->checkpoint( tr("Line") );
		
		mObject->setLineWidth( glabels::Distance::pt(lineWidthSpin->value()) );
		mObject->setLineColorNode( lineColorButton->colorNode() );

		mBlocked = false;
	}
}

	
void ObjectEditor::onFillControlsChanged()
{
	if ( !mBlocked )
	{
		mBlocked = true;

		mUndoRedoModel->checkpoint( tr("Fill") );
		
		mObject->setFillColorNode( fillColorButton->colorNode() );

		mBlocked = false;
	}
}


void ObjectEditor::onImageFileButtonClicked()
{
	QString filename =
		QFileDialog::getOpenFileName( this->window(),
					      tr("gLabels - Select image file"),
					      ".",
					      tr("Image Files (*.png *.jpg *.bmp);;All files (*)") );
	if ( !filename.isEmpty() )
	{
		mUndoRedoModel->checkpoint( tr("Set image") );
		mObject->setFilenameNode( TextNode( false, filename ) );
	}
}


void ObjectEditor::onImageKeySelected(QString key )
{
	qDebug() << "Key = " << key;
}


void ObjectEditor::onPositionControlsChanged()
{
	if ( !mBlocked )
	{
		mBlocked = true;

		mUndoRedoModel->checkpoint( tr("Move") );
		
		glabels::Distance x = glabels::Distance(posXSpin->value(), mUnits);
		glabels::Distance y = glabels::Distance(posYSpin->value(), mUnits);

		mObject->setPosition( x, y );

		mBlocked = false;
	}
}


void ObjectEditor::onRectSizeControlsChanged()
{
	if ( !mBlocked )
	{
		mBlocked = true;
			
		mUndoRedoModel->checkpoint( tr("Size") );
		
		glabels::Distance spinW = glabels::Distance(sizeWSpin->value(), mUnits);
		glabels::Distance spinH = glabels::Distance(sizeHSpin->value(), mUnits);
				
		if ( sizeAspectCheck->isChecked() )
		{
			if ( fabs(spinW - mObject->w()) > fabs(spinH - mObject->h()) )
			{
				mObject->setWHonorAspect( spinW );
				sizeHSpin->setValue( mObject->h().inUnits(mUnits) );
			}
			else
			{
				mObject->setHHonorAspect( spinH );
				sizeWSpin->setValue( mObject->w().inUnits(mUnits) );
			}
		}
		else
		{
			mObject->setSize( spinW, spinH );
		}
			
		mBlocked = false;
	}
}


void ObjectEditor::onLineSizeControlsChanged()
{
	if ( !mBlocked )
	{
		mBlocked = true;
			
		mUndoRedoModel->checkpoint( tr("Size") );
		
		glabels::Distance spinLength = glabels::Distance(sizeLineLengthSpin->value(), mUnits);
		double spinAngleRads = (M_PI/180)*sizeLineAngleSpin->value();
				
		mObject->setSize( spinLength*cos(spinAngleRads), spinLength*sin(spinAngleRads) );
			
		mBlocked = false;
	}
}


void ObjectEditor::onShadowControlsChanged()
{
	if ( !mBlocked )
	{
		mBlocked = true;

		mUndoRedoModel->checkpoint( tr("Shadow") );
		
		mObject->setShadow( shadowEnableCheck->isChecked() );
		mObject->setShadowX( glabels::Distance(shadowXSpin->value(), mUnits) );
		mObject->setShadowY( glabels::Distance(shadowYSpin->value(), mUnits) );
		mObject->setShadowColorNode( shadowColorButton->colorNode() );
		mObject->setShadowOpacity( shadowOpacitySpin->value()/100.0 );

		mBlocked = false;
	}
}


void ObjectEditor::onChanged()
{
	if ( !mBlocked )
	{
		mBlocked = true;

		qDebug() << "Form changed.";

		mBlocked = false;
	}
}
