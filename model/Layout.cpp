/*  Layout.cpp
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

#include "Layout.h"

#include "Constants.h"

#include <cmath>


namespace glabels
{
	namespace model
	{

		Layout::Layout( int             nx,
		                int             ny,
		                const Distance& x0,
		                const Distance& y0,
		                const Distance& dx,
		                const Distance& dy )
			: mNx(nx), mNy(ny), mX0(x0), mY0(y0), mDx(dx), mDy(dy)
		{
			// empty
		}

	
		Layout::Layout( const Layout& other )
			: mNx(other.mNx), mNy(other.mNy), mX0(other.mX0), mY0(other.mY0),
			  mDx(other.mDx), mDy(other.mDy)
		{
			// empty
		}


		int Layout::nx() const
		{
			return mNx;
		}

		
		int Layout::ny() const
		{
			return mNy;
		}
		

		Distance Layout::x0() const
		{
			return mX0;
		}

		
		Distance Layout::y0() const
		{
			return mY0;
		}
		

		Distance Layout::dx() const
		{
			return mDx;
		}

		
		Distance Layout::dy() const
		{
			return mDy;
		}


		bool Layout::isSimilarTo( const Layout& other ) const
		{
			return ( (mNx == other.mNx)                &&
			         (mNy == other.mNy)                &&
			         (fabs(mX0 - other.mX0) < EPSILON) &&
			         (fabs(mY0 - other.mY0) < EPSILON) &&
			         (fabs(mDx - other.mDx) < EPSILON) &&
			         (fabs(mDy - other.mDy) < EPSILON) );
		}

	}
}


QDebug operator<<( QDebug dbg, const glabels::model::Layout& layout )
{
	QDebugStateSaver saver(dbg);

	dbg.nospace() << "Layout{ "
	              << layout.nx() << "," 
	              << layout.ny() << "," 
	              << layout.x0() << "," 
	              << layout.y0() << "," 
	              << layout.dx() << "," 
	              << layout.dy()
	              << " }";

	return dbg;
}
