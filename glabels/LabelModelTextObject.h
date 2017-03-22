/*  LabelModelTextObject.h
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

#ifndef LabelModelTextObject_h
#define LabelModelTextObject_h


#include <QTextLayout>

#include "LabelModelObject.h"


namespace glabels
{

	///
	/// Label Model Line Object
	///
	class LabelModelTextObject : public LabelModelObject
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	public:
		LabelModelTextObject();
		LabelModelTextObject( const LabelModelTextObject* object );
		~LabelModelTextObject() override;


		///////////////////////////////////////////////////////////////
		// Object duplication
		///////////////////////////////////////////////////////////////
		LabelModelTextObject* clone() const override;


		///////////////////////////////////////////////////////////////
		// Property Implementations
		///////////////////////////////////////////////////////////////
	public:
		//
		// Text Property: text
		//
		QString text() const override;
		void setText( const QString &value ) override;


		//
		// Text Property: fontFamily
		//
		QString fontFamily() const override;
		void setFontFamily( const QString &value ) override;


		//
		// Text Property: fontSize
		//
		double fontSize() const override;
		void setFontSize( double value ) override;


		//
		// Text Property: fontWeight
		//
		QFont::Weight fontWeight() const override;
		void setFontWeight( QFont::Weight value ) override;


		//
		// Text Property: fontItalicFlag
		//
		bool fontItalicFlag() const override;
		void setFontItalicFlag( bool value ) override;


		//
		// Text Property: fontUnderlineFlag
		//
		bool fontUnderlineFlag() const override;
		void setFontUnderlineFlag( bool value ) override;


		//
		// Text Property: textColorNode
		//
		ColorNode textColorNode() const override;
		void setTextColorNode( const ColorNode &value ) override;
		

		//
		// Text Property: textHAlign
		//
		Qt::Alignment textHAlign() const override;
		void setTextHAlign( Qt::Alignment value ) override;


		//
		// Text Property: textVAlign
		//
		Qt::Alignment textVAlign() const override;
		void setTextVAlign( Qt::Alignment value ) override;


		//
		// Text Property: textLineSpacing
		//
		double textLineSpacing() const override;
		void setTextLineSpacing( double value ) override;


		//
		// Property: naturalSize
		//
		Size naturalSize() const override;


		///////////////////////////////////////////////////////////////
		// Capability Implementations
		///////////////////////////////////////////////////////////////
	public:
		virtual bool canText();


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
		void drawTextInEditor( QPainter* painter, const QColor& color ) const;
		void drawText( QPainter* painter, const QColor&color, merge::Record* record ) const;
		QString expandText( QString text, merge::Record* record ) const;
	

		///////////////////////////////////////////////////////////////
		// Private Members
		///////////////////////////////////////////////////////////////
	private:
		QString              mText;
		QString              mFontFamily;
		double               mFontSize;
		QFont::Weight        mFontWeight;
		bool                 mFontItalicFlag;
		bool                 mFontUnderlineFlag;
		ColorNode            mTextColorNode;
		Qt::Alignment        mTextHAlign;
		Qt::Alignment        mTextVAlign;
		double               mTextLineSpacing;

		QList<QTextLayout*>  mEditorLayouts;
		QPainterPath         mHoverPath;

	};

}


#endif // LabelModelTextObject_h
