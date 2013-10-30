/*  FrameRect.h
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

#ifndef libglabels_FrameRect_h
#define libglabels_FrameRect_h

#include "Frame.h"


namespace libglabels
{

	class FrameRect : public Frame
	{
	public:
		FrameRect( double  w,
			   double  h,
			   double  r,
			   double  xWaste,
			   double  yWaste,
			   QString id = "0" )
			: mW(w), mH(h), mR(r), mXWaste(xWaste), mYWaste(yWaste), Frame(id)
		{
		}

		inline double w() const { return mW; }
		inline double h() const { return mH; }
		inline double r() const { return mR; }
		inline double xWaste() const { return mXWaste; }
		inline double yWaste() const { return mYWaste; }


		void getSize( double *w, double *h ) const;
		bool isSimilar( Frame *b ) const;
		QString &getSizeDescription( Units *units ) const;


	private:
		double mW;
		double mH;
		double mR;
		double mXWaste;
		double mYWaste;

	};

}

#endif // libglabels_FrameRect_h
