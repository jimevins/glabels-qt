/*  FrameRound.h
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

#ifndef glabels_FrameRound_h
#define glabels_FrameRound_h

#include "Frame.h"


namespace glabels
{

	class FrameRound : public Frame
	{

	public:
		FrameRound( const Distance& r,
		            const Distance& waste,
		            const QString&  id = "0" );

		FrameRound( const FrameRound &other );

		Frame *dup() const;

		Distance r() const;
		Distance waste() const;

		Distance w() const;
		Distance h() const;

		const QString sizeDescription( Distance::Units units ) const;
		bool isSimilarTo( Frame* other ) const;

		const QPainterPath& path() const;
		QPainterPath marginPath( const Distance& size ) const;


	private:
		Distance mR;
		Distance mWaste;

		QPainterPath mPath;

	};

}


#include "FrameRound.inl"


#endif // glabels_FrameRound_h
