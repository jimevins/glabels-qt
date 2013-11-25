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


namespace glabels
{

	struct LabelRegion
	{
	public:
		inline double x1( void ) const { return mX1; }
		inline void x1( double value ) { mX1 = value; }

		inline double y1( void ) const { return mY1; }
		inline void y1( double value ) { mY1 = value; }

		inline double x2( void ) const { return mX2; }
		inline void x2( double value ) { mX2 = value; }

		inline double y2( void ) const { return mY2; }
		inline void y2( double value ) { mY2 = value; }


	private:
		double mX1;
		double mY1;
		double mX2;
		double mY2;
	};

}

#endif // glabels_LabelRegion_h
