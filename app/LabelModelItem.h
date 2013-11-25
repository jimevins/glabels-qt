/*  LabelModelItem.h
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

#ifndef glabels_LabelModelItem_h
#define glabels_LabelModelItem_h

#include <QObject>
#include <QTransform>
#include <QFont>
#include <QPainter>

#include "ColorNode.h"
#include "TextNode.h"
#include "BarcodeStyle.h"
#include "LabelRegion.h"
#include "MergeRecord.h"


namespace glabels
{

	class LabelModelItem : public QObject
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	public:
		LabelModelItem( QObject *parent );
		virtual ~LabelModelItem() {}


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
		/*
		 * Selected Property.
		 */
		Q_PROPERTY( bool selected READ isSelected WRITE select RESET unselect )

		bool isSelected( void ) { return mSelectedFlag; }
		void select( bool value = true ) { mSelectedFlag = value; }
		void unselect( void ) { mSelectedFlag = false; }


		/*
		 * x0 Property ( x coordinate of origin )
		 */
		Q_PROPERTY( double x0 READ x0 WRITE x0 );

		double x0( void ) { return mX0; }
		void x0( double value )
		{
			if ( mX0 != value ) { mX0 = value; emit moved(); }
		}
		

		/*
		 * y0 Property ( y coordinate of origin )
		 */
		Q_PROPERTY( double y0 READ y0 WRITE y0 );

		double y0( void ) { return mY0; }
		void y0( double value )
		{
			if ( mY0 != value ) { mY0 = value; emit moved(); }
		}
		

		/*
		 * w Property ( width of bounding box )
		 */
		Q_PROPERTY( double w  READ w  WRITE w );

		double w( void ) { return mW; }
		void w( double value )
		{
			if ( mW != value ) { mW = value; emit moved(); }
		}
		

		/*
		 * h Property ( height of bounding box )
		 */
		Q_PROPERTY( double h  READ h  WRITE h );

		double h( void ) { return mH; }
		void h( double value )
		{
			if ( mH != value ) { mH = value; emit moved(); }
		}


		/*
		 * Transformation Matrix Property
		 */
		Q_PROPERTY( QTransform matrix READ matrix WRITE matrix );

		QTransform matrix( void ) { return mMatrix; }
		void matrix( const QTransform &value )
		{
			if ( mMatrix != value ) { mMatrix = value; emit changed(); }
		}


		/*
		 * Shadow State Property
		 */
		Q_PROPERTY( bool shadow READ shadow WRITE shadow );

		bool shadow( void ) { return mShadowState; }
		void shadow( bool value )
		{
			if ( mShadowState != value ) { mShadowState = value; emit changed(); }
		}


		/*
		 * Shadow x Offset Property
		 */
		Q_PROPERTY( double shadowX READ shadowX WRITE shadowX );

		double shadowX( void ) { return mShadowX; }
		void shadowX( double value )
		{
			if ( mShadowX != value ) { mShadowX = value; emit changed(); }
		}
		

		/*
		 * Shadow y Offset Property
		 */
		Q_PROPERTY( double shadowY READ shadowY WRITE shadowY );

		double shadowY( void ) { return mShadowY; }
		void shadowY( double value )
		{
			if ( mShadowY != value ) { mShadowY = value; emit changed(); }
		}
		

		/*
		 * Shadow opacity Property
		 */
		Q_PROPERTY( double shadowOpacity READ shadowOpacity WRITE shadowOpacity );

		double shadowOpacity( void ) { return mShadowOpacity; }
		void shadowOpacity( double value )
		{
			if ( mShadowOpacity != value ) { mShadowOpacity = value; emit changed(); }
		}
		

		/*
		 * Shadow Color Property
		 */
		Q_PROPERTY( ColorNode shadowColorNode READ shadowColorNode WRITE shadowColorNode );

		ColorNode shadowColorNode( void ) { return mShadowColorNode; }
		void shadowColorNode( const ColorNode &value )
		{
			if ( mShadowColorNode != value ) { mShadowColorNode = value; emit changed(); }
		}
		

		///////////////////////////////////////////////////////////////
		// Text Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		/*
		 * Virtual Text Property: fontFamily
		 */
		Q_PROPERTY( QString fontFamily READ fontFamily WRITE fontFamily );

		virtual QString fontFamily( void ) { return ""; }
		virtual void fontFamily( const QString &value ) { }


		/*
		 * Virtual Text Property: fontSize
		 */
		Q_PROPERTY( double fontSize READ fontSize WRITE fontSize );

		virtual double fontSize( void ) { return 0; }
		virtual void fontSize( double value ) { }


		/*
		 * Virtual Text Property: fontWeight
		 */
		Q_PROPERTY( QFont::Weight fontWeight READ fontWeight WRITE fontWeight );

		virtual QFont::Weight fontWeight( void ) { return QFont::Normal; }
		virtual void fontWeight( QFont::Weight value ) { }


		/*
		 * Virtual Text Property: fontItalicFlag
		 */
		Q_PROPERTY( bool fontItalicFlag READ fontItalicFlag WRITE fontItalicFlag );

		virtual bool fontItalicFlag( void ) { return false; }
		virtual void fontItalicFlag( bool value ) { }


		/*
		 * Virtual Text Property: fontUnderlineFlag
		 */
		Q_PROPERTY( bool fontUnderlineFlag READ fontUnderlineFlag WRITE fontUnderlineFlag );

		virtual bool fontUnderlineFlag( void ) { return false; }
		virtual void fontUnderlineFlag( bool value ) { }


		/*
		 * Virtual Text Property: fontColorNode
		 */
		Q_PROPERTY( ColorNode fontColorNode READ fontColorNode WRITE fontColorNode );

		virtual ColorNode fontColorNode( void ) { return ColorNode( QColor::fromRgba(0x00000000) ); }
		virtual void fontColorNode( const ColorNode &value ) { }
		

		/*
		 * Virtual Text Property: textHAlign
		 */
		Q_PROPERTY( Qt::Alignment textHAlign READ textHAlign WRITE textHAlign );

		virtual Qt::Alignment textHAlign( void ) { return Qt::AlignLeft; }
		virtual void textHAlign( Qt::Alignment value ) { }


		/*
		 * Virtual Text Property: textVAlign
		 */
		Q_PROPERTY( Qt::Alignment textVAlign READ textVAlign WRITE textVAlign );

		virtual Qt::Alignment textVAlign( void ) { return Qt::AlignTop; }
		virtual void textVAlign( Qt::Alignment value ) { }


		/*
		 * Virtual Text Property: textLineSpacing
		 */
		Q_PROPERTY( double textLineSpacing READ textLineSpacing WRITE textLineSpacing );

		virtual double textLineSpacing( void ) { return 0; }
		virtual void textLineSpacing( double value ) { }


		///////////////////////////////////////////////////////////////
		// Image Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		/*
		 * Virtual Image Property: filenameNode
		 */
		Q_PROPERTY( TextNode filenameNode READ filenameNode WRITE filenameNode );

		virtual TextNode filenameNode( void ) { return TextNode(); }
		virtual void filenameNode( const TextNode &value ) { }
		

		///////////////////////////////////////////////////////////////
		// Shape Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		/*
		 * Virtual Shape Property: lineWidth
		 */
		Q_PROPERTY( double lineWidth READ lineWidth WRITE lineWidth );

		virtual double lineWidth( void ) { return 0; }
		virtual void lineWidth( double value ) { }


		/*
		 * Virtual Shape Property: lineColorNode
		 */
		Q_PROPERTY( ColorNode lineColorNode READ lineColorNode WRITE lineColorNode );

		virtual ColorNode lineColorNode( void ) { return ColorNode( QColor::fromRgba(0x00000000) ); }
		virtual void lineColorNode( const ColorNode &value ) { }
		

		/*
		 * Virtual Shape Property: fillColorNode
		 */
		Q_PROPERTY( ColorNode fillColorNode READ fillColorNode WRITE fillColorNode );

		virtual ColorNode fillColorNode( void ) { return ColorNode( QColor::fromRgba(0x00000000) ); }
		virtual void fillColorNode( const ColorNode &value ) { }
		

		///////////////////////////////////////////////////////////////
		// Barcode Properties Virtual Interface
		///////////////////////////////////////////////////////////////
	public:
		/*
		 * Virtual Barcode Property: bcDataNode
		 */
		Q_PROPERTY( TextNode bcDataNode READ bcDataNode WRITE bcDataNode );

		virtual TextNode bcDataNode( void ) { return TextNode(); }
		virtual void bcDataNode( const TextNode &value ) { }
		

		/*
		 * Virtual Barcode Property: bcTextFlag
		 */
		Q_PROPERTY( bool bcTextFlag READ bcTextFlag WRITE bcTextFlag );

		virtual bool bcTextFlag( void ) { return false; }
		virtual void bcTextFlag( bool value ) { }


		/*
		 * Virtual Barcode Property: bcChecksumFlag
		 */
		Q_PROPERTY( bool bcChecksumFlag READ bcChecksumFlag WRITE bcChecksumFlag );

		virtual bool bcChecksumFlag( void ) { return false; }
		virtual void bcChecksumFlag( bool value ) { }


		/*
		 * Virtual Barcode Property: bcColorNode
		 */
		Q_PROPERTY( ColorNode bcColorNode READ bcColorNode WRITE bcColorNode );

		virtual ColorNode bcColorNode( void ) { return ColorNode( QColor::fromRgba(0x00000000) ); }
		virtual void bcColorNode( const ColorNode &value ) { }
		

		/*
		 * Virtual Barcode Property: bcStyle
		 */
		Q_PROPERTY( BarcodeStyle bcStyle READ bcStyle WRITE bcStyle );

		virtual BarcodeStyle bcStyle( void ) { return BarcodeStyle(); }
		virtual void bcStyle( const BarcodeStyle &value ) { }
		

		/*
		 * Virtual Barcode Property: bcFormatDigits
		 */
		Q_PROPERTY( int bcFormatDigits READ bcFormatDigits WRITE bcFormatDigits );

		virtual int bcFormatDigits( void ) { return false; }
		virtual void bcFormatDigits( int value ) { }


		///////////////////////////////////////////////////////////////
		// Capabilities (Overridden by concrete classes.)
		///////////////////////////////////////////////////////////////
	public:
		virtual bool canText()	{ return false;	}

		virtual bool canFill()	{ return false;	}

		virtual bool canLineColor() { return false; }

		virtual bool canLineWidth() { return false; }


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
		// Private Members
		///////////////////////////////////////////////////////////////
	private:
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

#endif // glabels_LabelModelItem_h
