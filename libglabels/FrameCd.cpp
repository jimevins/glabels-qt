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

	const QString &FrameCd::sizeDescription( Units *units )
	{
		if ( units->id() == "in" )
		{
			QString dStr = StrUtil::formatFraction( 2 * mR1 * units->unitsPerPoint() );

			mSizeDescription = QString().sprintf( "%s %s %s",
							      qPrintable(dStr),
							      qPrintable(units->name()),
							      qPrintable(tr("diameter")) );
		}
		else
		{
			mSizeDescription = QString().sprintf( "%.5g %s %s",
							      2 * mR1 * units->unitsPerPoint(),
							      qPrintable(units->name()),
							      qPrintable(tr("diameter")) );
		}

		return mSizeDescription;
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

}

