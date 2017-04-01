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

#include "ColorNode.h"
#include "BarcodeStyle.h"
#include "Region.h"
#include "Size.h"
#include "TextNode.h"

#include <QFont>
#include <QtDebug>


namespace glabels
{

	///
	/// Next Object ID
	///
	int LabelModelObject::msNextId = 0;


	///
	/// Constructor
	///
	LabelModelObject::LabelModelObject() : QObject(nullptr)
	{
		mId = msNextId++;

		mX0 = 0;
		mY0 = 0;
		mW  = 0;
		mH  = 0;
		mMatrix = QMatrix();

		mShadowState     = false;
		mShadowX         = 1.3;
		mShadowY         = 1.3;
		mShadowColorNode = ColorNode( QColor( 0, 0, 0 ) );
		mShadowOpacity   = 0.5;

		mSelectedFlag = false;

		mOutline = nullptr;
	}


	///
	/// Copy constructor
	///
	LabelModelObject::LabelModelObject( const LabelModelObject* object )
	{
		mId = msNextId++;

		mSelectedFlag    = object->mSelectedFlag;

		mX0              = object->mX0;
		mY0              = object->mY0;
		mW               = object->mW;
		mH               = object->mH;

		mShadowState     = object->mShadowState;
		mShadowX         = object->mShadowX;
		mShadowY         = object->mShadowY;
		mShadowOpacity   = object->mShadowOpacity;
		mShadowColorNode = object->mShadowColorNode;

		foreach ( Handle* handle, object->mHandles )
		{
			mHandles.append( handle->clone( this ) );
		}
	
		if ( object->mOutline )
		{
			mOutline = object->mOutline->clone( this );
		}
		else
		{
			mOutline = nullptr;
		}

		mMatrix          = object->mMatrix;
	}


	///
	/// Destructor
	///
	LabelModelObject::~LabelModelObject()
	{
		// empty
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
	Distance LabelModelObject::x0() const
	{
		return mX0;
	}


	///
	/// X0 Property Setter
	///
	void LabelModelObject::setX0( const Distance& value )
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
	Distance LabelModelObject::y0() const
	{
		return mY0;
	}


	///
	/// Y0 Property Setter
	///
	void LabelModelObject::setY0( const Distance& value )
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
	Distance LabelModelObject::w() const
	{
		return mW;
	}


	///
	/// W (Width) Property Setter
	///
	void LabelModelObject::setW( const Distance& value )
	{
		if ( mW != value )
		{
			mW = value;
			sizeUpdated();
			emit changed();
		}
	}
		

	///
	/// H (Height) Property Getter
	///
	Distance LabelModelObject::h() const
	{
		return mH;
	}


	///
	/// H (Height) Property Setter
	///
	void LabelModelObject::setH( const Distance& value )
	{
		if ( mH != value )
		{
			mH = value;
			sizeUpdated();
			emit changed();
		}
	}


	///
	/// Matrix Property Getter
	///
	QMatrix LabelModelObject::matrix() const
	{
		return mMatrix;
	}


	///
	/// Matrix Property Setter
	///
	void LabelModelObject::setMatrix( const QMatrix& value )
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
	Distance LabelModelObject::shadowX() const
	{
		return mShadowX;
	}


	///
	/// Shadow X Property Setter
	///
	void LabelModelObject::setShadowX( const Distance& value )
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
	Distance LabelModelObject::shadowY() const
	{
		return mShadowY;
	}


	///
	/// Shadow Y Property Setter
	///
	void LabelModelObject::setShadowY( const Distance& value )
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
	/// Virtual Natural Size Property Default Getter
	/// (Overridden by concrete class)
	///
	Size LabelModelObject::naturalSize() const
	{
		return Size( Distance::pt(0), Distance::pt(0) );
	}


	///
	/// Virtual Text Property Default Getter
	/// (Overridden by concrete class)
	///
	QString LabelModelObject::text() const
	{
		return "";
	}


	///
	/// Virtual Text Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setText( const QString& value )
	{
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
	}
		

	///
	/// Virtual Image Property Default Getter
	/// (Overridden by concrete class)
	///
	const QImage* LabelModelObject::image() const
	{
		return nullptr;
	}


	///
	/// Virtual Image Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setImage( const QImage& value )
	{
		// empty
	}
		

	///
	/// Virtual Image Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setImage( const QString& name, const QImage& value )
	{
		// empty
	}
		

	///
	/// Virtual SVG Property Default Getter
	/// (Overridden by concrete class)
	///
	QByteArray LabelModelObject::svg() const
	{
		return QByteArray();
	}


	///
	/// Virtual SVG Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setSvg( const QString& name, const QByteArray& value )
	{
		// empty
	}
		

	///
	/// Virtual Line Width Property Default Getter
	/// (Overridden by concrete class)
	///
	Distance LabelModelObject::lineWidth() const
	{
		return 0;
	}


	///
	/// Virtual Line Width Property Default Setter
	/// (Overridden by concrete class)
	///
	void LabelModelObject::setLineWidth( const Distance& value )
	{
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
		// empty
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
	void LabelModelObject::setPosition( const Distance& x0,
	                                    const Distance& y0 )
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
	void LabelModelObject::setPositionRelative( const Distance& dx,
	                                            const Distance& dy )
	{
		if ( ( dx != 0 ) || ( dy != 0 ) )
		{
			mX0 += dx;
			mY0 += dy;

			emit moved();
		}
	}


	///
	/// Get Size
	///
	Size LabelModelObject::size() const
	{
		return Size( mW, mH );
	}


	///
	/// Set Size
	///
	void LabelModelObject::setSize( const Distance& w,
	                                const Distance& h )
	{
		mW = w;
		mH = h;

		sizeUpdated();
		emit changed();
	}


	///
	/// Set Size
	///
	void LabelModelObject::setSize( const Size& size )
	{
		mW = size.w();
		mH = size.h();

		sizeUpdated();
		emit changed();
	}


	///
	/// Set Size (But Maintain Current Aspect Ratio)
	///
	void LabelModelObject::setSizeHonorAspect( const Distance& w,
	                                           const Distance& h )
	{
		double aspectRatio = mH / mW;
		Distance wNew = w;
		Distance hNew = h;
		
		if ( h > (w*aspectRatio) )
		{
			hNew = w*aspectRatio;
		}
		else
		{
			wNew = h/aspectRatio;
		}

		setSize( wNew, hNew );
	}


	///
	/// Set Width (But Maintain Current Aspect Ratio)
	///
	void LabelModelObject::setWHonorAspect( const Distance& w )
	{
		double aspectRatio = mH / mW;
		Distance h = w * aspectRatio;

		if ( ( mW != w ) || ( mH != h ) )
		{
			mW = w;
			mH = h;

			sizeUpdated();
			emit changed();
		}
	}


	///
	/// Set Height (But Maintain Current Aspect Ratio)
	///
	void LabelModelObject::setHHonorAspect( const Distance& h )
	{
		double aspectRatio = mH / mW;
		Distance w = h / aspectRatio;

		if ( ( mW != w ) || ( mH != h ) )
		{
			mW = w;
			mH = h;

			sizeUpdated();
			emit changed();
		}
	}


	///
	/// Get Extent of Bounding Box
	///
	Region LabelModelObject::getExtent()
	{
		QPointF a1( (   - lineWidth()/2).pt(), (   - lineWidth()/2).pt() );
		QPointF a2( (mW + lineWidth()/2).pt(), (   - lineWidth()/2).pt() );
		QPointF a3( (mW + lineWidth()/2).pt(), (mH + lineWidth()/2).pt() );
		QPointF a4( (   - lineWidth()/2).pt(), (mH + lineWidth()/2).pt() );

		a1 = mMatrix.map( a1 );
		a2 = mMatrix.map( a2 );
		a3 = mMatrix.map( a3 );
		a4 = mMatrix.map( a4 );

		Region region;
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
			QMatrix m;
			m.rotate( thetaDegs );
			mMatrix *= m;

			emit changed();
		}
	}


	///
	/// Flip Object Horizontally
	///
	void LabelModelObject::flipHoriz()
	{
		QMatrix m;
		m.scale( -1, 1 );
		mMatrix *= m;

		emit changed();
	}


	///
	/// Flip Object Vertically
	///
	void LabelModelObject::flipVert()
	{
		QMatrix m;
		m.scale( 1, -1 );
		mMatrix *= m;

		emit changed();
	}


	///
	/// Is this object located at x,y?
	///
	bool LabelModelObject::isLocatedAt( double          scale,
	                                    const Distance& x,
	                                    const Distance& y ) const
	{
		QPointF p( x.pt(), y.pt() );

		/*
		 * Change point to object relative coordinates
		 */
		p -= QPointF( mX0.pt(), mY0.pt() ); // Translate point to x0,y0
		p = mMatrix.inverted().map( p );

		if ( hoverPath( scale ).contains( p ) )
		{
			return true;
		}
		else if ( isSelected() && mOutline )
		{
			if ( mOutline->hoverPath( scale ).contains( p ) )
			{
				return true;
			}
		}

		return false;
	}


	///
	/// Is one of this object's handles locate at x,y?  If so, return it.
	///
	Handle* LabelModelObject::handleAt( double          scale,
	                                    const Distance& x,
	                                    const Distance& y ) const
	{
		if ( mSelectedFlag )
		{
			QPointF p( x.pt(), y.pt() );
			p -= QPointF( mX0.pt(), mY0.pt() ); // Translate point to x0,y0

			foreach ( Handle* handle, mHandles )
			{
				QPainterPath handlePath = mMatrix.map( handle->path( scale ) );
				if ( handlePath.contains( p ) )
				{
					return handle;
				}
			}
		}

		return nullptr;
	}


	///
	/// Draw object + shadow
	///
	void LabelModelObject::draw( QPainter* painter, bool inEditor, merge::Record* record ) const
	{
		painter->save();
		painter->translate( mX0.pt(), mY0.pt() );

		if ( mShadowState )
		{
			painter->save();
			painter->translate( mShadowX.pt(), mShadowY.pt() );
			painter->setMatrix( mMatrix, true );
			drawShadow( painter, inEditor, record );
			painter->restore();
		}

		painter->setMatrix( mMatrix, true );
		drawObject( painter, inEditor, record );

		painter->restore();
	}


	///
	/// Draw selection highlights
	///
	void LabelModelObject::drawSelectionHighlight( QPainter* painter, double scale ) const
	{
		painter->save();

		painter->translate( mX0.pt(), mY0.pt() );
		painter->setMatrix( mMatrix, true );

		if ( mOutline )
		{
			mOutline->draw( painter );
		}

		foreach( Handle* handle, mHandles )
		{
			handle->draw( painter, scale );
		}
		
		painter->restore();
	}


	///
	/// Default sizeUpdated implementation.
	///
	void LabelModelObject::sizeUpdated()
	{
		// empty
	}

} // namespace glabels
