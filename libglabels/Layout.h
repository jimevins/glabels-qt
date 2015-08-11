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
		Layout( int nx, int ny, double x0, double y0, double dx, double dy );

		Layout( const Layout &other );

		int nx() const;
		int ny() const;

		double x0() const;
		double y0() const;

		double dx() const;
		double dy() const;

		bool isSimilarTo( const Layout *other );

		Layout* dup() const;


	private:
		int     mNx;
		int     mNy;
		double  mX0;
		double  mY0;
		double  mDx;
		double  mDy;
		
	};

}


#include "Layout.inl"


#endif // libglabels_Layout_h
