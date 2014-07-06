/*  LabelModelObject.cpp
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

#include "LabelModelObject.h"

#include <QGraphicsDropShadowEffect>
#include <QTransform>
#include <QFont>
#include <QGraphicsItem>
#include <algorithm>

#include "ColorNode.h"
#include "TextNode.h"
#include "BarcodeStyle.h"
#include "LabelRegion.h"
#include "MergeRecord.h"


namespace glabels
{

	///
	/// Next Object ID
	///
	int LabelModelObject::msNextId = 0;


	///
	/// Constructor
	///
	LabelModelObject::LabelModelObject( QObject *parent = 0 ) : QObject(parent)
	{
		mId = msNextId++;

		mX0 = 0;
		mY0 = 0;
		mW  = 0;
		mH  = 0;
		mMatrix = QTransform();

		mShadowState     = false;
		mShadowX         = 1.3;
		mShadowY         = 1.3;
		mShadowColorNode = ColorNode( QColor::fromRgb(0x000000) );
		mShadowOpacity   = 0.5;

		mSelectedFlag = false;
	}


	///
	/// Destructor
	///
	LabelModelObject::~LabelModelObject()
	{
	}


	///
	/// ID Property Getter
	///
	int LabelModelObject::id() const
	{
		return mId;
	}


	///
	/// Selected Property Getter
	///
	bool LabelModelObject::isSelected() const
	{
		return mSelectedFlag;
	}


	///
	/// Selected Property Setter
	///
	void LabelModelObject::select( bool value )
	{
		mSelectedFlag = value;
	}


	///
	/// Clear Selected Property Setter
	///
	void LabelModelObject::unselect()
	{
		mSelectedFlag = false;
	}


	///
	/// X0 Property Getter
	///
	double LabelModelObject::x0() const
	{
		return mX0;
	}


	///
	/// X0 Property Setter
	///
	void LabelModelObject::setX0( double value )
	{
		if ( mX0 != value )
		{
			mX0 = value;
			emit moved();
		}
	}
		

	///
	/// Y0 Property Getter
	///
	double LabelModelObject::y0() const
	{
		return mY0;
	}


	///
	/// Y0 Property Setter
	///
	void LabelModelObject::setY0( double value )
	{
		if ( mY0 != value )
		{
			mY0 = value;
			emit moved();
		}
	}
		

	///
	/// W (Width) Property Getter
	///
	double LabelModelObject::w() const
	{
		return mW;
	}


	///
	/// W (Width) Property Setter
	///
	void LabelModelObject::setW( double value )
	{
		if ( mW != value )
		{
			mW = value;
			emit moved();
		}
	}
		

	///
	/// H (Height) Property Getter
	///
	double LabelModelObject::h() const
	{
		return mH;
	}


	///
	/// H (Height) Property Setter
	///
	void LabelModelObject::setH( double value )
	{
		if ( mH != value )
		{
			mH = value;
			emit moved();
		}
	}


	///
	/// Matrix Property Getter
	///
	QTransform LabelModelObject::matrix() const
	{
		return mMatrix;
	}


	///
	/// Matrix Property Setter
	///
	void LabelModelObject::setMatrix( const QTransform& value )
	{
		if ( mMatrix != value )
		{
			mMatrix = value;
			emit changed();
		}
	}


	///
	/// Shadow State Property Getter
	///
	bool LabelModelObject::shadow() const
	{
		return mShadowState;
	}


	///
	/// Shadow State Property Setter
	///
	void LabelModelObject::setShadow( bool value )
	{
		if ( mShadowState != value )
		{
			mShadowState = value;
			emit changed();
		}
	}


	///
	/// Shadow X Property Getter
	///
	double LabelModelObject::shadowX() const
	{
		return mShadowX;
	}


	///
	/// Shadow X Property Setter
	///
	void LabelModelObject::setShadowX( double value )
	{
		if ( mShadowX != value )
		{
			mShadowX = value;
			emit changed();
		}
	}
		

	///
	/// Shadow Y Property Getter
	///
	double LabelModelObject::shadowY() const
	{
		return mShadowY;
	}


	///
	/// Shadow Y Property Setter
	///
	void LabelModelObject::setShadowY( double value )
	{
		if ( mShadowY != value )
		{
			mShadowY = value;
			emit changed();
		}
	}
		

	///
	/// Shadow Opacity Property Getter
	///
	double LabelModelObject::shadowOpacity() const
	{
		return mShadowOpacity;
	}


	///
	/// Shadow Opacity Property Setter
	///
	void LabelModelObject::setShadowOpacity( double value )
	{
		if ( mShadowOpacity != value )
		{
			mShadowOpacity = value;
			emit changed();
		}
	}
		

	///
	/// Shadow Color Node Property Getter
	///
	ColorNode LabelModelObject::shadowColorNode() const
	{
		return mShadowColorNode;
	}


	///
	/// Shadow Color Node Property Setter
	///
	void LabelModelObject::setShadowColorNode( const ColorNode& value )
	{
		if ( mShadowColorNode != value )
		{
			mShadowColorNode = value;
			emit changed();
		}
	}
		

	///
	/// Virtual Font Family Property Default Getter
	/// (Overridden by concrete class)
	///
	QString LabelModelObject::fontFamily() const
	{
		return "";
	}


	///
	/// Virtual Font Family Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setFontFamily( const QString& value )
	{
	}


	///
	/// Virtual Font Size Property Default Getter
	/// (Overridden by concrete class)
	///
	double LabelModelObject::fontSize() const
	{
		return 0;
	}


	///
	/// Virtual Font Size Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setFontSize( double value )
	{
	}


	///
	/// Virtual Font Weight Property Default Getter
	/// (Overridden by concrete class)
	///
	QFont::Weight LabelModelObject::fontWeight() const
	{
		return QFont::Normal;
	}


	///
	/// Virtual Font Weight Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setFontWeight( QFont::Weight value )
	{
	}


	///
	/// Virtual Font Italic Flag Property Default Getter
	/// (Overridden by concrete class)
	///
	bool LabelModelObject::fontItalicFlag() const
	{
		return false;
	}


	///
	/// Virtual Font Italic Flag Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setFontItalicFlag( bool value )
	{
	}


	///
	/// Virtual Font Underline Flag Property Default Getter
	/// (Overridden by concrete class)
	///
	bool LabelModelObject::fontUnderlineFlag() const
	{
		return false;
	}


	///
	/// Virtual Font Underline Flag Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setFontUnderlineFlag( bool value )
	{
	}


	///
	/// Virtual Text Color Node Property Default Getter
	/// (Overridden by concrete class)
	///
	ColorNode LabelModelObject::textColorNode() const
	{
		return ColorNode( QColor::fromRgba(0x00000000) );
	}


	///
	/// Virtual Text Color Node Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setTextColorNode( const ColorNode &value )
	{
	}
		

	///
	/// Virtual Text Horizontal Alignment Property Default Getter
	/// (Overridden by concrete class)
	///
	Qt::Alignment LabelModelObject::textHAlign() const
	{
		return Qt::AlignLeft;
	}


	///
	/// Virtual Text Horizontal Alignment Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setTextHAlign( Qt::Alignment value )
	{
	}


	///
	/// Virtual Text Vertical Alignment Property Default Getter
	/// (Overridden by concrete class)
	///
	Qt::Alignment LabelModelObject::textVAlign() const
	{
		return Qt::AlignTop;
	}


	///
	/// Virtual Text Vertical Alignment Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setTextVAlign( Qt::Alignment value )
	{
	}


	///
	/// Virtual Text Line Spacing Property Default Getter
	/// (Overridden by concrete class)
	///
	double LabelModelObject::textLineSpacing() const
	{
		return 0;
	}


	///
	/// Virtual Text Line Spacing Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setTextLineSpacing( double value )
	{
	}


	///
	/// Virtual Filename Node Property Default Getter
	/// (Overridden by concrete class)
	///
	TextNode LabelModelObject::filenameNode() const
	{
		return TextNode();
	}


	///
	/// Virtual Filename Node Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setFilenameNode( const TextNode& value )
	{
	}
		

	///
	/// Virtual Line Width Property Default Getter
	/// (Overridden by concrete class)
	///
	double LabelModelObject::lineWidth() const
	{
		return 0;
	}


	///
	/// Virtual Line Width Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setLineWidth( double value )
	{
	}


	///
	/// Virtual Line Color Node Property Default Getter
	/// (Overridden by concrete class)
	///
	ColorNode LabelModelObject::lineColorNode() const
	{
		return ColorNode( QColor::fromRgba(0x00000000) );
	}


	///
	/// Virtual Line Color Node Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setLineColorNode( const ColorNode &value )
	{
	}
		

	///
	/// Virtual Fill Color Node Property Default Getter
	/// (Overridden by concrete class)
	///
	ColorNode LabelModelObject::fillColorNode() const
	{
		return ColorNode( QColor::fromRgba(0x00000000) );
	}


	///
	/// Virtual Fill Color Node Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setFillColorNode( const ColorNode &value )
	{
	}
		

	///
	/// Virtual Barcode Data Node Property Default Getter
	/// (Overridden by concrete class)
	///
	TextNode LabelModelObject::bcDataNode() const
	{
		return TextNode();
	}


	///
	/// Virtual Barcode Data Node Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setBcDataNode( const TextNode &value )
	{
	}
		

	///
	/// Virtual Barcode Text Flag Property Default Getter
	/// (Overridden by concrete class)
	///
	bool LabelModelObject::bcTextFlag() const
	{
		return false;
	}


	///
	/// Virtual Barcode Text Flag Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setBcTextFlag( bool value )
	{
	}


	///
	/// Virtual Barcode Checksum Flag Property Default Getter
	/// (Overridden by concrete class)
	///
	bool LabelModelObject::bcChecksumFlag() const
	{
		return false;
	}


	///
	/// Virtual Barcode Checksum Flag Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setBcChecksumFlag( bool value )
	{
	}


	///
	/// Virtual Barcode Color Node Property Default Getter
	/// (Overridden by concrete class)
	///
	ColorNode LabelModelObject::bcColorNode() const
	{
		return ColorNode( QColor::fromRgba(0x00000000) );
	}


	///
	/// Virtual Barcode Color Node Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setBcColorNode( const ColorNode &value )
	{
	}
		

	///
	/// Virtual Barcode Style Property Default Getter
	/// (Overridden by concrete class)
	///
	BarcodeStyle LabelModelObject::bcStyle() const
	{
		return BarcodeStyle();
	}


	///
	/// Virtual Barcode Style Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setBcStyle( const BarcodeStyle &value )
	{
	}
		

	///
	/// Virtual Barcode Format Digits Property Default Getter
	/// (Overridden by concrete class)
	///
	int LabelModelObject::bcFormatDigits() const
	{
		return 0;
	}


	///
	/// Virtual Barcode Format Digits Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setBcFormatDigits( int value )
	{
	}


	///
	/// Virtual Can Text Capability Read-Only Property Default Getter
	/// (Overridden by concrete class)
	///
	bool LabelModelObject::canText() const
	{
		return false;
	}


	///
	/// Virtual Can Fill Capability Read-Only Property Default Getter
	/// (Overridden by concrete class)
	///
	bool LabelModelObject::canFill() const
	{
		return false;
	}


	///
	/// Virtual Can Line Color Capability Read-Only Property Default Getter
	/// (Overridden by concrete class)
	///
	bool LabelModelObject::canLineColor() const
	{ 
		return false;
	}


	///
	/// Virtual Can Line Width Capability Read-Only Property Default Getter
	/// (Overridden by concrete class)
	///
	bool LabelModelObject::canLineWidth() const
	{
		return false;
	}


	///
	/// Set Absolute Position
	///
	void LabelModelObject::setPosition( double x0, double y0 )
	{
		if ( ( mX0 != x0 ) || ( mY0 != y0 ) )
		{
			mX0 = x0;
			mY0 = y0;

			emit moved();
		}
	}


	///
	/// Set Relative Position
	///
	void LabelModelObject::setPositionRelative( double dx, double dy )
	{
		if ( ( dx != 0 ) || ( dy != 0 ) )
		{
			mX0 += dx;
			mY0 += dy;

			emit moved();
		}
	}


	///
	/// Set Size
	///
	void LabelModelObject::setSize( double w, double h )
	{
		mW = w;
		mH = h;
	}


	///
	/// Set Size (But Maintain Current Aspect Ratio)
	///
	void LabelModelObject::setSizeHonorAspect( double w, double h )
	{
		double aspectRatio = mH / mW;

		if ( h > (w * aspectRatio) )
		{
			h = w * aspectRatio;
		}
		else
		{
			w = h / aspectRatio;
		}

		if ( ( mW != w ) || ( mH != h ) )
		{
			mW = w;
			mH = h;

			emit changed();
		}
	}


	///
	/// Set Width (But Maintain Current Aspect Ratio)
	///
	void LabelModelObject::setWHonorAspect( double w )
	{
		double aspectRatio = mH / mW;
		double h = w * aspectRatio;

		if ( ( mW != w ) || ( mH != h ) )
		{
			mW = w;
			mH = h;

			emit changed();
		}
	}


	///
	/// Set Height (But Maintain Current Aspect Ratio)
	///
	void LabelModelObject::setHHonorAspect( double h )
	{
		double aspectRatio = mH / mW;
		double w = h / aspectRatio;

		if ( ( mW != w ) || ( mH != h ) )
		{
			mW = w;
			mH = h;

			emit changed();
		}
	}


	///
	/// Get Extent of Bounding Box
	///
	LabelRegion LabelModelObject::getExtent()
	{
		using std::min;
		using std::max;

		QPointF a1(    - lineWidth()/2,    - lineWidth()/2 );
		QPointF a2( mW + lineWidth()/2,    - lineWidth()/2 );
		QPointF a3( mW + lineWidth()/2, mH + lineWidth()/2 );
		QPointF a4(    - lineWidth()/2, mH + lineWidth()/2 );

		a1 = mMatrix.map( a1 );
		a2 = mMatrix.map( a2 );
		a3 = mMatrix.map( a3 );
		a4 = mMatrix.map( a4 );

		LabelRegion region;
		region.setX1( min( a1.x(), min( a2.x(), min( a3.x(), a4.x() ) ) ) + mX0 );
		region.setY1( min( a1.y(), min( a2.y(), min( a3.y(), a4.y() ) ) ) + mY0 );
		region.setX2( max( a1.x(), max( a2.x(), max( a3.x(), a4.x() ) ) ) + mX0 );
		region.setY2( max( a1.y(), max( a2.y(), max( a3.y(), a4.y() ) ) ) + mY0 );

		return region;
	}


	///
	/// Rotate Object
	///
	void LabelModelObject::rotate( double thetaDegs )
	{
		if ( thetaDegs != 0 )
		{
			mMatrix = mMatrix.rotate( thetaDegs );
			emit changed();
		}
	}


	///
	/// Flip Object Horizontally
	///
	void LabelModelObject::flipHoriz()
	{
		mMatrix = mMatrix.scale( -1, 1 );
		emit changed();
	}


	///
	/// Flip Object Vertically
	///
	void LabelModelObject::flipVert()
	{
		mMatrix = mMatrix.scale( 1, -1 );
		emit changed();
	}


	///
	/// Update Representative Graphics Item with Object's Transformation Matrix
	///
	void LabelModelObject::updateGraphicsItemMatrix( QGraphicsItem* graphicsItem )
	{
		graphicsItem->setTransform( mMatrix );
	}


	///
	/// Update Representative Graphics Item with Object's Shadow Properties
	///
	void LabelModelObject::updateGraphicsItemShadow( QGraphicsItem* graphicsItem )
	{
		QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();

		QColor color = mShadowColorNode.color();
		color.setAlphaF( mShadowOpacity );

		shadowEffect->setColor( color );
		shadowEffect->setOffset( mShadowX, mShadowY );
		shadowEffect->setBlurRadius( 0 );

		graphicsItem->setGraphicsEffect( shadowEffect );
	}

}

