/*  FrameCd.cpp
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

#include "FrameCd.h"

#include <cmath>

#include "StrUtil.h"
#include "privateConstants.h"
#include <QtDebug>


namespace libglabels
{

	FrameCd::FrameCd( double r1, double r2, double w, double h, double waste, QString id )
		: mR1(r1), mR2(r2), mW(w), mH(h), mWaste(waste), Frame(id)
	{
		double wReal = (mW == 0) ? 2*mR1 : mW;
		double hReal = (mH == 0) ? 2*mR1 : mH;

		/*
		 * Construct outer subpath (may be clipped if it's a business card CD)
		 */
		QPainterPath outerPath;
		outerPath.addEllipse( wReal/2 - r1, hReal/2 - r1, 2*r1, 2*r1 );

		QPainterPath clipPath;
		clipPath.addRect( 0, 0, wReal, hReal );

		mPath.addPath( outerPath & clipPath );
		mPath.closeSubpath();

		/*
		 * Add inner subpath
		 */
		mPath.addEllipse( wReal/2 - r2, hReal/2 - r2, 2*r2, 2*r2 );
	}


	FrameCd::FrameCd( const FrameCd& other )
		: mR1(other.mR1), mR2(other.mR2), mW(other.mW), mH(other.mH), mWaste(other.mWaste),
		  mPath(other.mPath), Frame(other)
	{
	}

	
	Frame* FrameCd::dup() const
	{
		return new FrameCd( *this );
	}
	

	double FrameCd::w() const
	{
		return (mW == 0) ? 2*mR1 : mW;
	}

	
	double FrameCd::h() const
	{
		return (mH == 0) ? 2*mR1 : mH;
	}


	const QString FrameCd::sizeDescription( const Units* units ) const
	{
		if ( units->id() == "in" )
		{
			QString dStr = StrUtil::formatFraction( 2 * mR1 * units->unitsPerPoint() );

			return QString().sprintf( "%s %s %s",
						  qPrintable(dStr),
						  qPrintable(units->name()),
						  qPrintable(tr("diameter")) );
		}
		else
		{
			return QString().sprintf( "%.5g %s %s",
						  2 * mR1 * units->unitsPerPoint(),
						  qPrintable(units->name()),
						  qPrintable(tr("diameter")) );
		}
	}


	bool FrameCd::isSimilarTo( Frame* other ) const
	{
		if ( FrameCd *otherCd = dynamic_cast<FrameCd*>(other) )
		{
			if ( (fabs( mW  - otherCd->mW )  <= Constants::EPSILON) &&
			     (fabs( mH  - otherCd->mH )  <= Constants::EPSILON) &&
			     (fabs( mR1 - otherCd->mR1 ) <= Constants::EPSILON) &&
			     (fabs( mR2 - otherCd->mR2 ) <= Constants::EPSILON) )
			{
				return true;
			}
		}
		return false;
	}


	const QPainterPath& FrameCd::path() const
	{
		return mPath;
	}
	

	QPainterPath FrameCd::marginPath( double size ) const
	{
		double wReal = (mW == 0) ? 2*mR1 : mW;
		double hReal = (mH == 0) ? 2*mR1 : mH;

		double r1 = mR1 - size;
		double r2 = mR2 + size;

		QPainterPath path;

		/*
		 * Construct outer subpath (may be clipped if it's a business card CD)
		 */
		QPainterPath outerPath;
		outerPath.addEllipse( wReal/2 - r1, hReal/2 - r1, 2*r1, 2*r1 );

		QPainterPath clipPath;
		clipPath.addRect( size, size, wReal-2*size, hReal-2*size );

		path.addPath( outerPath & clipPath );
		path.closeSubpath();

		/*
		 * Add inner subpath
		 */
		path.addEllipse( wReal/2 - r2, hReal/2 - r2, 2*r2, 2*r2 );

		return path;
	}

}

