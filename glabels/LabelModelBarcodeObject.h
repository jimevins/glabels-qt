/*  LabelModelBarcodeObject.h
 *
 *  Copyright (C) 2017  Jim Evins <evins@snaught.com>
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

#ifndef LabelModelBarcodeObject_h
#define LabelModelBarcodeObject_h


#include "LabelModelObject.h"

#include "glbarcode/Barcode.h"


namespace glabels
{

	///
	/// Label Model Line Object
	///
	class LabelModelBarcodeObject : public LabelModelObject
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	public:
		LabelModelBarcodeObject();
		LabelModelBarcodeObject( const LabelModelBarcodeObject* object );
		~LabelModelBarcodeObject() override;


		///////////////////////////////////////////////////////////////
		// Object duplication
		///////////////////////////////////////////////////////////////
		LabelModelBarcodeObject* clone() const override;


		///////////////////////////////////////////////////////////////
		// Property Implementations
		///////////////////////////////////////////////////////////////
	public:
                //
                // Barcode Property: bcDataNode
                //
                TextNode bcDataNode() const override;
                void setBcDataNode( const TextNode &value ) override;
                

                //
                // Barcode Property: bcTextFlag
                //
                bool bcTextFlag() const override;
                void setBcTextFlag( bool value ) override;


                //
                // Barcode Property: bcChecksumFlag
                //
                bool bcChecksumFlag() const override;
                void setBcChecksumFlag( bool value ) override;


                //
                // Barcode Property: bcColorNode
                //
                ColorNode bcColorNode() const override;
                void setBcColorNode( const ColorNode &value ) override;
                

                //
                // Barcode Property: bcStyle
                //
                BarcodeStyle bcStyle() const override;
                void setBcStyle( const BarcodeStyle &value ) override;
                

                //
                // Barcode Property: bcFormatDigits
                //
                int bcFormatDigits() const override;
                void setBcFormatDigits( int value ) override;



		///////////////////////////////////////////////////////////////
		// Capability Implementations
		///////////////////////////////////////////////////////////////
	public:


		///////////////////////////////////////////////////////////////
		// Drawing operations
		///////////////////////////////////////////////////////////////
	protected:
		void drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const override;
		void drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const override;
		QPainterPath hoverPath( double scale ) const override;


		///////////////////////////////////////////////////////////////
		// Private methods
		///////////////////////////////////////////////////////////////
	private:
		void sizeUpdated() override;
		void update();

		void drawBcInEditor( QPainter* painter, const QColor& color ) const;
		void drawBc( QPainter* painter, const QColor& color, merge::Record* record ) const;

	

		///////////////////////////////////////////////////////////////
		// Private Members
		///////////////////////////////////////////////////////////////
	private:
		BarcodeStyle mBcStyle;
		bool         mBcTextFlag;
		bool         mBcChecksumFlag;
		int          mBcFormatDigits;
		TextNode     mBcDataNode;
		ColorNode    mBcColorNode;

		glbarcode::Barcode* mEditorBarcode;
		
		QPainterPath mHoverPath;

	};

}


#endif // LabelModelBarcodeObject_h
