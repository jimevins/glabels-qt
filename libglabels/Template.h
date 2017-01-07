/*  Template.h
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

#ifndef glabels_Template_h
#define glabels_Template_h


#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QList>

#include "Distance.h"
#include "Frame.h"
#include "MiniPreviewPixmap.h"
#include "Point.h"


namespace glabels
{

	const int TEMPLATE_PREVIEW_SIZE = 80;


	class Template
	{
		Q_DECLARE_TR_FUNCTIONS(Template)

	public:

		Template( const QString&  brand,
			  const QString&  part,
			  const QString&  description,
			  const QString&  paperId,
		          const Distance& pageWidth,
		          const Distance& pageHeight );

		Template( const Template& other );

		Template* dup() const;

		// Generic full page template
		static Template* fullPage( const QString& paperId );

		// From equivalent part number
		static Template* fromEquiv( const QString& brand,
					    const QString& part,
					    const QString& equivPart );


		const QString& brand() const;
		const QString& part() const;
		const QString& description() const;

		const QString& paperId() const;
		Distance pageWidth() const;
		Distance pageHeight() const;
		bool isSizeIso() const;
		bool isSizeUs() const;
		bool isSizeOther() const;

		const QString& equivPart() const;
		void setEquivPart( const QString& value );

		const QString& productUrl() const;
		void setProductUrl( const QString& value );

		const QString& name() const;

		void addCategory( const QString& categoryId );
		void addFrame( Frame* frame );

		void initPreview();
		const MiniPreviewPixmap& preview() const;

		const QList<Frame*>& frames() const;

		bool operator==( const Template& other ) const;

		bool hasCategory( const QString& categoryId ) const;
		bool isSimilarTo( const Template* other ) const;


	private:
		QString mBrand;
		QString mPart;
		QString mDescription;

		QString  mPaperId;
		Distance mPageWidth;
		Distance mPageHeight;
		bool     mIsSizeIso;
		bool     mIsSizeUs;

		QString mEquivPart;
		QString mName;

		QString        mProductUrl;
		QStringList    mCategoryIds;

		QList<Frame*>  mFrames;

		MiniPreviewPixmap mPreview;
	};

}


#include "Template.inl"


#endif // glabels_Template_h
