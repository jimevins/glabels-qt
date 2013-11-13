/*  Template.h
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

#ifndef libglabels_Template_h
#define libglabels_Template_h

#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QList>

#include <vector>

#include "Units.h"
#include "Point.h"
#include "Frame.h"
#include "MiniPreviewPixmap.h"


namespace libglabels
{

	const int TEMPLATE_PREVIEW_SIZE = 80;


	class Template
	{
		Q_DECLARE_TR_FUNCTIONS(Template)

	public:

		Template( const QString &brand,
			  const QString &part,
			  const QString &description,
			  const QString &paperId,
			  double         pageWidth,
			  double         pageHeight );

		Template( const Template &other );

		inline Template *dup() const { return new Template( *this ); }


		// Generic full page template
		static Template *fullPage( const QString &paperId );

		// From equivalent part number
		static Template *fromEquiv( const QString &brand,
					    const QString &part,
					    const QString &equivPart );


		inline const QString &brand() const { return mBrand; }
		inline const QString &part() const { return mPart; }
		inline const QString &description() const { return mDescription; }

		inline const QString &paperId() const { return mPaperId; }
		inline double pageWidth() const { return mPageWidth; }
		inline double pageHeight() const { return mPageHeight; }
		inline bool isSizeIso() const { return mIsSizeIso; }
		inline bool isSizeUs() const { return mIsSizeUs; }
		inline bool isSizeOther() const { return !mIsSizeIso && !mIsSizeUs; }

		inline const QString &equivPart() const { return mEquivPart; }
		inline void setEquivPart( const QString &value ) { mEquivPart = value; }

		inline const QString &productUrl() const { return mProductUrl; }
		inline void setProductUrl( const QString &value ) { mProductUrl = value; }

		inline const QString &name() const { return mName; }

		void addCategory( const QString &categoryId );
		void addFrame( Frame *frame );

		void initPreview();
		inline const MiniPreviewPixmap &preview() const { return mPreview; }

		inline const QList<Frame*> &frames() const { return mFrames; }

		bool operator==( const Template &other ) const;

		bool hasCategory( const QString &categoryId ) const;
		bool isSimilarTo( const Template &other ) const;


	private:
		QString mBrand;
		QString mPart;
		QString mDescription;

		QString mPaperId;
		double  mPageWidth;
		double  mPageHeight;
		bool    mIsSizeIso;
		bool    mIsSizeUs;

		QString mEquivPart;
		QString mName;

		QString        mProductUrl;
		QStringList    mCategoryIds;

		QList<Frame*>  mFrames;

		MiniPreviewPixmap mPreview;
	};

}

#endif // libglabels_Template_h
