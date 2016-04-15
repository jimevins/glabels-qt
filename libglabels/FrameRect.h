/*  FrameRect.h
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

#ifndef glabels_FrameRect_h
#define glabels_FrameRect_h

#include "Frame.h"


namespace glabels
{

	class FrameRect : public Frame
	{
	public:
		FrameRect( const Distance& w,
			   const Distance& h,
		           const Distance& r,
			   const Distance& xWaste,
		           const Distance& yWaste,
		           const QString&  id = "0" );

		FrameRect( const FrameRect& other );

		Frame* dup() const;

		Distance r() const;
		Distance xWaste() const;
		Distance yWaste() const;

		Distance w() const;
		Distance h() const;

		const QString sizeDescription( const Units& units ) const;

		bool isSimilarTo( Frame* other ) const;

		const QPainterPath& path() const;
		QPainterPath marginPath( const Distance& size ) const;


	private:
		Distance mW;
		Distance mH;
		Distance mR;
		Distance mXWaste;
		Distance mYWaste;

		QPainterPath mPath;

	};

}


#include "FrameRect.inl"


#endif // glabels_FrameRect_h
