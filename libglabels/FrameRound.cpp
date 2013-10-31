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

	void FrameRound::getSize( double *w, double *h ) const
	{
		*w = 2*mR;
		*h = 2*mR;
	}


	bool FrameRound::isSimilar( Frame *b ) const
	{
		if ( FrameRound *bRound = dynamic_cast<FrameRound*>(b) )
		{
			if ( fabs( mR - bRound->mR ) <= Constants::EPSILON )
			{
				return true;
			}
		}
		return false;
	}


	QString &FrameRound::getSizeDescription( Units *units ) const
	{
		if ( units->id() == "in" )
		{
			QString dStr = StrUtil::formatFraction( 2 * mR * units->unitsPerPoint() );

			return QString().sprintf( "%s %s %s",
						  dStr.toStdString().c_str(),
						  units->name().toStdString().c_str(),
						  tr("diameter").toStdString().c_str() );
		}
		else
		{
			return QString().sprintf( "%.5g %s %s",
						  2 * mR * units->unitsPerPoint(),
						  units->name().toStdString().c_str(),
						  tr("diameter").toStdString().c_str() );
		}
	}

}

