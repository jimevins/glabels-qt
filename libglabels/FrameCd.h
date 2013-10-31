/*  FrameCd.h
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

#ifndef libglabels_FrameCd_h
#define libglabels_FrameCd_h

#include "Frame.h"


namespace libglabels
{

	class FrameCd : public Frame
	{
	public:
		FrameCd( double r1,
			 double r2,
			 double  w,
			 double  h,
			 double  waste,
			 QString id = "0" )
			: mR1(r1), mR2(r2), mW(w), mH(h), mWaste(waste), Frame(id)
		{
		}

		inline double r1() const { return mR1; }
		inline double r2() const { return mR2; }
		inline double waste() const { return mWaste; }

		double w() const { return (mW == 0) ? 2*mR1 : mW; }
		double h() const { return (mH == 0) ? 2*mR1 : mH; }

		const QString &sizeDescription( Units *units );
		bool isSimilar( Frame *b ) const;


	private:
		double mR1;
		double mR2;
		double mW;
		double mH;
		double mWaste;

		QString mSizeDescription;

	};

}

#endif // libglabels_FrameCd_h
