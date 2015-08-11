/*  Markup.inl
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


namespace libglabels
{

	inline double MarkupMargin::size() const { return mSize; }

	inline double MarkupLine::x1() const { return mX1; }
	inline double MarkupLine::y1() const { return mY1; }
	inline double MarkupLine::x2() const { return mX2; }
	inline double MarkupLine::y2() const { return mY2; }

	inline double MarkupRect::x1() const { return mX1; }
	inline double MarkupRect::y1() const { return mY1; }
	inline double MarkupRect::w() const { return mW; }
	inline double MarkupRect::h() const { return mH; }
	inline double MarkupRect::r() const { return mR; }

	inline double MarkupEllipse::x1() const { return mX1; }
	inline double MarkupEllipse::y1() const { return mY1; }
	inline double MarkupEllipse::w() const { return mW; }
	inline double MarkupEllipse::h() const { return mH; }

	inline double MarkupCircle::x0() const { return mX0; }
	inline double MarkupCircle::y0() const { return mY0; }
	inline double MarkupCircle::r() const { return mR; }

}
