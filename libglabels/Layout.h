/*  Layout.h
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

#ifndef libglabels_Layout_h
#define libglabels_Layout_h


namespace libglabels
{

	class Layout
	{
	public:
		Layout( int nx, int ny, double x0, double y0, double dx, double dy )
			: mNx(nx), mNy(ny), mX0(x0), mY0(y0), mDx(dx), mDy(dy)
		{
		}

		inline int    nx() const { return mNx; }
		inline int    ny() const { return mNy; }

		inline double x0() const { return mX0; }
		inline double y0() const { return mY0; }

		inline double dx() const { return mDx; }
		inline double dy() const { return mDy; }

		bool is_similar_to( const Layout &b );


	private:
		int     mNx;
		int     mNy;
		double  mX0;
		double  mY0;
		double  mDx;
		double  mDy;
	};

}

#endif // libglabels_Layout_h
