/*  Template.cpp
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

#include "Template.h"


namespace libglabels
{

	Template::Template( const Template &other )
	{
		mBrand       = other.mBrand;
		mPart        = other.mPart;
		mDescription = other.mDescription;
		mPaperId     = other.mPaperId;
		mPageWidth   = other.mPageWidth;
		mPageHeight  = other.mPageHeight;
		mEquivPart   = other.mEquivPart;
		mName        = other.mName;
		mProductUrl  = other.mProductUrl;

		{
			std::list<Frame*>::const_iterator it;
			for ( it = other.mFrames.begin(); it != other.mFrames.end(); it++ )
			{
				Frame *frame = (*it)->dup();

				addFrame( frame );
			}
		}

		{
			std::list<QString>::const_iterator it;
			for ( it = other.mCategoryIds.begin(); it != other.mCategoryIds.end(); it++ )
			{
				addCategory( *it );
			}
		}
	}


	// Generic full page template
	Template *Template::full_page( const QString &paperId )
	{
		// TODO
		return NULL;
	}


	// From equivalent part number
	Template *Template::from_equiv( const QString &brand,
					const QString &part,
					const QString &equiv_part )
	{
		// TODO
		return NULL;
	}


	void Template::addCategory( const QString &categoryId )
	{
		mCategoryIds.push_back( categoryId );
	}


	void Template::addFrame( Frame *frame )
	{
		mFrames.push_back( frame );
	}


	bool Template::operator==( const Template &other ) const
	{
		return (mBrand == other.mBrand) && (mPart == other.mPart);
	}


	bool Template::hasCategory( const QString &categoryId ) const
	{
		std::list<QString>::const_iterator it;

		for ( it = mCategoryIds.begin(); it != mCategoryIds.end(); it++ )
		{
			if ( categoryId == *it )
			{
				return true;
			}
		}

		return false;
	}


	bool Template::isSimilarTo( const Template &other ) const
	{
		// Does page size match?
		if ( (mPaperId    != other.mPaperId)    ||
		     (mPageWidth  != other.mPageWidth ) ||
		     (mPageHeight != other.mPageHeight ) )
		{
			return false;
		}

		// Are frames similar
		Frame *frame1 = *(mFrames.begin());
		Frame *frame2 = *(other.mFrames.begin());
		if ( !frame1->isSimilarTo( frame2 ) )
		{
			return false;
		}

		// Are they layed out similarly?
		std::list<Layout*>::const_iterator it1;
		std::list<Layout*>::const_iterator it2;
		for ( it1 = frame1->layouts().begin(); it1 != frame1->layouts().end(); it1++ )
		{
			bool matchFound = false;
			for ( it2 = frame2->layouts().begin(); it2 != frame2->layouts().end(); it2++ )
			{
				if ( (*it1)->isSimilarTo(*it2) )
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

