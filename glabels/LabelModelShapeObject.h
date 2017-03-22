/*  LabelModelShapeObject.h
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

#ifndef LabelModelShapeObject_h
#define LabelModelShapeObject_h


#include "LabelModelObject.h"


namespace glabels
{

	///
	/// Label Model Shape Object (Box or Ellipse)
	///
	class LabelModelShapeObject : public LabelModelObject
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	protected:
		LabelModelShapeObject();
		LabelModelShapeObject( const LabelModelShapeObject* object );
	public:
		~LabelModelShapeObject() override;


		///////////////////////////////////////////////////////////////
		// Property Implementations
		///////////////////////////////////////////////////////////////
	public:
		//
		// Shape Property: lineWidth
		//
		Distance lineWidth( void ) const override;
		void setLineWidth( const Distance& value ) override;


		//
		// Shape Property: lineColorNode
		//
		ColorNode lineColorNode( void ) const override;
		void setLineColorNode( const ColorNode& value ) override;
		

		//
		// Shape Property: fillColorNode
		//
		ColorNode fillColorNode( void ) const override;
		void setFillColorNode( const ColorNode& value ) override;
		

		///////////////////////////////////////////////////////////////
		// Capability Implementations
		///////////////////////////////////////////////////////////////
	public:
		virtual bool canFill();
		virtual bool canLineColor();
		virtual bool canLineWidth();


		///////////////////////////////////////////////////////////////
		// Private Members
		///////////////////////////////////////////////////////////////
	protected:
		Distance             mLineWidth;
		ColorNode            mLineColorNode;
		ColorNode            mFillColorNode;

	};

}


#endif // LabelModelShapeObject_h
