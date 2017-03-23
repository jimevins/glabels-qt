/*  LabelModelShapeObject.cpp
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

#include "LabelModelShapeObject.h"


#include <QBrush>
#include <QPen>


namespace glabels
{

	///
	/// Constructor
	///
	LabelModelShapeObject::LabelModelShapeObject()
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

		mLineWidth       = 1.0;
		mLineColorNode   = ColorNode( QColor( 0, 0, 0 ) );
		mFillColorNode   = ColorNode( QColor( 0, 255, 0 ) );
	}


	///
	/// Copy constructor
	///
	LabelModelShapeObject::LabelModelShapeObject( const LabelModelShapeObject* object ) : LabelModelObject(object)
	{
		mLineWidth       = object->mLineWidth;
		mLineColorNode   = object->mLineColorNode;
		mFillColorNode   = object->mFillColorNode;
	}


	///
	/// Destructor
	///
	LabelModelShapeObject::~LabelModelShapeObject()
	{
		delete mOutline;

		foreach( Handle* handle, mHandles )
		{
			delete handle;
		}
		mHandles.clear();
	}


	///
	/// Line Width Property Getter
	///
	Distance LabelModelShapeObject::lineWidth() const
	{
		return mLineWidth;
	}


	///
	/// Line Width Property Setter
	///
	void LabelModelShapeObject::setLineWidth( const Distance& value )
	{
		if ( mLineWidth != value )
		{
			mLineWidth = value;
			emit changed();
		}
	}


	///
	/// Line Color Node Property Getter
	///
	ColorNode LabelModelShapeObject::lineColorNode() const
	{
		return mLineColorNode;
	}


	///
	/// Line Color Node Property Setter
	///
	void LabelModelShapeObject::setLineColorNode( const ColorNode& value )
	{
		if ( mLineColorNode != value )
		{
			mLineColorNode = value;
			emit changed();
		}
	}
		

	///
	/// Fill Color Node Property Getter
	///
	ColorNode LabelModelShapeObject::fillColorNode() const
	{
		return mFillColorNode;
	}


	///
	/// Fill Color Node Property Setter
	///
	void LabelModelShapeObject::setFillColorNode( const ColorNode& value )
	{
		if ( mFillColorNode != value )
		{
			mFillColorNode = value;
			emit changed();
		}
	}
		

	///
	/// Can Fill Capability Implementation
	///
	bool LabelModelShapeObject::canFill()
	{
		return true;
	}


	///
	/// Can Line Color Capability Implementation
	///
	bool LabelModelShapeObject::canLineColor()
	{
		return true;
	}


	///
	/// Can Line Width Capability Implementation
	///
	bool LabelModelShapeObject::canLineWidth()
	{
		return true;
	}

}
