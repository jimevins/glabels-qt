/*  Template.cpp
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

#include "Template.h"

#include "Db.h"

#include <QtDebug>


namespace glabels
{
	namespace model
	{

		Template::Template( const QString&  brand,
		                    const QString&  part,
		                    const QString&  description,
		                    const QString&  paperId,
		                    const Distance& pageWidth,
		                    const Distance& pageHeight,
		                    bool            isUserDefined )
			: mBrand(brand),
			  mPart(part),
			  mDescription(description),
			  mPaperId(paperId),
			  mPageWidth(pageWidth),
			  mPageHeight(pageHeight),
			  mIsUserDefined(isUserDefined),
			  mIsSizeIso(false),
			  mIsSizeUs(false),
			  mName("")
		{
			mName.append( brand ).append( " " ).append( part );

			if ( Db::isPaperIdKnown( paperId ) )
			{
				const Paper* paper = Db::lookupPaperFromId( paperId );
				mIsSizeIso = paper->isSizeIso();
				mIsSizeUs  = paper->isSizeUs();
			}
		}


		Template::Template( const Template& other )
		{
			mBrand       = other.mBrand;
			mPart        = other.mPart;
			mDescription = other.mDescription;
			mPaperId     = other.mPaperId;
			mPageWidth   = other.mPageWidth;
			mPageHeight  = other.mPageHeight;
			mIsSizeIso   = other.mIsSizeIso;
			mIsSizeUs    = other.mIsSizeUs;
			mEquivPart   = other.mEquivPart;
			mName        = other.mName;
			mProductUrl  = other.mProductUrl;

			foreach ( Frame* frame, other.mFrames )
			{
				addFrame( frame );
			}

			foreach ( QString categoryId, other.mCategoryIds )
			{
				addCategory( categoryId );
			}
		}


		Template* Template::dup() const
		{
			return new Template( *this );
		}


		// Generic full page template
		Template* Template::fullPage( const QString& paperId )
		{
			// TODO
			return nullptr;
		}


		// From equivalent part number
		Template* Template::fromEquiv( const QString& brand,
		                               const QString& part,
		                               const QString& equivPart )
		{
			const Template* other = Db::lookupTemplateFromBrandPart( brand, equivPart );
			if ( other != nullptr )
			{
				Template* tmplate = other->dup();

				tmplate->mPart      = part;
				tmplate->mEquivPart = equivPart;

				tmplate->mName = "";
				tmplate->mName.append( brand ).append( " " ).append( part );

				return tmplate;
			}
			else
			{
				qWarning() << "Error: cannot create equivalent template for "
				           << brand << ", " << equivPart
				           << ". Forward references not supported.";
				return nullptr;
			}
		}


		QString Template::brand() const
		{
			return mBrand;
		}

	
		QString Template::part() const
		{
			return mPart;
		}

	
		QString Template::description() const
		{
			return mDescription;
		}
	

		QString Template::paperId() const
		{
			return mPaperId;
		}

	
		Distance Template::pageWidth() const
		{
			return mPageWidth;
		}

	
		Distance Template::pageHeight() const
		{
			return mPageHeight;
		}

	
		bool Template::isSizeIso() const
		{
			return mIsSizeIso;
		}

	
		bool Template::isSizeUs() const
		{
			return mIsSizeUs;
		}

	
		bool Template::isSizeOther() const
		{
			return !mIsSizeIso && !mIsSizeUs;
		}
	

		bool Template::isUserDefined() const
		{
			return mIsUserDefined;
		}
	

		QString Template::equivPart() const
		{
			return mEquivPart;
		}

	
		void Template::setEquivPart( const QString& value )
		{
			mEquivPart = value;
		}
	

		QString Template::productUrl() const
		{
			return mProductUrl;
		}

	
		void Template::setProductUrl( const QString& value )
		{
			mProductUrl = value;
		}
	

		QString Template::name() const
		{
			return mName;
		}
	

		const QList<Frame*>& Template::frames() const
		{
			return mFrames;
		}


		void Template::addCategory( const QString& categoryId )
		{
			mCategoryIds << categoryId;
		}


		void Template::addFrame( Frame* frame )
		{
			mFrames << frame;
		}


		bool Template::operator==( const Template& other ) const
		{
			return (mBrand == other.mBrand) && (mPart == other.mPart);
		}


		bool Template::hasCategory( const QString& categoryId ) const
		{
			foreach ( QString testCategoryId, mCategoryIds )
			{
				if ( categoryId == testCategoryId )
				{
					return true;
				}
			}

			return false;
		}


		bool Template::isSimilarTo( const Template* other ) const
		{
			// Does page size match?
			if ( (mPaperId    != other->mPaperId)    ||
			     (mPageWidth  != other->mPageWidth ) ||
			     (mPageHeight != other->mPageHeight ) )
			{
				return false;
			}

			// Are frames similar
			Frame* frame1 = mFrames.first();
			Frame* frame2 = other->mFrames.first();
			if ( !frame1->isSimilarTo( frame2 ) )
			{
				return false;
			}

			// Are they layed out similarly?
			foreach ( Layout* layout1, frame1->layouts() )
			{
				bool matchFound = false;
				foreach ( Layout* layout2, frame2->layouts() )
				{
					if ( layout1->isSimilarTo(layout2) )
					{
						matchFound = true;
						break;
					}
				}
				if ( !matchFound )
				{
					return false;
				}
			}

			return true;
		}


	}
}
