/*  Markup.inl
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


namespace libglabels
{

	inline Distance MarkupMargin::size() const { return mSize; }

	inline Distance MarkupLine::x1() const { return mX1; }
	inline Distance MarkupLine::y1() const { return mY1; }
	inline Distance MarkupLine::x2() const { return mX2; }
	inline Distance MarkupLine::y2() const { return mY2; }

	inline Distance MarkupRect::x1() const { return mX1; }
	inline Distance MarkupRect::y1() const { return mY1; }
	inline Distance MarkupRect::w() const { return mW; }
	inline Distance MarkupRect::h() const { return mH; }
	inline Distance MarkupRect::r() const { return mR; }

	inline Distance MarkupEllipse::x1() const { return mX1; }
	inline Distance MarkupEllipse::y1() const { return mY1; }
	inline Distance MarkupEllipse::w() const { return mW; }
	inline Distance MarkupEllipse::h() const { return mH; }

	inline Distance MarkupCircle::x0() const { return mX0; }
	inline Distance MarkupCircle::y0() const { return mY0; }
	inline Distance MarkupCircle::r() const { return mR; }

}
