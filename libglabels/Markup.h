/*  Markup.h
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

#ifndef libglabels_Markup_h
#define libglabels_Markup_h


namespace libglabels
{

	class Markup
	{
	public:
		virtual Markup *dup() const = 0;
	};


	class MarkupMargin : public Markup
	{
	public:
		MarkupMargin( double size ) : mSize(size)
		{
		}

		inline double size() const { return mSize; }

		Markup *dup() const { return new MarkupMargin( mSize ); }

	private:
		double  mSize;
	};


	class MarkupLine : public Markup
	{
	public:
		MarkupLine( double x1, double y1, double x2, double y2 ) : mX1(x1), mY1(y1), mX2(x2), mY2(y2)
		{
		}

		inline double x1() const { return mX1; }
		inline double y1() const { return mY1; }
		inline double x2() const { return mX2; }
		inline double y2() const { return mY2; }

		Markup *dup() const { return new MarkupLine( mX1, mY1, mX2, mY2 ); }

	private:
		double  mX1;
		double  mY1;
		double  mX2;
		double  mY2;
	};


	class MarkupRect : public Markup
	{
	public:
		MarkupRect( double x1, double y1, double w, double h, double r )
			: mX1(x1), mY1(y1), mW(w), mH(h), mR(r)
		{
		}

		inline double x1() const { return mX1; }
		inline double y1() const { return mY1; }
		inline double w() const { return mW; }
		inline double h() const { return mH; }
		inline double r() const { return mR; }

		Markup *dup() const { return new MarkupRect( mX1, mY1, mW, mH, mR ); }

	private:
		double  mX1;
		double  mY1;
		double  mW;
		double  mH;
		double  mR;
	};


	class MarkupEllipse : public Markup
	{
	public:
		MarkupEllipse( double x1, double y1, double w, double h )
			: mX1(x1), mY1(y1), mW(w), mH(h)
		{
		}

		inline double x1() const { return mX1; }
		inline double y1() const { return mY1; }
		inline double w() const { return mW; }
		inline double h() const { return mH; }

		Markup *dup() const { return new MarkupEllipse( mX1, mY1, mW, mH ); }

	private:
		double  mX1;
		double  mY1;
		double  mW;
		double  mH;
	};


	class MarkupCircle : public Markup
	{
	public:
		MarkupCircle( double x0, double y0, double r )
			: mX0(x0), mY0(y0), mR(r)
		{
		}

		inline double x0() const { return mX0; }
		inline double y0() const { return mY0; }
		inline double r() const { return mR; }

		Markup *dup() const { return new MarkupCircle( mX0, mY0, mR ); }

	private:
		double  mX0;
		double  mY0;
		double  mR;
	};


	

}

#endif // libglabels_Markup_h
