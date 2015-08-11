/*  Template.inl
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

	inline const QString& Template::brand() const { return mBrand; }
	inline const QString& Template::part() const { return mPart; }
	inline const QString& Template::description() const { return mDescription; }

	inline const QString& Template::paperId() const { return mPaperId; }
	inline double Template::pageWidth() const { return mPageWidth; }
	inline double Template::pageHeight() const { return mPageHeight; }
	inline bool Template::isSizeIso() const { return mIsSizeIso; }
	inline bool Template::isSizeUs() const { return mIsSizeUs; }
	inline bool Template::isSizeOther() const { return !mIsSizeIso && !mIsSizeUs; }

	inline const QString& Template::equivPart() const { return mEquivPart; }
	inline void Template::setEquivPart( const QString& value ) { mEquivPart = value; }

	inline const QString& Template::productUrl() const { return mProductUrl; }
	inline void Template::setProductUrl( const QString& value ) { mProductUrl = value; }

	inline const QString& Template::name() const { return mName; }

	inline const MiniPreviewPixmap& Template::preview() const { return mPreview; }

	inline const QList<Frame*>& Template::frames() const { return mFrames; }

}
