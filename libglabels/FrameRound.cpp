/*  FrameRound.cpp
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

#include "FrameRound.h"

#include <cmath>

#include "StrUtil.h"
#include "privateConstants.h"


namespace libglabels
{

	FrameRound::FrameRound( double r, double waste, QString id )
		: mR(r), mWaste(waste), Frame(id)
	{
		mPath.addEllipse( 0, 0, 2*mR, 2*mR );
	}
	

	FrameRound::FrameRound( const FrameRound& other )
		: mR(other.mR), mWaste(other.mWaste), mPath(other.mPath), Frame(other)
	{
	}
	

	Frame* FrameRound::dup() const
	{
		return new FrameRound( *this );
	}

	
	double FrameRound::w() const
	{
		return 2*mR;
	}

	
	double FrameRound::h() const
	{
		return 2*mR;
	}

	
	const QString FrameRound::sizeDescription( const Units* units ) const
	{
		if ( units->id() == "in" )
		{
			QString dStr = StrUtil::formatFraction( 2 * mR * units->unitsPerPoint() );

			return QString().sprintf( "%s %s %s",
						  qPrintable(dStr),
						  qPrintable(units->name()),
						  qPrintable(tr("diameter")) );
		}
		else
		{
			return QString().sprintf( "%.5g %s %s",
						  2 * mR * units->unitsPerPoint(),
						  qPrintable(units->name()),
						  qPrintable(tr("diameter")) );
		}
	}


	bool FrameRound::isSimilarTo( Frame* other ) const
	{
		if ( FrameRound *otherRound = dynamic_cast<FrameRound*>(other) )
		{
			if ( fabs( mR - otherRound->mR ) <= Constants::EPSILON )
			{
				return true;
			}
		}
		return false;
	}


	const QPainterPath& FrameRound::path() const
	{
		return mPath;
	}


	QPainterPath FrameRound::marginPath( double size ) const
	{
		double r = mR - size;

		QPainterPath path;
		path.addEllipse( size, size, 2*r, 2*r );

		return path;
	}

}

