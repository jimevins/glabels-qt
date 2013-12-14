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


namespace libglabels
{

	const QString FrameCd::sizeDescription( const Units *units ) const
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


	bool FrameCd::isSimilarTo( Frame *other ) const
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


	void FrameCd::initPath()
	{
		// Outer path (may be clipped in the case business card type CD)
		double theta1 = acos( w() / (2*mR1) ) * 180/M_PI;
		double theta2 = asin( h() / (2*mR1) ) * 180/M_PI;

		mPath.arcMoveTo( 0, 0, 2*mR1, 2*mR1, theta1 );
		mPath.arcTo( 0, 0, 2*mR1, 2*mR1, theta1,     theta2-theta1 );
		mPath.arcTo( 0, 0, 2*mR1, 2*mR1, 180-theta2, theta2-theta1 );
		mPath.arcTo( 0, 0, 2*mR1, 2*mR1, 180+theta1, theta2-theta1 );
		mPath.arcTo( 0, 0, 2*mR1, 2*mR1, 360-theta2, theta2-theta1 );
		mPath.closeSubpath();

		// Inner path (hole)
		mPath.addEllipse( mR1-mR2, mR1-mR2, 2*mR2, 2*mR2 );

		// Translate to account for offset with clipped business card CDs (applies to element already drawn)
		mPath.translate( w()/2 - mR1, h()/2 - mR1 );
	}


	QGraphicsItem* FrameCd::createMarginGraphicsItem( double size, const QPen& pen ) const
	{
		double r1 = mR1 - size;
		double r2 = mR2 + size;

		QPainterPath path;

		// Outer path (may be clipped in the case business card type CD)
		double theta1 = acos( (mW-2*size) / (2*r1) ) * 180/M_PI;
		double theta2 = asin( (mH-2*size) / (2*r1) ) * 180/M_PI;

		path.arcMoveTo( 0, 0, 2*r1, 2*r1, theta1 );
		path.arcTo( 0, 0, 2*r1, 2*r1, theta1,     theta2-theta1 );
		path.arcTo( 0, 0, 2*r1, 2*r1, 180-theta2, theta2-theta1 );
		path.arcTo( 0, 0, 2*r1, 2*r1, 180+theta1, theta2-theta1 );
		path.arcTo( 0, 0, 2*r1, 2*r1, 360-theta2, theta2-theta1 );
		path.closeSubpath();

		// Inner path (hole)
		path.addEllipse( r1-r2, r1-r2, 2*r2, 2*r2 );

		// Translate to account for offset with clipped business card CDs (applies to element already drawn)
		path.translate( mW/2 - r1, mH/2 - r1 );

		QGraphicsPathItem* item = new QGraphicsPathItem( path );
		item->setPen( pen );

		return item;
	}

}

