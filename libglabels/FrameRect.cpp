/*  FrameRect.cpp
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

#include "FrameRect.h"

#include <cmath>

#include "StrUtil.h"
#include "privateConstants.h"


namespace libglabels
{

	FrameRect::FrameRect( const Distance& w,
			      const Distance& h,
			      const Distance& r,
			      const Distance& xWaste,
			      const Distance& yWaste,
			      const QString&  id )
		: mW(w), mH(h), mR(r), mXWaste(xWaste), mYWaste(yWaste), Frame(id)
	{
		mPath.addRoundedRect( 0, 0, mW.pt(), mH.pt(), mR.pt(), mR.pt() );
	}

	
	FrameRect::FrameRect( const FrameRect &other )
		: mW(other.mW), mH(other.mH), mR(other.mR), mXWaste(other.mXWaste),
		  mYWaste(other.mYWaste), mPath(other.mPath), Frame(other)
	{
	}

	
	Frame* FrameRect::dup() const
	{
		return new FrameRect( *this );
	}


	Distance FrameRect::w() const
	{
		return mW;
	}

	
	Distance FrameRect::h() const
	{
		return mH;
	}


	const QString FrameRect::sizeDescription( Distance::Units units ) const
	{
		if ( units == Distance::Units::IN )
		{
			QString wStr = StrUtil::formatFraction( mW.in() );
			QString hStr = StrUtil::formatFraction( mH.in() );

			return QString().sprintf( "%s x %s %s",
						  qPrintable(wStr),
						  qPrintable(hStr),
						  qPrintable(Distance::toTrName(units)) );
		}
		else
		{
			return QString().sprintf( "%.5g x %.5g %s",
						  mW.inUnits(units),
						  mH.inUnits(units),
						  qPrintable(Distance::toTrName(units)) );
		}
	}


	bool FrameRect::isSimilarTo( Frame* other ) const
	{
		if ( FrameRect *otherRect = dynamic_cast<FrameRect*>(other) )
		{
			if ( (fabs( mW - otherRect->mW ) <= Constants::EPSILON) &&
			     (fabs( mH - otherRect->mH ) <= Constants::EPSILON) )
			{
				return true;
			}
		}
		return false;
	}


	const QPainterPath& FrameRect::path() const
	{
		return mPath;
	}


	QPainterPath FrameRect::marginPath( const Distance& size ) const
	{
		Distance w = mW - 2*size;
		Distance h = mH - 2*size;
		Distance r = std::max( mR - size, Distance(0.0) );

		QPainterPath path;
		path.addRoundedRect( size.pt(), size.pt(), w.pt(), h.pt(), r.pt(), r.pt() );

		return path;
	}


}

