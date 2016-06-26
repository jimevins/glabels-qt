/*  LabelModelImageObject.h
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

#ifndef LabelModelImageObject_h
#define LabelModelImageObject_h

#include "LabelModelObject.h"


///
/// Label Model Image Object
///
class LabelModelImageObject : public LabelModelObject
{
	Q_OBJECT

	///////////////////////////////////////////////////////////////
	// Lifecycle Methods
	///////////////////////////////////////////////////////////////
public:
	LabelModelImageObject();
	LabelModelImageObject( const LabelModelImageObject* object );
	virtual ~LabelModelImageObject();


	///////////////////////////////////////////////////////////////
	// Object duplication
	///////////////////////////////////////////////////////////////
	virtual LabelModelImageObject* clone() const;


	///////////////////////////////////////////////////////////////
	// Property Implementations
	///////////////////////////////////////////////////////////////
public:
	//
	// Image Property: filenameNode
	//
	virtual TextNode filenameNode( void ) const;
	virtual void setFilenameNode( const TextNode& value );


	///////////////////////////////////////////////////////////////
	// Capability Implementations
	///////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////
	// Drawing operations
	///////////////////////////////////////////////////////////////
protected:
	virtual void drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const;
	virtual void drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const;
	virtual QPainterPath hoverPath( double scale ) const;


	///////////////////////////////////////////////////////////////
	// Private
	///////////////////////////////////////////////////////////////
	void loadImage();
	QImage* createShadowImage( const QColor& color ) const;
	

	///////////////////////////////////////////////////////////////
	// Private Members
	///////////////////////////////////////////////////////////////
protected:
	TextNode       mFilenameNode;
	QImage*        mImage;

	static QImage* smDefaultImage;

};


#endif // LabelModelImageObject_h
