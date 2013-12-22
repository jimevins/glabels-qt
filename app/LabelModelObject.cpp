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

#include "ColorNode.h"
#include "TextNode.h"
#include "BarcodeStyle.h"
#include "LabelRegion.h"
#include "MergeRecord.h"


namespace glabels
{

	int LabelModelObject::lastId = 0;

	/*
	 * Default constructor.
	 */
	LabelModelObject::LabelModelObject( QObject *parent = 0 ) : QObject(parent)
	{
		mId = lastId++;

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


	LabelModelObject::~LabelModelObject()
	{
	}


	int LabelModelObject::id() const
	{
		return mId;
	}


	bool LabelModelObject::isSelected() const
	{
		return mSelectedFlag;
	}


	void LabelModelObject::select( bool value )
	{
		mSelectedFlag = value;
	}


	void LabelModelObject::unselect()
	{
		mSelectedFlag = false;
	}


	double LabelModelObject::x0() const
	{
		return mX0;
	}


	void LabelModelObject::setX0( double value )
	{
		if ( mX0 != value )
		{
			mX0 = value;
			emit moved();
		}
	}
		

	double LabelModelObject::y0() const
	{
		return mY0;
	}


	void LabelModelObject::setY0( double value )
	{
		if ( mY0 != value )
		{
			mY0 = value;
			emit moved();
		}
	}
		

	double LabelModelObject::w() const
	{
		return mW;
	}


	void LabelModelObject::setW( double value )
	{
		if ( mW != value )
		{
			mW = value;
			emit moved();
		}
	}
		

	double LabelModelObject::h() const
	{
		return mH;
	}


	void LabelModelObject::setH( double value )
	{
		if ( mH != value )
		{
			mH = value;
			emit moved();
		}
	}


	QTransform LabelModelObject::matrix() const
	{
		return mMatrix;
	}


	void LabelModelObject::setMatrix( const QTransform& value )
	{
		if ( mMatrix != value )
		{
			mMatrix = value;
			emit changed();
		}
	}


	bool LabelModelObject::shadow() const
	{
		return mShadowState;
	}


	void LabelModelObject::setShadow( bool value )
	{
		if ( mShadowState != value )
		{
			mShadowState = value;
			emit changed();
		}
	}


	double LabelModelObject::shadowX() const
	{
		return mShadowX;
	}


	void LabelModelObject::setShadowX( double value )
	{
		if ( mShadowX != value )
		{
			mShadowX = value;
			emit changed();
		}
	}
		

	double LabelModelObject::shadowY() const
	{
		return mShadowY;
	}


	void LabelModelObject::setShadowY( double value )
	{
		if ( mShadowY != value )
		{
			mShadowY = value;
			emit changed();
		}
	}
		

	double LabelModelObject::shadowOpacity() const
	{
		return mShadowOpacity;
	}


	void LabelModelObject::setShadowOpacity( double value )
	{
		if ( mShadowOpacity != value )
		{
			mShadowOpacity = value;
			emit changed();
		}
	}
		

	ColorNode LabelModelObject::shadowColorNode() const
	{
		return mShadowColorNode;
	}


	void LabelModelObject::setShadowColorNode( const ColorNode& value )
	{
		if ( mShadowColorNode != value )
		{
			mShadowColorNode = value;
			emit changed();
		}
	}
		

	QString LabelModelObject::fontFamily() const
	{
		return "";
	}


	void LabelModelObject::setFontFamily( const QString& value )
	{
	}


	double LabelModelObject::fontSize() const
	{
		return 0;
	}


	void LabelModelObject::setFontSize( double value )
	{
	}


	QFont::Weight LabelModelObject::fontWeight() const
	{
		return QFont::Normal;
	}


	void LabelModelObject::setFontWeight( QFont::Weight value )
	{
	}


	bool LabelModelObject::fontItalicFlag() const
	{
		return false;
	}


	void LabelModelObject::setFontItalicFlag( bool value )
	{
	}


	bool LabelModelObject::fontUnderlineFlag() const
	{
		return false;
	}


	void LabelModelObject::setFontUnderlineFlag( bool value )
	{
	}


	ColorNode LabelModelObject::textColorNode() const
	{
		return ColorNode( QColor::fromRgba(0x00000000) );
	}


	void LabelModelObject::setTextColorNode( const ColorNode &value )
	{
	}
		

	Qt::Alignment LabelModelObject::textHAlign() const
	{
		return Qt::AlignLeft;
	}


	void LabelModelObject::setTextHAlign( Qt::Alignment value )
	{
	}


	Qt::Alignment LabelModelObject::textVAlign() const
	{
		return Qt::AlignTop;
	}


	void LabelModelObject::setTextVAlign( Qt::Alignment value )
	{
	}


	double LabelModelObject::textLineSpacing() const
	{
		return 0;
	}


	void LabelModelObject::setTextLineSpacing( double value )
	{
	}


	TextNode LabelModelObject::filenameNode() const
	{
		return TextNode();
	}


	void LabelModelObject::setFilenameNode( const TextNode& value )
	{
	}
		

	double LabelModelObject::lineWidth() const
	{
		return 0;
	}


	void LabelModelObject::setLineWidth( double value )
	{
	}


	ColorNode LabelModelObject::lineColorNode() const
	{
		return ColorNode( QColor::fromRgba(0x00000000) );
	}


	void LabelModelObject::setLineColorNode( const ColorNode &value )
	{
	}
		

	ColorNode LabelModelObject::fillColorNode() const
	{
		return ColorNode( QColor::fromRgba(0x00000000) );
	}


	void LabelModelObject::setFillColorNode( const ColorNode &value )
	{
	}
		

	TextNode LabelModelObject::bcDataNode() const
	{
		return TextNode();
	}


	void LabelModelObject::setBcDataNode( const TextNode &value )
	{
	}
		

	bool LabelModelObject::bcTextFlag() const
	{
		return false;
	}


	void LabelModelObject::setBcTextFlag( bool value )
	{
	}


	bool LabelModelObject::bcChecksumFlag() const
	{
		return false;
	}


	void LabelModelObject::setBcChecksumFlag( bool value )
	{
	}


	ColorNode LabelModelObject::bcColorNode() const
	{
		return ColorNode( QColor::fromRgba(0x00000000) );
	}


	void LabelModelObject::setBcColorNode( const ColorNode &value )
	{
	}
		

	BarcodeStyle LabelModelObject::bcStyle() const
	{
		return BarcodeStyle();
	}


	void LabelModelObject::setBcStyle( const BarcodeStyle &value )
	{
	}
		

	int LabelModelObject::bcFormatDigits() const
	{
		return false;
	}


	void LabelModelObject::setBcFormatDigits( int value )
	{
	}


	bool LabelModelObject::canText() const
	{
		return false;
	}


	bool LabelModelObject::canFill() const
	{
		return false;
	}


	bool LabelModelObject::canLineColor() const
	{ 
		return false;
	}


	bool LabelModelObject::canLineWidth() const
	{
		return false;
	}


	void LabelModelObject::setPosition( double x0, double y0 )
	{
		if ( ( mX0 != x0 ) || ( mY0 != y0 ) )
		{
			mX0 = x0;
			mY0 = y0;

			emit moved();
		}
	}


	void LabelModelObject::setPositionRelative( double dx, double dy )
	{
		if ( ( dx != 0 ) || ( dy != 0 ) )
		{
			mX0 += dx;
			mY0 += dy;

			emit moved();
		}
	}


	void LabelModelObject::setSize( double w, double h )
	{
		mW = w;
		mH = h;
	}


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


	LabelRegion LabelModelObject::getExtent()
	{
		QPointF a1(    - lineWidth()/2,    - lineWidth()/2 );
		QPointF a2( mW + lineWidth()/2,    - lineWidth()/2 );
		QPointF a3( mW + lineWidth()/2, mH + lineWidth()/2 );
		QPointF a4(    - lineWidth()/2, mH + lineWidth()/2 );

		a1 = mMatrix.map( a1 );
		a2 = mMatrix.map( a2 );
		a3 = mMatrix.map( a3 );
		a4 = mMatrix.map( a4 );

		LabelRegion region;
		region.x1( std::min( a1.x(), std::min( a2.x(), std::min( a3.x(), a4.x() ) ) ) + mX0 );
		region.y1( std::min( a1.y(), std::min( a2.y(), std::min( a3.y(), a4.y() ) ) ) + mY0 );
		region.x2( std::max( a1.x(), std::max( a2.x(), std::max( a3.x(), a4.x() ) ) ) + mX0 );
		region.y2( std::max( a1.y(), std::max( a2.y(), std::max( a3.y(), a4.y() ) ) ) + mY0 );

		return region;
	}


	void LabelModelObject::rotate( double thetaDegs )
	{
		if ( thetaDegs != 0 )
		{
			mMatrix = mMatrix.rotate( thetaDegs );
			emit changed();
		}
	}


	void LabelModelObject::flipHoriz()
	{
		mMatrix = mMatrix.scale( -1, 1 );
		emit changed();
	}


	void LabelModelObject::flipVert()
	{
		mMatrix = mMatrix.scale( 1, -1 );
		emit changed();
	}


	void LabelModelObject::updateGraphicsItemMatrix( QGraphicsItem* graphicsItem )
	{
		graphicsItem->setTransform( mMatrix );
	}


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

