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
		inline double x1( void ) const;
		inline void setX1( double value );


		//
		// Y1 Property
		//
		inline double y1( void ) const;
		inline void setY1( double value );


		//
		// X2 Property
		//
		inline double x2( void ) const;
		inline void setX2( double value );



		//
		// Y2 Property
		//
		inline double y2( void ) const;
		inline void setY2( double value );


		/////////////////////////////////
		// Methods
		/////////////////////////////////
	public:
		QRectF rect() const;


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		double mX1;
		double mY1;
		double mX2;
		double mY2;
	};


	/////////////////////////////////
	// INLINE METHODS
	/////////////////////////////////
	double LabelRegion::x1( void ) const
	{
		return mX1;
	}


	void LabelRegion::setX1( double value )
	{
		mX1 = value;
	}


	double LabelRegion::y1( void ) const
	{
		return mY1;
	}


	void LabelRegion::setY1( double value )
	{
		mY1 = value;
	}


	double LabelRegion::x2( void ) const
	{
		return mX2;
	}


	void LabelRegion::setX2( double value )
	{
		mX2 = value;
	}


	double LabelRegion::y2( void ) const
	{
		return mY2;
	}


	void LabelRegion::setY2( double value )
	{
		mY2 = value;
	}

}

#endif // glabels_LabelRegion_h
