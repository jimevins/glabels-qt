/*  Paper.inl
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

	inline const QString& Paper::id() const { return mId; }
	inline const QString& Paper::name() const { return mName; }

	inline Distance Paper::width() const { return mWidth; }
	inline Distance Paper::height() const { return mHeight; }

	inline QString Paper::pwgSize() const { return mPwgSize; }

	inline bool Paper::isSizeIso() const { return mPwgSize.startsWith( "iso_" ); }
	inline bool Paper::isSizeUs() const { return mPwgSize.startsWith( "na_" ); }

}
