/*  Frame.cpp
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

#include "Frame.h"


namespace libglabels
{

	Frame::Frame( const Frame &other )
	{
		mId = other.mId;
		mNLabels = 0;

		{
			std::list<Layout*>::const_iterator it;

			for ( it = other.mLayouts.begin(); it != other.mLayouts.end(); it++ )
			{
				Layout *layout = (*it)->dup();
				addLayout( layout );
			}
		}
		
		{
			std::list<Markup*>::const_iterator it;

			for ( it = other.mMarkups.begin(); it != other.mMarkups.end(); it++ )
			{
				Markup *markup = (*it)->dup();
				addMarkup( markup );
			}
		}
	}


	std::vector<Point> Frame::getOrigins() const
	{
		std::vector<Point> origins( nLabels() );

		std::list<Layout*>::const_iterator it;
		for ( it = mLayouts.begin(); it != mLayouts.end(); it++ )
		{
			Layout *lo = *it;

			for ( int iy = 0; iy < lo->ny(); iy++ )
			{
				for ( int ix = 0; ix < lo->nx(); ix++ )
				{
					origins.push_back( Point( ix*lo->dx() + lo->x0(), iy*lo->dy() + lo->y0() ) );
				}
			}
		}

		std::sort( origins.begin(), origins.end(), Point::compare );
	}


	void Frame::addLayout( Layout *layout )
	{
		mLayouts.push_back( layout );

		// Update total number of labels
		mNLabels += layout->nx() * layout->ny();

		// Update layout description
		if ( mLayouts.size() == 1 )
		{
			/*
			 * Translators: %1 = number of labels across a page,
			 *              %2 = number of labels down a page,
			 *              %3 = total number of labels on a page (sheet).
			 */
			mLayoutDescription = QString( tr("%1 x %2 (%3 per sheet)") )
				.arg(layout->nx()).arg(layout->ny()).arg(mNLabels);
		}
		else
		{
			/* Translators: %1 is the total number of labels on a page (sheet). */
			mLayoutDescription = QString( tr("%1 per sheet") ).arg(mNLabels);
		}
	}


	void Frame::addMarkup( Markup *markup )
	{
		mMarkups.push_back( markup );
	}

}
