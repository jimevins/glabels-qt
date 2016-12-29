/*  LabelModelObject.h
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

#ifndef LabelModelObject_h
#define LabelModelObject_h

#include <QObject>
#include <QFont>
#include <QMatrix>
#include <QPainter>

#include "libglabels/Distance.h"
#include "Merge/Record.h"
#include "ColorNode.h"
#include "TextNode.h"
#include "BarcodeStyle.h"
#include "Handles.h"
#include "Outline.h"


// Forward References
class LabelRegion;


///
/// Label Model Object Base Class
///
class LabelModelObject : public QObject
{
	Q_OBJECT

	///////////////////////////////////////////////////////////////
	// Lifecycle Methods
	///////////////////////////////////////////////////////////////
protected:
	LabelModelObject();
	LabelModelObject( const LabelModelObject* object );
public:
	virtual ~LabelModelObject();


	///////////////////////////////////////////////////////////////
	// Object duplication
	///////////////////////////////////////////////////////////////
	virtual LabelModelObject* clone() const = 0;

	
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
	int id() const;

	//
	// Selected Property.
	//
	bool isSelected() const;
	void select( bool value = true );
	void unselect();


	//
	// x0 Property ( x coordinate of origin )
	//
	glabels::Distance x0() const;
	void setX0( const glabels::Distance& value );
		

	//
	// y0 Property ( y coordinate of origin )
	//
	glabels::Distance y0() const;
	void setY0( const glabels::Distance& value );
		

	//
	// w Property ( width of bounding box )
	//
	glabels::Distance w() const;
	void setW( const glabels::Distance& value );
		

	//
	// h Property ( height of bounding box )
	//
	glabels::Distance h() const;
	void setH( const glabels::Distance& value );


	//
	// Transformation Matrix Property
	//
	QMatrix matrix() const;
	void setMatrix( const QMatrix& value );


	//
	// Shadow State Property
	//
	bool shadow() const;
	void setShadow( bool value );


	//
	// Shadow x Offset Property
	//
	glabels::Distance shadowX() const;
	void setShadowX( const glabels::Distance& value );
		

	//
	// Shadow y Offset Property
	//
	glabels::Distance shadowY() const;
	void setShadowY( const glabels::Distance& value );
		

	//
	// Shadow opacity Property
	//
	double shadowOpacity() const;
	void setShadowOpacity( double value );
		

	//
	// Shadow Color Property
	//
	ColorNode shadowColorNode() const;
	void setShadowColorNode( const ColorNode& value );
		

	///////////////////////////////////////////////////////////////
	// Text Properties Virtual Interface
	///////////////////////////////////////////////////////////////
public:
	//
	// Virtual Text Property: text
	//
	virtual QString text() const;
	virtual void setText( const QString &value );


	//
	// Virtual Text Property: fontFamily
	//
	virtual QString fontFamily() const;
	virtual void setFontFamily( const QString &value );


	//
	// Virtual Text Property: fontSize
	//
	virtual double fontSize() const;
	virtual void setFontSize( double value );


	//
	// Virtual Text Property: fontWeight
	//
	virtual QFont::Weight fontWeight() const;
	virtual void setFontWeight( QFont::Weight value );


	//
	// Virtual Text Property: fontItalicFlag
	//
	virtual bool fontItalicFlag() const;
	virtual void setFontItalicFlag( bool value );


	//
	// Virtual Text Property: fontUnderlineFlag
	//
	virtual bool fontUnderlineFlag() const;
	virtual void setFontUnderlineFlag( bool value );


	//
	// Virtual Text Property: textColorNode
	//
	virtual ColorNode textColorNode() const;
	virtual void setTextColorNode( const ColorNode &value );
		

	//
	// Virtual Text Property: textHAlign
	//
	virtual Qt::Alignment textHAlign() const;
	virtual void setTextHAlign( Qt::Alignment value );


	//
	// Virtual Text Property: textVAlign
	//
	virtual Qt::Alignment textVAlign() const;
	virtual void setTextVAlign( Qt::Alignment value );


	//
	// Virtual Text Property: textLineSpacing
	//
	virtual double textLineSpacing() const;
	virtual void setTextLineSpacing( double value );


	///////////////////////////////////////////////////////////////
	// Image Properties Virtual Interface
	///////////////////////////////////////////////////////////////
public:
	//
	// Virtual Image Property: filenameNode
	//
	virtual TextNode filenameNode() const;
	virtual void setFilenameNode( const TextNode &value );
		

	///////////////////////////////////////////////////////////////
	// Shape Properties Virtual Interface
	///////////////////////////////////////////////////////////////
public:
	//
	// Virtual Shape Property: lineWidth
	//
	virtual glabels::Distance lineWidth() const;
	virtual void setLineWidth( const glabels::Distance& value );


	//
	// Virtual Shape Property: lineColorNode
	//
	virtual ColorNode lineColorNode() const;
	virtual void setLineColorNode( const ColorNode &value );
		

	//
	// Virtual Shape Property: fillColorNode
	//
	virtual ColorNode fillColorNode() const;
	virtual void setFillColorNode( const ColorNode &value );
		

	///////////////////////////////////////////////////////////////
	// Barcode Properties Virtual Interface
	///////////////////////////////////////////////////////////////
public:
	//
	// Virtual Barcode Property: bcDataNode
	//
	virtual TextNode bcDataNode() const;
	virtual void setBcDataNode( const TextNode &value );
		

	//
	// Virtual Barcode Property: bcTextFlag
	//
	virtual bool bcTextFlag() const;
	virtual void setBcTextFlag( bool value );


	//
	// Virtual Barcode Property: bcChecksumFlag
	//
	virtual bool bcChecksumFlag() const;
	virtual void setBcChecksumFlag( bool value );


	//
	// Virtual Barcode Property: bcColorNode
	//
	virtual ColorNode bcColorNode() const;
	virtual void setBcColorNode( const ColorNode &value );
		

	//
	// Virtual Barcode Property: bcStyle
	//
	virtual BarcodeStyle bcStyle() const;
	virtual void setBcStyle( const BarcodeStyle &value );
		

	//
	// Virtual Barcode Property: bcFormatDigits
	//
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
	void setPosition( const glabels::Distance& x0, const glabels::Distance& y0 );
	void setPositionRelative( const glabels::Distance& dx, const glabels::Distance& dy );
	void setSize( const glabels::Distance& w, const glabels::Distance& h );
	void setSizeHonorAspect( const glabels::Distance& w, const glabels::Distance& h );
	void setWHonorAspect( const glabels::Distance& w );
	void setHHonorAspect( const glabels::Distance& h );
	LabelRegion getExtent();
	void rotate( double thetaDegs );
	void flipHoriz();
	void flipVert();
	bool isLocatedAt( double scale, const glabels::Distance& x, const glabels::Distance& y ) const;
	Handle* handleAt( double scale, const glabels::Distance& x, const glabels::Distance& y ) const;


	///////////////////////////////////////////////////////////////
	// Drawing operations
	///////////////////////////////////////////////////////////////
public:
	void draw( QPainter* painter, bool inEditor, merge::Record* record ) const;
	void drawSelectionHighlight( QPainter* painter, double scale ) const;

protected:
	virtual void drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const = 0;
	virtual void drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const = 0;
	virtual QPainterPath hoverPath( double scale ) const = 0;

	virtual void sizeUpdated();

		
	///////////////////////////////////////////////////////////////
	// Protected Members
	///////////////////////////////////////////////////////////////
protected:
	bool              mSelectedFlag;

	glabels::Distance mX0;
	glabels::Distance mY0;
	glabels::Distance mW;
	glabels::Distance mH;

	bool              mShadowState;
	glabels::Distance mShadowX;
	glabels::Distance mShadowY;
	double            mShadowOpacity;
	ColorNode         mShadowColorNode;

	QList<Handle*>    mHandles;
	Outline*          mOutline;


	///////////////////////////////////////////////////////////////
	// Private Members
	///////////////////////////////////////////////////////////////
private:
	static int msNextId;
	int        mId;

	QMatrix    mMatrix;

};


#endif // LabelModelObject_h
