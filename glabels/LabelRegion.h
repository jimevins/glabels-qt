/*  LabelRegion.h
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

#ifndef glabels_LabelRegion_h
#define glabels_LabelRegion_h

#include <QRectF>
#include "libglabels/Distance.h"


namespace glabels
{

	///
	/// Label Region Type
	///
	struct LabelRegion
	{

		/////////////////////////////////
		// Properties
		/////////////////////////////////
	public:
		//
		// X1 Property
		//
		libglabels::Distance x1( void ) const;
		void setX1( const libglabels::Distance& value );


		//
		// Y1 Property
		//
		libglabels::Distance y1( void ) const;
		void setY1( const libglabels::Distance& value );


		//
		// X2 Property
		//
		libglabels::Distance x2( void ) const;
		void setX2( const libglabels::Distance& value );



		//
		// Y2 Property
		//
		libglabels::Distance y2( void ) const;
		void setY2( const libglabels::Distance& value );


		/////////////////////////////////
		// Methods
		/////////////////////////////////
	public:
		QRectF rect() const;


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		libglabels::Distance mX1;
		libglabels::Distance mY1;
		libglabels::Distance mX2;
		libglabels::Distance mY2;
	};


	/////////////////////////////////
	// INLINE METHODS
	/////////////////////////////////
	inline libglabels::Distance LabelRegion::x1( void ) const
	{
		return mX1;
	}


	inline void LabelRegion::setX1( const libglabels::Distance& value )
	{
		mX1 = value;
	}


	inline libglabels::Distance LabelRegion::y1( void ) const
	{
		return mY1;
	}


	inline void LabelRegion::setY1( const libglabels::Distance& value )
	{
		mY1 = value;
	}


	inline libglabels::Distance LabelRegion::x2( void ) const
	{
		return mX2;
	}


	inline void LabelRegion::setX2( const libglabels::Distance& value )
	{
		mX2 = value;
	}


	inline libglabels::Distance LabelRegion::y2( void ) const
	{
		return mY2;
	}


	inline void LabelRegion::setY2( const libglabels::Distance& value )
	{
		mY2 = value;
	}

}

#endif // glabels_LabelRegion_h
