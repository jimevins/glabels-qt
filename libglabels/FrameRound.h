/*  FrameRound.h
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

#ifndef libglabels_FrameRound_h
#define libglabels_FrameRound_h

#include "Frame.h"


namespace libglabels
{

	class FrameRound : public Frame
	{
	public:
		FrameRound( double  r,
			    double  waste,
			    QString id = "0" )
			: mR(r), mWaste(waste), Frame(id)
		{
		}

		inline double r() const { return mR; }
		inline double waste() const { return mWaste; }


		void getSize( double *w, double *h ) const;
		bool isSimilar( Frame *b ) const;
		QString &getSizeDescription( Units *units ) const;


	private:
		double mR;
		double mWaste;

	};

}

#endif // libglabels_FrameRound_h
