/*  LabelModelBarcodeObject.cpp
 *
 *  Copyright (C) 2017  Jim Evins <evins@snaught.com>
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

#include "LabelModelBarcodeObject.h"

#include "BarcodeBackends.h"
#include "Size.h"

#include "glbarcode/Factory.h"
#include "glbarcode/QtRenderer.h"

#include <QBrush>
#include <QPen>
#include <QTextDocument>
#include <QTextBlock>
#include <QRegularExpression>
#include <QtDebug>


namespace glabels
{

	//
	// Private
	//
	namespace
	{
		const QColor emptyFillColor = QColor( 128, 128, 128, 128 );
		const Distance pad = Distance::pt(4);
		const Distance minW = Distance::pt(18);
		const Distance minH = Distance::pt(18);
	}


	///
	/// Constructor
	///
	LabelModelBarcodeObject::LabelModelBarcodeObject()
	{
		mOutline = new Outline( this );

		mHandles << new HandleNorthWest( this );
		mHandles << new HandleNorth( this );
		mHandles << new HandleNorthEast( this );
		mHandles << new HandleEast( this );
		mHandles << new HandleSouthEast( this );
		mHandles << new HandleSouth( this );
		mHandles << new HandleSouthWest( this );
		mHandles << new HandleWest( this );

		mBcStyle        = BarcodeBackends::defaultStyle();
		mBcTextFlag     = mBcStyle.canText();
		mBcChecksumFlag = mBcStyle.canChecksum();
		mBcFormatDigits = mBcStyle.preferedN();
		mBcData         = "";
		mBcColorNode    = ColorNode( Qt::black );

		mEditorBarcode = nullptr;

		update(); // Initialize cached editor layouts
	}


	///
	/// Copy constructor
	///
	LabelModelBarcodeObject::LabelModelBarcodeObject( const LabelModelBarcodeObject* object )
		: LabelModelObject(object)
	{
		mBcStyle        = object->mBcStyle;
		mBcTextFlag     = object->mBcTextFlag;
		mBcChecksumFlag = object->mBcChecksumFlag;
		mBcFormatDigits = object->mBcFormatDigits;
		mBcData         = object->mBcData;
		mBcColorNode    = object->mBcColorNode;

		mEditorBarcode = nullptr;
		update(); // Initialize cached editor layouts
	}


	///
	/// Destructor
	///
	LabelModelBarcodeObject::~LabelModelBarcodeObject()
	{
		delete mOutline;

		foreach( Handle* handle, mHandles )
		{
			delete handle;
		}
		mHandles.clear();

		delete mEditorBarcode;
	}


	///
	/// Clone
	///
	LabelModelBarcodeObject* LabelModelBarcodeObject::clone() const
	{
		return new LabelModelBarcodeObject( this );
	}


	///
	/// bcData Property Getter
	///
	QString LabelModelBarcodeObject::bcData() const
	{
		return mBcData.toString();
	}


	///
	/// bcData Property Setter
	///
	void LabelModelBarcodeObject::setBcData( const QString& value )
	{
		if ( mBcData.toString() != value )
		{
			mBcData = value;
			update();
			emit changed();
		}
	}


	///
	/// bcTextFlag Property Getter
	///
	bool LabelModelBarcodeObject::bcTextFlag() const
	{
		return mBcTextFlag;
	}


	///
	/// bcTextFlag Property Setter
	///
	void LabelModelBarcodeObject::setBcTextFlag( bool value )
	{
		if ( mBcTextFlag != value )
		{
			mBcTextFlag = value;
			update();
			emit changed();
		}
	}


	///
	/// bcChecksumFlag Property Getter
	///
	bool LabelModelBarcodeObject::bcChecksumFlag() const
	{
		return mBcChecksumFlag;
	}


	///
	/// bcChecksumFlag Property Setter
	///
	void LabelModelBarcodeObject::setBcChecksumFlag( bool value )
	{
		if ( mBcChecksumFlag != value )
		{
			mBcChecksumFlag = value;
			update();
			emit changed();
		}
	}


	///
	/// Barcode Color Node Property Getter
	///
	ColorNode LabelModelBarcodeObject::bcColorNode() const
	{
		return mBcColorNode;
	}


	///
	/// Barcode Color Node Property Setter
	///
	void LabelModelBarcodeObject::setBcColorNode( const ColorNode& value )
	{
		if ( mBcColorNode != value )
		{
			mBcColorNode = value;
			update();
			emit changed();
		}
	}
		

	///
	/// Barcode Style Property Getter
	///
	BarcodeStyle LabelModelBarcodeObject::bcStyle() const
	{
		return mBcStyle;
	}


	///
	/// Barcode Style Property Setter
	///
	void LabelModelBarcodeObject::setBcStyle( const BarcodeStyle& value )
	{
		if ( mBcStyle != value )
		{
			mBcStyle = value;
			update();
			emit changed();
		}
	}


	///
	/// Barcode Format Digits Property Getter
	///
	int LabelModelBarcodeObject::bcFormatDigits() const
	{
		return mBcFormatDigits;
	}


	///
	/// Barcode Format Digits Property Setter
	///
	void LabelModelBarcodeObject::setBcFormatDigits( int value )
	{
		if ( mBcFormatDigits != value )
		{
			mBcFormatDigits = value;
			update();
			emit changed();
		}
	}


	///
	/// Draw shadow of object
	///
	void LabelModelBarcodeObject::drawShadow( QPainter*      painter,
	                                          bool           inEditor,
	                                          merge::Record* record ) const
	{
		// Barcodes don't support shadows.
	}

	
	///
	/// Draw object itself
	///
	void LabelModelBarcodeObject::drawObject( QPainter*      painter,
	                                          bool           inEditor,
	                                          merge::Record* record ) const
	{
		QColor bcColor = mBcColorNode.color( record );

		if ( inEditor )
		{
			drawBcInEditor( painter, bcColor );
		}
		else
		{
			drawBc( painter, bcColor, record );
		}
	}


	///
	/// Path to test for hover condition
	///
	QPainterPath LabelModelBarcodeObject::hoverPath( double scale ) const
	{
		return mHoverPath;
	}


	///
	/// Size updated
	///
	void LabelModelBarcodeObject::sizeUpdated()
	{
		update();
	}


	///
	/// Update cached information for editor view
	///
	void LabelModelBarcodeObject::update()
	{
		if ( mEditorBarcode )
		{
			delete mEditorBarcode;
		}
		mEditorBarcode = glbarcode::Factory::createBarcode( mBcStyle.id().toStdString() );
		if ( !mEditorBarcode )
		{
			qWarning() << "Invalid barcode style" << mBcStyle.id() << "using \"code39\".";
			mBcStyle = BarcodeBackends::defaultStyle();
			mEditorBarcode = glbarcode::Factory::createBarcode( mBcStyle.id().toStdString() );
		}
		mEditorBarcode->setChecksum(mBcChecksumFlag);
		mEditorBarcode->setShowText(mBcTextFlag);

		mEditorBarcode->build( mBcData.toStdString(), mW.pt(), mH.pt() );

		if ( mEditorBarcode->isDataValid() )
		{
			mW = Distance::pt( mEditorBarcode->width() );
			mH = Distance::pt( mEditorBarcode->height() );
		}
		else
		{
			mW = max( mW, minW );
			mH = max( mH, minH );
		}

		QPainterPath path;
		path.addRect( 0, 0, mW.pt(), mH.pt() );
		mHoverPath = path;
	}


	///
	/// Draw barcode in editor from cached information
	///
	void LabelModelBarcodeObject::drawBcInEditor( QPainter* painter, const QColor& color ) const
	{
		if ( mBcData.isEmpty() )
		{
			drawPlaceHolder( painter, color, tr("No barcode data") );
		}
		else if ( mBcData.hasPlaceHolders() )
		{
			drawPlaceHolder( painter, color, mBcData.toString() );
		}
		else if ( mEditorBarcode->isDataValid() )
		{
			painter->setPen( QPen( color ) );
			glbarcode::QtRenderer renderer(painter);
			mEditorBarcode->render( renderer );
		}
		else
		{
			drawPlaceHolder( painter, color, tr("Invalid barcode data") );
		}
	}


	///
	/// Draw barcode in final printout or preview
	///
	void
	LabelModelBarcodeObject::drawBc( QPainter*      painter,
	                                 const QColor&  color,
	                                 merge::Record* record ) const
	{
		painter->setPen( QPen( color ) );

		glbarcode::Barcode* bc = glbarcode::Factory::createBarcode( mBcStyle.id().toStdString() );
		bc->setChecksum(mBcChecksumFlag);
		bc->setShowText(mBcTextFlag);

		bc->build( mBcData.toStdString(), mW.pt(), mH.pt() );

		glbarcode::QtRenderer renderer(painter);
		bc->render( renderer );
	}


	///
	/// Draw place holder in editor
	///
	void
	LabelModelBarcodeObject::drawPlaceHolder( QPainter*      painter,
	                                          const QColor&  color,
	                                          const QString& text ) const
	{
		painter->setPen( Qt::NoPen );
		painter->setBrush( QBrush( emptyFillColor ) );
		painter->drawRect( QRectF( 0, 0, mW.pt(), mH.pt() ) );

		QFont font( "Sans" );
		font.setPointSizeF( 6 );

		QFontMetricsF fm(font);
		QRectF textRect = fm.boundingRect( text );

		double wPts = (mW - 2*pad).pt();
		double hPts = (mH - 2*pad).pt();
		if ( (wPts < textRect.width()) || (hPts < textRect.height()) )
		{
			double scaleX = wPts / textRect.width();
			double scaleY = hPts / textRect.height();
			font.setPointSizeF( 6 * std::min( scaleX, scaleY ) );
		}

		painter->setFont( font );
		painter->setPen( QPen( color ) );
		painter->drawText( QRectF( 0, 0, mW.pt(), mH.pt() ),
		                   Qt::AlignCenter,
		                   text );
	}

	
} // namespace glabels
