/*  LabelModelBoxItem.h
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

#ifndef glabels_LabelModelBoxItem_h
#define glabels_LabelModelBoxItem_h

#include "LabelModelItem.h"


namespace glabels
{

	class LabelModelBoxItem : public LabelModelItem
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	public:
		LabelModelBoxItem( QObject *parent = 0 ) : LabelModelItem(parent) { /* TODO: initialize default line and fill poperties.  */ };
		virtual ~LabelModelBoxItem() {}


		///////////////////////////////////////////////////////////////
		// Properties
		///////////////////////////////////////////////////////////////
	public:
		/*
		 * Virtual Shape Property: lineWidth
		 */
		double lineWidth( void ) const { return mLineWidth; }
		void setLineWidth( double value ) { mLineWidth = value; }


		/*
		 * Virtual Shape Property: lineColorNode
		 */
		ColorNode lineColorNode( void ) { return mLineColorNode; }
		void setLineColorNode( const ColorNode &value ) { mLineColorNode = value; }
		

		/*
		 * Virtual Shape Property: fillColorNode
		 */
		ColorNode fillColorNode( void ) { return mFillColorNode; }
		void setFillColorNode( const ColorNode &value ) { mFillColorNode = value; }
		

		///////////////////////////////////////////////////////////////
		// Capabilities
		///////////////////////////////////////////////////////////////
	public:
		bool canFill()	{ return true;	}

		bool canLineColor() { return true; }

		bool canLineWidth() { return true; }


		///////////////////////////////////////////////////////////////
		// QGraphicsItem methods
		///////////////////////////////////////////////////////////////
	public:
		QGraphicsItem* createGraphicsItem();
		void updateGraphicsItem( QGraphicsItem* graphicsItem );


		///////////////////////////////////////////////////////////////
		// Private Members
		///////////////////////////////////////////////////////////////
	private:
		double     mLineWidth;
		ColorNode  mLineColorNode;
		ColorNode  mFillColorNode;

	};

}

#endif // glabels_LabelModelBoxItem_h
