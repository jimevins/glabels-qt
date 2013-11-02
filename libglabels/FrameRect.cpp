/*  FrameRect.cpp
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

#include "FrameRect.h"

#include <cmath>

#include "StrUtil.h"
#include "privateConstants.h"


namespace libglabels
{

	const QString &FrameRect::sizeDescription( Units *units )
	{
		if ( units->id() == "in" )
		{
			QString wStr = StrUtil::formatFraction( mW * units->unitsPerPoint() );
			QString hStr = StrUtil::formatFraction( mH * units->unitsPerPoint() );

			mSizeDescription = QString().sprintf( "%s x %s %s",
							      wStr.toStdString().c_str(),
							      hStr.toStdString().c_str(),
							      units->name().toStdString().c_str() );
		}
		else
		{
			mSizeDescription = QString().sprintf( "%.5g x %.5g %s",
							      mW * units->unitsPerPoint(),
							      mH * units->unitsPerPoint(),
							      units->name().toStdString().c_str() );
		}

		return mSizeDescription;
	}


	bool FrameRect::isSimilarTo( Frame *other ) const
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


}

