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

#include <list>
#include <vector>

#include "Units.h"
#include "Point.h"
#include "Frame.h"


namespace libglabels
{

	class Template
	{
		Q_DECLARE_TR_FUNCTIONS(Template)

	public:
		Template( const QString &brand,
			  const QString &part,
			  const QString &description,
			  const QString &paperId,
			  double         pageWidth = 0,
			  double         pageHeight = 0 )
			: mBrand(brand),
			  mPart(part),
			  mDescription(description),
			  mPaperId(paperId),
			  mPageWidth(pageWidth),
			  mPageHeight(pageHeight)
		{
		}

		Template( const Template &other );

		inline Template *dup() const { return new Template( *this ); }


		// Generic full page template
		static Template *full_page( const QString &paperId );

		// From equivalent part number
		static Template *from_equiv( const QString &brand,
					     const QString &part,
					     const QString &equiv_part );


		inline const QString &brand() const { return mBrand; }
		inline const QString &part() const { return mPart; }
		inline const QString &description() const { return mDescription; }

		inline const QString &paperId() const { return mPaperId; }
		inline double pageWidth() const { return mPageWidth; }
		inline double pageHeight() const { return mPageHeight; }

		inline const QString &equivPart() const { return mEquivPart; }
		inline void setEquivPart( const QString &value ) { mEquivPart = value; }

		inline const QString &productUrl() const { return mProductUrl; }
		inline void setProductUrl( const QString &value ) { mProductUrl = value; }

		void addCategory( const QString &categoryId );
		void addFrame( Frame *frame );

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

		QString mEquivPart;
		QString mName;

		QString            mProductUrl;
		std::list<QString> mCategoryIds;

		std::list<Frame*>  mFrames;
	};

}

#endif // libglabels_Template_h
