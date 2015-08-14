/*  Outline.h
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

#ifndef glabels_Outline_h
#define glabels_Outline_h


#include <QPainter>
#include <QPainterPath>


namespace glabels
{

	class LabelModelObject;


	///
	/// Outline Base Class
	///
	class Outline
	{
		////////////////////////////
		// Lifecycle Methods
		////////////////////////////
	public:
		Outline( LabelModelObject* owner );
		virtual ~Outline();


		////////////////////////////
		// Drawing Methods
		////////////////////////////
	public:
		void  draw( QPainter* painter ) const;
		QPainterPath path( double scale ) const;


		////////////////////////////
		// Private Data
		////////////////////////////
	private:
		LabelModelObject* mOwner;

		QVector<qreal> mDashes;
		QPen           mPen1;
		QPen           mPen2;
	
	};

}

#endif // glabels_Outline_h
