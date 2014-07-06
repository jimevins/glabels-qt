/*  LabelModelObject.h
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

#ifndef glabels_LabelModelObject_h
#define glabels_LabelModelObject_h

#include <QObject>
#include <QFont>
#include <QTransform>

#include "ColorNode.h"
#include "TextNode.h"
#include "BarcodeStyle.h"

class QGraphicsItem;


namespace glabels
{
	// Forward References
	class LabelRegion;
	class MergeRecord;


	///
	/// Label Model Object Base Class
	///
	class LabelModelObject : public QObject
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	public:
		LabelModelObject( QObject *parent );
		virtual ~LabelModelObject();


		///////////////////////////////////////////////////////////////
		// Signals
		///////////////////////////////////////////////////////////////
	signals:
		void moved();
		void changed();


		///////////////////////////////////////////////////////////////
		// Common Properties
		///////////////////////////////////////////////////////////////
	public:
		//
		// ID Property.
		//
		Q_PROPERTY( int id READ id )

		int id() const;

		//
		// Selected Property.
		//
		Q_PROPERTY( bool selected READ isSelected WRITE select RESET unselect )

		bool isSelected() const;
		void select( bool value = true );
		void unselect();


		//
		// x0 Property ( x coordinate of origin )
		//
		Q_PROPERTY( double x0 READ x0 WRITE setX0 );

		double x0() const;
		void setX0( double value );
		

		//
		// y0 Property ( y coordinate of origin )
		//
		Q_PROPERTY( double y0 READ y0 WRITE setY0 );

		double y0() const;
		void setY0( double value );
		

		//
		// w Property ( width of bounding box )
		//
		Q_PROPERTY( double w  READ w  WRITE setW );

		double w() const;
		void setW( double value );
		

		//
		// h Property ( height of bounding box )
		//
		Q_PROPERTY( double h  READ h  WRITE setH );

		double h() const;
		void setH( double value );


		//
		// Transformation Matrix Property
		//
		Q_PROPERTY( QTransform matrix READ matrix WRITE setMatrix );

		QTransform matrix() const;
		void setMatrix( const QTransform& value );


		//
		// Shadow State Property
		//
		Q_PROPERTY( bool shadow READ shadow WRITE setShadow );

		bool shadow() const;
		void setShadow( bool value );


		//
		// Shadow x Offset Property
		//
		Q_PROPERTY( double shadowX READ shadowX WRITE setShadowX );

		double shadowX() const;
		void setShadowX( double value );
		

		//
		// Shadow y Offset Property
		//
		Q_PROPERTY( double shadowY READ shadowY WRITE setShadowY );

		double shadowY() const;
		void setShadowY( double value );
		

		//
		// Shadow opacity Property
		//
		Q_PROPERTY( double shadowOpacity READ shadowOpacity WRITE setShadowOpacity );

		double shadowOpacity() const;
		void setShadowOpacity( double value );
		

		//
		// Shadow Color Property
		//
		Q_PROPERTY( ColorNode shadowColorNode READ shadowColorNode WRITE setShadowColorNode );

		ColorNode shadowColorNode() const;
		void setShadowColorNode( const ColorNode& value );
		

		///////////////////////////////////////////////////////////////
		// Text Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		//
		// Virtual Text Property: fontFamily
		//
		Q_PROPERTY( QString fontFamily READ fontFamily WRITE setFontFamily );

		virtual QString fontFamily() const;
		virtual void setFontFamily( const QString &value );


		//
		// Virtual Text Property: fontSize
		//
		Q_PROPERTY( double fontSize READ fontSize WRITE setFontSize );

		virtual double fontSize() const;
		virtual void setFontSize( double value );


		//
		// Virtual Text Property: fontWeight
		//
		Q_PROPERTY( QFont::Weight fontWeight READ fontWeight WRITE setFontWeight );

		virtual QFont::Weight fontWeight() const;
		virtual void setFontWeight( QFont::Weight value );


		//
		// Virtual Text Property: fontItalicFlag
		//
		Q_PROPERTY( bool fontItalicFlag READ fontItalicFlag WRITE setFontItalicFlag );

		virtual bool fontItalicFlag() const;
		virtual void setFontItalicFlag( bool value );


		//
		// Virtual Text Property: fontUnderlineFlag
		//
		Q_PROPERTY( bool fontUnderlineFlag READ fontUnderlineFlag WRITE setFontUnderlineFlag );

		virtual bool fontUnderlineFlag() const;
		virtual void setFontUnderlineFlag( bool value );


		//
		// Virtual Text Property: textColorNode
		//
		Q_PROPERTY( ColorNode textColorNode READ textColorNode WRITE setTextColorNode );

		virtual ColorNode textColorNode() const;
		virtual void setTextColorNode( const ColorNode &value );
		

		//
		// Virtual Text Property: textHAlign
		//
		Q_PROPERTY( Qt::Alignment textHAlign READ textHAlign WRITE setTextHAlign );

		virtual Qt::Alignment textHAlign() const;
		virtual void setTextHAlign( Qt::Alignment value );


		//
		// Virtual Text Property: textVAlign
		//
		Q_PROPERTY( Qt::Alignment textVAlign READ textVAlign WRITE setTextVAlign );

		virtual Qt::Alignment textVAlign() const;
		virtual void setTextVAlign( Qt::Alignment value );


		//
		// Virtual Text Property: textLineSpacing
		//
		Q_PROPERTY( double textLineSpacing READ textLineSpacing WRITE setTextLineSpacing );

		virtual double textLineSpacing() const;
		virtual void setTextLineSpacing( double value );


		///////////////////////////////////////////////////////////////
		// Image Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		//
		// Virtual Image Property: filenameNode
		//
		Q_PROPERTY( TextNode filenameNode READ filenameNode WRITE setFilenameNode );

		virtual TextNode filenameNode() const;
		virtual void setFilenameNode( const TextNode &value );
		

		///////////////////////////////////////////////////////////////
		// Shape Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		//
		// Virtual Shape Property: lineWidth
		//
		Q_PROPERTY( double lineWidth READ lineWidth WRITE setLineWidth );

		virtual double lineWidth() const;
		virtual void setLineWidth( double value );


		//
		// Virtual Shape Property: lineColorNode
		//
		Q_PROPERTY( ColorNode lineColorNode READ lineColorNode WRITE setLineColorNode );

		virtual ColorNode lineColorNode() const;
		virtual void setLineColorNode( const ColorNode &value );
		

		//
		// Virtual Shape Property: fillColorNode
		//
		Q_PROPERTY( ColorNode fillColorNode READ fillColorNode WRITE setFillColorNode );

		virtual ColorNode fillColorNode() const;
		virtual void setFillColorNode( const ColorNode &value );
		

		///////////////////////////////////////////////////////////////
		// Barcode Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		//
		// Virtual Barcode Property: bcDataNode
		//
		Q_PROPERTY( TextNode bcDataNode READ bcDataNode WRITE setBcDataNode );

		virtual TextNode bcDataNode() const;
		virtual void setBcDataNode( const TextNode &value );
		

		//
		// Virtual Barcode Property: bcTextFlag
		//
		Q_PROPERTY( bool bcTextFlag READ bcTextFlag WRITE setBcTextFlag );

		virtual bool bcTextFlag() const;
		virtual void setBcTextFlag( bool value );


		//
		// Virtual Barcode Property: bcChecksumFlag
		//
		Q_PROPERTY( bool bcChecksumFlag READ bcChecksumFlag WRITE setBcChecksumFlag );

		virtual bool bcChecksumFlag() const;
		virtual void setBcChecksumFlag( bool value );


		//
		// Virtual Barcode Property: bcColorNode
		//
		Q_PROPERTY( ColorNode bcColorNode READ bcColorNode WRITE setBcColorNode );

		virtual ColorNode bcColorNode() const;
		virtual void setBcColorNode( const ColorNode &value );
		

		//
		// Virtual Barcode Property: bcStyle
		//
		Q_PROPERTY( BarcodeStyle bcStyle READ bcStyle WRITE setBcStyle );

		virtual BarcodeStyle bcStyle() const;
		virtual void setBcStyle( const BarcodeStyle &value );
		

		//
		// Virtual Barcode Property: bcFormatDigits
		//
		Q_PROPERTY( int bcFormatDigits READ bcFormatDigits WRITE setBcFormatDigits );

		virtual int bcFormatDigits() const;
		virtual void setBcFormatDigits( int value );


		///////////////////////////////////////////////////////////////
		// Capabilities (Overridden by concrete classes.)
		///////////////////////////////////////////////////////////////
	public:
		virtual bool canText() const;
		virtual bool canFill() const;
		virtual bool canLineColor() const;
		virtual bool canLineWidth() const;


		///////////////////////////////////////////////////////////////
		// Position and Size methods
		///////////////////////////////////////////////////////////////
	public:
		void setPosition( double x0, double y0 );
		void setPositionRelative( double dx, double dy );
		void setSize( double w, double h );
		void setSizeHonorAspect( double w, double h );
		void setWHonorAspect( double w );
		void setHHonorAspect( double h );
		LabelRegion getExtent();
		void rotate( double thetaDegs );
		void flipHoriz();
		void flipVert();


		///////////////////////////////////////////////////////////////
		// QGraphicsItem methods
		///////////////////////////////////////////////////////////////
	public:
		virtual QGraphicsItem* createGraphicsItem() = 0;
		virtual void updateGraphicsItem( QGraphicsItem* graphicsItem ) = 0;

	protected:
		void updateGraphicsItemMatrix( QGraphicsItem* graphicsItem );
		void updateGraphicsItemShadow( QGraphicsItem* graphicsItem );


		///////////////////////////////////////////////////////////////
		// Private Members
		///////////////////////////////////////////////////////////////
	private:
		static int msNextId;
		int        mId;

		bool       mSelectedFlag;

		double     mX0;
		double     mY0;
		double     mW;
		double     mH;

		QTransform mMatrix;

		bool       mShadowState;
		double     mShadowX;
		double     mShadowY;
		double     mShadowOpacity;
		ColorNode  mShadowColorNode;

	};

}

#endif // glabels_LabelModelObject_h
