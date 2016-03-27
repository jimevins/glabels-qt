/*  Markup.cpp
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
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


namespace glabels
{

	const QPainterPath& Markup::path() const
	{
		return mPath;
	}

	
	MarkupMargin::MarkupMargin( const Frame*    frame,
				    const Distance& size )
		: mFrame(frame), mSize(size)
	{
		mPath = frame->marginPath( size );
	}
	

	Markup* MarkupMargin::dup() const
	{
		return new MarkupMargin( mFrame, mSize );
	}


	MarkupLine::MarkupLine( const Distance& x1,
				const Distance& y1,
				const Distance& x2,
				const Distance& y2 )
		: mX1(x1), mY1(y1), mX2(x2), mY2(y2)
	{
		mPath.moveTo( x1.pt(), y1.pt() );
		mPath.lineTo( x2.pt(), y2.pt() );
	}


	Markup* MarkupLine::dup() const
	{
		return new MarkupLine( mX1, mY1, mX2, mY2 );
	}

	
	MarkupRect::MarkupRect( const Distance& x1,
				const Distance& y1,
				const Distance& w,
				const Distance& h,
				const Distance& r )
		: mX1(x1), mY1(y1), mW(w), mH(h), mR(r)
	{
		mPath.addRoundedRect( x1.pt(), y1.pt(), w.pt(), h.pt(), r.pt(), r.pt() );
	}


	Markup* MarkupRect::dup() const
	{
		return new MarkupRect( mX1, mY1, mW, mH, mR );
	}
	

	MarkupEllipse::MarkupEllipse( const Distance& x1,
				      const Distance& y1,
				      const Distance& w,
				      const Distance& h )
		: mX1(x1), mY1(y1), mW(w), mH(h)
	{
		mPath.addEllipse( x1.pt(), y1.pt(), w.pt(), h.pt() );
	}


	Markup* MarkupEllipse::dup() const
	{
		return new MarkupEllipse( mX1, mY1, mW, mH );
	}

	
	MarkupCircle::MarkupCircle( const Distance& x0,
				    const Distance& y0,
				    const Distance& r )
		: mX0(x0), mY0(y0), mR(r)
	{
		mPath.addEllipse( (x0-r).pt(), (y0-r).pt(), 2*r.pt(), 2*r.pt() );
	}

	Markup* MarkupCircle::dup() const
	{
		return new MarkupCircle( mX0, mY0, mR );
	}

}
