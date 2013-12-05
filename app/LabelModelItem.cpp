/*  LabelModelItem.cpp
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

#include "LabelModelItem.h"


namespace glabels
{

	int LabelModelItem::lastId = 0;

	/*
	 * Default constructor.
	 */
	LabelModelItem::LabelModelItem( QObject *parent = 0 ) : QObject(parent)
	{
		mId = lastId++;

		mX0 = 0;
		mY0 = 0;
		mW  = 0;
		mH  = 0;
		mMatrix = QTransform();

		mShadowState     = false;
		mShadowX         = 1.3;
		mShadowY         = 1.3;
		mShadowColorNode = ColorNode( QColor::fromRgb(0x000000) );
		mShadowOpacity   = 0.5;

		mSelectedFlag = false;
	}


	void LabelModelItem::setPosition( double x0, double y0 )
	{
		if ( ( mX0 != x0 ) || ( mY0 != y0 ) )
		{
			mX0 = x0;
			mY0 = y0;

			emit moved();
		}
	}


	void LabelModelItem::setPositionRelative( double dx, double dy )
	{
		if ( ( dx != 0 ) || ( dy != 0 ) )
		{
			mX0 += dx;
			mY0 += dy;

			emit moved();
		}
	}


	void LabelModelItem::setSize( double w, double h )
	{
		mW = w;
		mH = h;
	}


	void LabelModelItem::setSizeHonorAspect( double w, double h )
	{
		double aspectRatio = mH / mW;

		if ( h > (w * aspectRatio) )
		{
			h = w * aspectRatio;
		}
		else
		{
			w = h / aspectRatio;
		}

		if ( ( mW != w ) || ( mH != h ) )
		{
			mW = w;
			mH = h;

			emit changed();
		}
	}


	void LabelModelItem::setWHonorAspect( double w )
	{
		double aspectRatio = mH / mW;
		double h = w * aspectRatio;

		if ( ( mW != w ) || ( mH != h ) )
		{
			mW = w;
			mH = h;

			emit changed();
		}
	}


	void LabelModelItem::setHHonorAspect( double h )
	{
		double aspectRatio = mH / mW;
		double w = h / aspectRatio;

		if ( ( mW != w ) || ( mH != h ) )
		{
			mW = w;
			mH = h;

			emit changed();
		}
	}


	LabelRegion LabelModelItem::getExtent()
	{
		QPointF a1(    - lineWidth()/2,    - lineWidth()/2 );
		QPointF a2( mW + lineWidth()/2,    - lineWidth()/2 );
		QPointF a3( mW + lineWidth()/2, mH + lineWidth()/2 );
		QPointF a4(    - lineWidth()/2, mH + lineWidth()/2 );

		a1 = mMatrix.map( a1 );
		a2 = mMatrix.map( a2 );
		a3 = mMatrix.map( a3 );
		a4 = mMatrix.map( a4 );

		LabelRegion region;
		region.x1( std::min( a1.x(), std::min( a2.x(), std::min( a3.x(), a4.x() ) ) ) + mX0 );
		region.y1( std::min( a1.y(), std::min( a2.y(), std::min( a3.y(), a4.y() ) ) ) + mY0 );
		region.x2( std::max( a1.x(), std::max( a2.x(), std::max( a3.x(), a4.x() ) ) ) + mX0 );
		region.y2( std::max( a1.y(), std::max( a2.y(), std::max( a3.y(), a4.y() ) ) ) + mY0 );

		return region;
	}


	void LabelModelItem::rotate( double thetaDegs )
	{
		if ( thetaDegs != 0 )
		{
			mMatrix = mMatrix.rotate( thetaDegs );
			emit changed();
		}
	}


	void LabelModelItem::flipHoriz()
	{
		mMatrix = mMatrix.scale( -1, 1 );
		emit changed();
	}


	void LabelModelItem::flipVert()
	{
		mMatrix = mMatrix.scale( 1, -1 );
		emit changed();
	}

}

