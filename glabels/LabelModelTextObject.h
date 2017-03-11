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
		virtual ~LabelModelTextObject();


		///////////////////////////////////////////////////////////////
		// Object duplication
		///////////////////////////////////////////////////////////////
		virtual LabelModelTextObject* clone() const;


		///////////////////////////////////////////////////////////////
		// Property Implementations
		///////////////////////////////////////////////////////////////
	public:
		//
		// Text Property: text
		//
		virtual QString text() const;
		virtual void setText( const QString &value );


		//
		// Text Property: fontFamily
		//
		virtual QString fontFamily() const;
		virtual void setFontFamily( const QString &value );


		//
		// Text Property: fontSize
		//
		virtual double fontSize() const;
		virtual void setFontSize( double value );


		//
		// Text Property: fontWeight
		//
		virtual QFont::Weight fontWeight() const;
		virtual void setFontWeight( QFont::Weight value );


		//
		// Text Property: fontItalicFlag
		//
		virtual bool fontItalicFlag() const;
		virtual void setFontItalicFlag( bool value );


		//
		// Text Property: fontUnderlineFlag
		//
		virtual bool fontUnderlineFlag() const;
		virtual void setFontUnderlineFlag( bool value );


		//
		// Text Property: textColorNode
		//
		virtual ColorNode textColorNode() const;
		virtual void setTextColorNode( const ColorNode &value );
		

		//
		// Text Property: textHAlign
		//
		virtual Qt::Alignment textHAlign() const;
		virtual void setTextHAlign( Qt::Alignment value );


		//
		// Text Property: textVAlign
		//
		virtual Qt::Alignment textVAlign() const;
		virtual void setTextVAlign( Qt::Alignment value );


		//
		// Text Property: textLineSpacing
		//
		virtual double textLineSpacing() const;
		virtual void setTextLineSpacing( double value );


		//
		// Property: naturalSize
		//
		virtual Size naturalSize() const;


		///////////////////////////////////////////////////////////////
		// Capability Implementations
		///////////////////////////////////////////////////////////////
	public:
		virtual bool canText();


		///////////////////////////////////////////////////////////////
		// Drawing operations
		///////////////////////////////////////////////////////////////
	protected:
		virtual void drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const;
		virtual void drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const;
		virtual QPainterPath hoverPath( double scale ) const;


		///////////////////////////////////////////////////////////////
		// Private methods
		///////////////////////////////////////////////////////////////
	private:
		virtual void sizeUpdated();
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
