/*  FrameEllipse.cpp
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

#include "FrameEllipse.h"

#include <cmath>

#include "StrUtil.h"
#include "privateConstants.h"


namespace libglabels
{

	FrameEllipse::FrameEllipse( double w, double h, double waste, QString id )
		: mW(w), mH(h), mWaste(waste), Frame(id)
	{
		mPath.addEllipse( 0, 0, mW, mH );
	}

	FrameEllipse::FrameEllipse( const FrameEllipse& other )
		: mW(other.mW), mH(other.mH), mWaste(other.mWaste), mPath(other.mPath), Frame(other)
	{
	}

	
	Frame* FrameEllipse::dup() const
	{
		return new FrameEllipse( *this );
	}


	double FrameEllipse::w() const
	{
		return mW;
	}

	
	double FrameEllipse::h() const
	{
		return mH;
	}
	

	const QString FrameEllipse::sizeDescription( const Units* units ) const
	{
		if ( units->id() == "in" )
		{
			QString wStr = StrUtil::formatFraction( mW * units->unitsPerPoint() );
			QString hStr = StrUtil::formatFraction( mH * units->unitsPerPoint() );

			return QString().sprintf( "%s x %s %s",
						  qPrintable(wStr),
						  qPrintable(hStr),
						  qPrintable(units->name()) );
		}
		else
		{
			return QString().sprintf( "%.5g x %.5g %s",
						  mW * units->unitsPerPoint(),
						  mH * units->unitsPerPoint(),
						  qPrintable(units->name()) );
		}
	}


	bool FrameEllipse::isSimilarTo( Frame* other ) const
	{
		if ( FrameEllipse* otherEllipse = dynamic_cast<FrameEllipse*>(other) )
		{
			if ( (fabs( mW - otherEllipse->mW ) <= Constants::EPSILON) &&
			     (fabs( mH - otherEllipse->mH ) <= Constants::EPSILON) )
			{
				return true;
			}
		}
		return false;
	}


	const QPainterPath& FrameEllipse::path() const
	{
		return mPath;
	}

	
	QPainterPath FrameEllipse::marginPath( double size ) const
	{
		double w = mW - 2*size;
		double h = mH - 2*size;

		QPainterPath path;
		path.addEllipse( size, size, w, h );

		return path;
	}

}

