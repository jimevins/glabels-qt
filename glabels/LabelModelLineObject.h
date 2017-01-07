/*  LabelModelLineObject.h
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

#ifndef LabelModelLineObject_h
#define LabelModelLineObject_h


#include "LabelModelObject.h"


///
/// Label Model Line Object
///
class LabelModelLineObject : public LabelModelObject
{
	Q_OBJECT

	///////////////////////////////////////////////////////////////
	// Lifecycle Methods
	///////////////////////////////////////////////////////////////
public:
	LabelModelLineObject();
	LabelModelLineObject( const LabelModelLineObject* object );
	virtual ~LabelModelLineObject();


	///////////////////////////////////////////////////////////////
	// Object duplication
	///////////////////////////////////////////////////////////////
	virtual LabelModelLineObject* clone() const;


	///////////////////////////////////////////////////////////////
	// Property Implementations
	///////////////////////////////////////////////////////////////
public:
	//
	// Line Property: lineWidth
	//
	virtual glabels::Distance lineWidth( void ) const;
	virtual void setLineWidth( const glabels::Distance& value );


	//
	// Line Property: lineColorNode
	//
	virtual ColorNode lineColorNode( void ) const;
	virtual void setLineColorNode( const ColorNode& value );
		

	///////////////////////////////////////////////////////////////
	// Capability Implementations
	///////////////////////////////////////////////////////////////
public:
	virtual bool canLineColor();
	virtual bool canLineWidth();


	///////////////////////////////////////////////////////////////
	// Drawing operations
	///////////////////////////////////////////////////////////////
protected:
	virtual void drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const;
	virtual void drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const;
	virtual QPainterPath hoverPath( double scale ) const;


	///////////////////////////////////////////////////////////////
	// Private Members
	///////////////////////////////////////////////////////////////
protected:
	glabels::Distance    mLineWidth;
	ColorNode            mLineColorNode;

};


#endif // LabelModelLineObject_h
