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

	bool FrameCd::isSimilar( Frame *b ) const
	{
		if ( FrameCd *bCd = dynamic_cast<FrameCd*>(b) )
		{
			if ( (fabs( mW  - bCd->mW )  <= Constants::EPSILON) &&
			     (fabs( mH  - bCd->mH )  <= Constants::EPSILON) &&
			     (fabs( mR1 - bCd->mR1 ) <= Constants::EPSILON) &&
			     (fabs( mR2 - bCd->mR2 ) <= Constants::EPSILON) )
			{
				return true;
			}
		}
		return false;
	}


	const QString &FrameCd::sizeDescription( Units *units )
	{
		if ( units->id() == "in" )
		{
			QString dStr = StrUtil::formatFraction( 2 * mR1 * units->unitsPerPoint() );

			mSizeDescription = QString().sprintf( "%s %s %s",
							      dStr.toStdString().c_str(),
							      units->name().toStdString().c_str(),
							      tr("diameter").toStdString().c_str() );
		}
		else
		{
			mSizeDescription = QString().sprintf( "%.5g %s %s",
							      2 * mR1 * units->unitsPerPoint(),
							      units->name().toStdString().c_str(),
							      tr("diameter").toStdString().c_str() );
		}

		return mSizeDescription;
	}

}

