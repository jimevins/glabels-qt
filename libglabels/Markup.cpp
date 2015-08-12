/*  Markup.cpp
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

#include "Markup.h"


namespace libglabels
{

	const QPainterPath& Markup::path() const
	{
		return mPath;
	}

	
	MarkupMargin::MarkupMargin( const Frame* frame, double size )
		: mFrame(frame), mSize(size)
	{
		mPath = frame->marginPath( size );
	}
	

	Markup* MarkupMargin::dup() const
	{
		return new MarkupMargin( mFrame, mSize );
	}


	MarkupLine::MarkupLine( double x1, double y1, double x2, double y2 )
		: mX1(x1), mY1(y1), mX2(x2), mY2(y2)
	{
		mPath.moveTo( x1, y1 );
		mPath.lineTo( x2, y2 );
	}


	Markup* MarkupLine::dup() const
	{
		return new MarkupLine( mX1, mY1, mX2, mY2 );
	}

	
	MarkupRect::MarkupRect( double x1, double y1, double w, double h, double r )
		: mX1(x1), mY1(y1), mW(w), mH(h), mR(r)
	{
		mPath.addRoundedRect( x1, y1, w, h, r, r );
	}


	Markup* MarkupRect::dup() const
	{
		return new MarkupRect( mX1, mY1, mW, mH, mR );
	}
	

	MarkupEllipse::MarkupEllipse( double x1, double y1, double w, double h )
		: mX1(x1), mY1(y1), mW(w), mH(h)
	{
		mPath.addEllipse( x1, y1, w, h );
	}


	Markup* MarkupEllipse::dup() const
	{
		return new MarkupEllipse( mX1, mY1, mW, mH );
	}

	
	MarkupCircle::MarkupCircle( double x0, double y0, double r )
		: mX0(x0), mY0(y0), mR(r)
	{
		mPath.addEllipse( x0-r, y0-r, 2*r, 2*r );
	}

	Markup* MarkupCircle::dup() const
	{
		return new MarkupCircle( mX0, mY0, mR );
	}

}
