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


#include <QFileDialog>
#include <QtMath>
#include <QtDebug>

#include "LabelModel.h"
#include "LabelModelObject.h"
#include "LabelModelBoxObject.h"
#include "LabelModelEllipseObject.h"
#include "LabelModelImageObject.h"
#include "LabelModelLineObject.h"
#include "LabelModelTextObject.h"
#include "Settings.h"
#include "Size.h"
#include "UndoRedoModel.h"

#include "Merge/Merge.h"


///
/// Constructor
///
ObjectEditor::ObjectEditor( QWidget *parent )
	: mModel(0), mObject(0), mImageCwd("."), mBlocked(false)
{
	setupUi( this );

	textHAlignGroup = new QButtonGroup( this );
	textHAlignGroup->addButton( textHAlignLeftToggle, Qt::AlignLeft );
	textHAlignGroup->addButton( textHAlignCenterToggle, Qt::AlignHCenter );
	textHAlignGroup->addButton( textHAlignRightToggle, Qt::AlignRight );

	textVAlignGroup = new QButtonGroup( this );
	textVAlignGroup->addButton( textVAlignTopToggle, Qt::AlignTop );
	textVAlignGroup->addButton( textVAlignMiddleToggle, Qt::AlignVCenter );
	textVAlignGroup->addButton( textVAlignBottomToggle, Qt::AlignBottom );

	lineColorButton->init( "No line", QColor(0,0,0,0), QColor(0,0,0,255) );
	fillColorButton->init( "No fill", QColor(0,0,0,0), QColor(0,0,0,255) );
	textColorButton->init( "Default", QColor(0,0,0,255), QColor(0,0,0,255) );
	shadowColorButton->init( "Default", QColor(0,0,0,255), QColor(0,0,0,255) );

	textInsertFieldCombo->setName( "Insert Field" );
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

		Size originalSize = mObject->originalSize();
		QString originalSizeString = QString( "%1:  %2 x %3 %4" )
			.arg( tr("Original size") )
			.arg( originalSize.w().inUnits(mUnits), 0, 'f', mSpinDigits )
			.arg( originalSize.h().inUnits(mUnits), 0, 'f', mSpinDigits )
			.arg( mUnits.toIdString() );
		sizeOriginalSizeLabel->setText( originalSizeString );

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
		sizeLineAngleSpin->setValue( qRadiansToDegrees( qAtan2( h, w ) ) );

		mBlocked = false;			
	}
}


void ObjectEditor::loadTextPage()
{
	if ( mObject )
	{
		mBlocked = true;

		textFontFamilyCombo->setCurrentText( mObject->fontFamily() );
		textFontSizeSpin->setValue( mObject->fontSize() );
		textFontBoldToggle->setChecked( mObject->fontWeight() == QFont::Bold );
		textFontItalicToggle->setChecked( mObject->fontItalicFlag() );
		textFontUnderlineToggle->setChecked( mObject->fontUnderlineFlag() );
		textColorButton->setColorNode( mObject->textColorNode() );
		textHAlignGroup->button( mObject->textHAlign() )->setChecked( true );
		textVAlignGroup->button( mObject->textVAlign() )->setChecked( true );
		textLineSpacingSpin->setValue( mObject->textLineSpacing() );
		textEdit->setText( mObject->text() );

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
				sizeOriginalSizeGroup->setVisible( false );
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
				sizeOriginalSizeGroup->setVisible( false );
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
				sizeOriginalSizeGroup->setVisible( true );
				sizeLineFrame->setVisible( false );

				loadImagePage();
				loadPositionPage();
				loadRectSizePage();
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
				sizeOriginalSizeGroup->setVisible( false );
				sizeLineFrame->setVisible( true );

				loadLineFillPage();
				loadPositionPage();
				loadLineSizePage();
				loadShadowPage();
				
				setEnabled( true );
			}
			else if ( dynamic_cast<LabelModelTextObject*>(mObject) )
			{
				titleImageLabel->setPixmap( QPixmap(":icons/24x24/actions/glabels-text.png") );
				titleLabel->setText( tr("Text object properties") );

				notebook->addTab( textPage, "text" );
				notebook->addTab( posSizePage, "position/size" );
				notebook->addTab( shadowPage, "shadow" );

				sizeRectFrame->setVisible( true );
				sizeOriginalSizeGroup->setVisible( false );
				sizeLineFrame->setVisible( false );

				loadTextPage();
				loadPositionPage();
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
		textInsertFieldCombo->setKeys( keys );
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
	// Either use saved CWD from a previous open or the current file, if it exists
	QString cwd = mImageCwd;
	if ( !mObject->filenameNode().isField() )
	{
		QFileInfo fileInfo( mObject->filenameNode().data() );
		if ( fileInfo.isFile() )
		{
			cwd = fileInfo.filePath();
		}
	}

	QString filters =
		tr("Image files (*.png *.jpg *.jpeg *.gif *.bmp *.pbm *.pgm *.ppm *.xbm *.xpm *.svg)") + ";;" +
		tr("All files (*)") + ";;" +
		tr("PNG - Portable Network Graphics (*.png)") + ";;" +
		tr("BMP - Windows Bitmap (*.bmp)") + ";;" +
		tr("GIF - Graphics Interchange Format (*.gif)") + ";;" +
		tr("JPEG - Joint Photographic Experts Group (*.jpg *.jpeg)") + ";;" +
		tr("PBM - Portable Bitmap (*.pbm)") + ";;" +
		tr("PGM - Portable Graymap (*.pgm)") + ";;" +
		tr("PPM - Portable Pixmap (*.ppm)") + ";;" +
		tr("SVG - Scalable Vector Graphics (*.svg)") + ";;" +
		tr("XBM - X11 Bitmap (*.xbm)") + ";;" +
		tr("XPM - X11 Pixmap (*.xpm)");
		
	QString filename =
		QFileDialog::getOpenFileName( this->window(),
					      tr("gLabels - Select image file"),
					      cwd, filters );

	if ( !filename.isEmpty() )
	{
		mUndoRedoModel->checkpoint( tr("Set image") );
		mObject->setFilenameNode( TextNode( false, filename ) );

		// Save CWD for next open
		QFileInfo fileInfo( filename );
		mImageCwd = fileInfo.absolutePath();
	}
}


void ObjectEditor::onImageKeySelected( QString key )
{
	mUndoRedoModel->checkpoint( tr("Set image") );
	mObject->setFilenameNode( TextNode( true, key ) );
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
		double spinAngleRads = qDegreesToRadians( sizeLineAngleSpin->value() );
				
		mObject->setSize( spinLength*qCos(spinAngleRads), spinLength*qSin(spinAngleRads) );
			
		mBlocked = false;
	}
}


void ObjectEditor::onTextControlsChanged()
{
	if ( !mBlocked )
	{
		mBlocked = true;

		mUndoRedoModel->checkpoint( tr("Text") );
		
		mObject->setFontFamily( textFontFamilyCombo->currentText() );
		mObject->setFontSize( textFontSizeSpin->value() );
		mObject->setFontWeight( textFontBoldToggle->isChecked() ? QFont::Bold : QFont::Normal );
		mObject->setFontItalicFlag( textFontItalicToggle->isChecked() );
		mObject->setFontUnderlineFlag( textFontUnderlineToggle->isChecked() );
		mObject->setTextColorNode( textColorButton->colorNode() );
		mObject->setTextHAlign( Qt::AlignmentFlag( textHAlignGroup->checkedId() ) );
		mObject->setTextVAlign( Qt::AlignmentFlag( textVAlignGroup->checkedId() ) );
		mObject->setTextLineSpacing( textLineSpacingSpin->value() );
		mObject->setText( textEdit->toPlainText() );

		mBlocked = false;
	}
}


void ObjectEditor::onTextInsertFieldKeySelected( QString key )
{
	textEdit->insertPlainText( "${" + key + "}" );
}


void ObjectEditor::onResetImageSize()
{
	mObject->setSize( mObject->originalSize() );
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
