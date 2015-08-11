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
			mPath.addEllipse( 0, 0, 2*mR, 2*mR );
		}

		FrameRound( const FrameRound &other )
			: mR(other.mR), mWaste(other.mWaste), mPath(other.mPath), Frame(other)
		{
		}

		Frame *dup() const { return new FrameRound( *this ); }

		inline double r() const { return mR; }
		inline double waste() const { return mWaste; }

		double w() const { return 2*mR; }
		double h() const { return 2*mR; }

		const QString sizeDescription( const Units *units ) const;
		bool isSimilarTo( Frame *other ) const;

		const QPainterPath &path( bool isRotated ) const { return mPath; }
		QGraphicsItem* createMarginGraphicsItem( double size, const QPen& pen ) const;


	private:
		double mR;
		double mWaste;

		QPainterPath mPath;

	};

}

#endif // libglabels_FrameRound_h
