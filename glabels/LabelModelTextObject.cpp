/*  LabelModelTextObject.cpp
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

#include "LabelModelTextObject.h"


#include <QBrush>
#include <QPen>
#include <QTextDocument>
#include <QTextBlock>
#include <QRegularExpression>
#include <QtDebug>


namespace glabels
{

	//
	// Private
	//
	namespace
	{
		const double marginPts = 3;
	}


	///
	/// Constructor
	///
	LabelModelTextObject::LabelModelTextObject()
	{
		mOutline = new Outline( this );

		mHandles << new HandleNorthWest( this );
		mHandles << new HandleNorth( this );
		mHandles << new HandleNorthEast( this );
		mHandles << new HandleEast( this );
		mHandles << new HandleSouthEast( this );
		mHandles << new HandleSouth( this );
		mHandles << new HandleSouthWest( this );
		mHandles << new HandleWest( this );

		mText              = "";
		mFontFamily        = "Sans";
		mFontSize          = 10;
		mFontWeight        = QFont::Normal;
		mFontItalicFlag    = false;
		mFontUnderlineFlag = false;
		mTextColorNode     = ColorNode( QColor( 0, 0, 0 ) );
		mTextHAlign        = Qt::AlignLeft;
		mTextVAlign        = Qt::AlignTop;
		mTextLineSpacing   = 1;
	}


	///
	/// Copy constructor
	///
	LabelModelTextObject::LabelModelTextObject( const LabelModelTextObject* object )
		: LabelModelObject(object)
	{
		mText              = object->mText;
		mFontFamily        = object->mFontFamily;
		mFontSize          = object->mFontSize;
		mFontWeight        = object->mFontWeight;
		mFontItalicFlag    = object->mFontItalicFlag;
		mFontUnderlineFlag = object->mFontUnderlineFlag;
		mTextColorNode     = object->mTextColorNode;
		mTextHAlign        = object->mTextHAlign;
		mTextVAlign        = object->mTextVAlign;
		mTextLineSpacing   = object->mTextLineSpacing;
	}


	///
	/// Destructor
	///
	LabelModelTextObject::~LabelModelTextObject()
	{
		delete mOutline;

		foreach( Handle* handle, mHandles )
		{
			delete handle;
		}
		mHandles.clear();
	}


	///
	/// Clone
	///
	LabelModelTextObject* LabelModelTextObject::clone() const
	{
		return new LabelModelTextObject( this );
	}


	///
	/// Text Property Getter
	///
	QString LabelModelTextObject::text( void ) const
	{
		return mText;
	}


	///
	/// Text Property Setter
	///
	void LabelModelTextObject::setText( const QString& value )
	{
		if ( mText != value )
		{
			mText = value;
			update();
			emit changed();
		}
	}


	///
	/// FontFamily Property Getter
	///
	QString LabelModelTextObject::fontFamily( void ) const
	{
		return mFontFamily;
	}


	///
	/// FontFamily Property Setter
	///
	void LabelModelTextObject::setFontFamily( const QString& value )
	{
		if ( mFontFamily != value )
		{
			mFontFamily = value;
			update();
			emit changed();
		}
	}


	///
	/// FontSize Property Getter
	///
	double LabelModelTextObject::fontSize( void ) const
	{
		return mFontSize;
	}


	///
	/// FontSize Property Setter
	///
	void LabelModelTextObject::setFontSize( double value )
	{
		if ( mFontSize != value )
		{
			mFontSize = value;
			update();
			emit changed();
		}
	}


	///
	/// FontWeight Property Getter
	///
	QFont::Weight LabelModelTextObject::fontWeight( void ) const
	{
		return mFontWeight;
	}


	///
	/// FontWeight Property Setter
	///
	void LabelModelTextObject::setFontWeight( QFont::Weight value )
	{
		if ( mFontWeight != value )
		{
			mFontWeight = value;
			update();
			emit changed();
		}
	}


	///
	/// FontItalicFlag Property Getter
	///
	bool LabelModelTextObject::fontItalicFlag( void ) const
	{
		return mFontItalicFlag;
	}


	///
	/// FontItalicFlag Property Setter
	///
	void LabelModelTextObject::setFontItalicFlag( bool value )
	{
		if ( mFontItalicFlag != value )
		{
			mFontItalicFlag = value;
			update();
			emit changed();
		}
	}


	///
	/// FontUnderlineFlag Property Getter
	///
	bool LabelModelTextObject::fontUnderlineFlag( void ) const
	{
		return mFontUnderlineFlag;
	}


	///
	/// FontUnderlineFlag Property Setter
	///
	void LabelModelTextObject::setFontUnderlineFlag( bool value )
	{
		if ( mFontUnderlineFlag != value )
		{
			mFontUnderlineFlag = value;
			update();
			emit changed();
		}
	}


	///
	/// Text Color Node Property Getter
	///
	ColorNode LabelModelTextObject::textColorNode( void ) const
	{
		return mTextColorNode;
	}


	///
	/// Text Color Node Property Setter
	///
	void LabelModelTextObject::setTextColorNode( const ColorNode& value )
	{
		if ( mTextColorNode != value )
		{
			mTextColorNode = value;
			update();
			emit changed();
		}
	}
		

	///
	/// TextHAlign Property Getter
	///
	Qt::Alignment LabelModelTextObject::textHAlign( void ) const
	{
		return mTextHAlign;
	}


	///
	/// TextHAlign Property Setter
	///
	void LabelModelTextObject::setTextHAlign( Qt::Alignment value )
	{
		if ( mTextHAlign != value )
		{
			mTextHAlign = value;
			update();
			emit changed();
		}
	}


	///
	/// TextVAlign Property Getter
	///
	Qt::Alignment LabelModelTextObject::textVAlign( void ) const
	{
		return mTextVAlign;
	}


	///
	/// TextVAlign Property Setter
	///
	void LabelModelTextObject::setTextVAlign( Qt::Alignment value )
	{
		if ( mTextVAlign != value )
		{
			mTextVAlign = value;
			update();
			emit changed();
		}
	}


	///
	/// TextLineSpacing Property Getter
	///
	double LabelModelTextObject::textLineSpacing( void ) const
	{
		return mTextLineSpacing;
	}


	///
	/// TextLineSpacing Property Setter
	///
	void LabelModelTextObject::setTextLineSpacing( double value )
	{
		if ( mTextLineSpacing != value )
		{
			mTextLineSpacing = value;
			update();
			emit changed();
		}
	}


	///
	/// Can Text Capability Implementation
	///
	bool LabelModelTextObject::canText()
	{
		return true;
	}


	///
	/// Draw shadow of object
	///
	void LabelModelTextObject::drawShadow( QPainter*      painter,
	                                       bool           inEditor,
	                                       merge::Record* record ) const
	{
		QColor textColor = mTextColorNode.color( record );

		if ( textColor.alpha() )
		{
			QColor shadowColor = mShadowColorNode.color( record );
			shadowColor.setAlphaF( mShadowOpacity );

			if ( inEditor )
			{
				drawTextInEditor( painter, shadowColor );
			}
			else
			{
				drawText( painter, shadowColor, record );
			}
		}
	}

	
	///
	/// Draw object itself
	///
	void LabelModelTextObject::drawObject( QPainter*      painter,
	                                       bool           inEditor,
	                                       merge::Record* record ) const
	{
		QColor textColor = mTextColorNode.color( record );

		if ( inEditor )
		{
			drawTextInEditor( painter, textColor );
		}
		else
		{
			drawText( painter, textColor, record );
		}
	}


	///
	/// Path to test for hover condition
	///
	QPainterPath LabelModelTextObject::hoverPath( double scale ) const
	{
		return mHoverPath;
	}


	///
	/// Size updated
	///
	void LabelModelTextObject::sizeUpdated()
	{
		update();
	}


	///
	/// Update cached information for editor view
	///
	void LabelModelTextObject::update()
	{
		QFont font;
		font.setFamily( mFontFamily );
		font.setPointSizeF( mFontSize );
		font.setWeight( mFontWeight );
		font.setItalic( mFontItalicFlag );
		font.setUnderline( mFontUnderlineFlag );

		QTextOption textOption;
		textOption.setAlignment( mTextHAlign );
		textOption.setWrapMode( QTextOption::WordWrap );

		QFontMetricsF fontMetrics( font );
		double dy = fontMetrics.lineSpacing() * mTextLineSpacing;

		QString displayText = mText.isEmpty() ? tr("Text") : mText;
		QTextDocument document( displayText );

		qDeleteAll( mEditorLayouts );
		mEditorLayouts.clear();

		// Pass #1 -- do initial layouts
		double x = 0;
		double y = 0;
		QRectF boundingRect;
		for ( int i = 0; i < document.blockCount(); i++ )
		{
			QTextLayout* layout = new QTextLayout( document.findBlockByNumber(i).text() );
		
			layout->setFont( font );
			layout->setTextOption( textOption );
			layout->setCacheEnabled(true);

			layout->beginLayout();
			for ( QTextLine l = layout->createLine(); l.isValid(); l = layout->createLine() )
			{
				l.setLineWidth( mW.pt() - 2*marginPts );
				l.setPosition( QPointF( x, y ) );
				y += dy;
			}
			layout->endLayout();

			mEditorLayouts.append( layout );

			boundingRect = layout->boundingRect().united( boundingRect );
		}
		double h = boundingRect.height();


		// Pass #2 -- adjust layout positions for vertical alignment and create hover path
		x = marginPts;
		switch ( mTextVAlign )
		{
		case Qt::AlignVCenter:
			y = mH.pt()/2 - h/2;
			break;
		case Qt::AlignBottom:
			y = mH.pt() - h - marginPts;
			break;
		default:
			y = marginPts;
			break;
		}
		QPainterPath hoverPath; // new empty hover path
		foreach ( QTextLayout* layout, mEditorLayouts )
		{
			for ( int j = 0; j < layout->lineCount(); j++ )
			{
				QTextLine l = layout->lineAt(j);
				l.setPosition( QPointF( x, y ) );
				y += dy;

				hoverPath.addRect( l.naturalTextRect() ); // add to new hover path
			}
		}
	
		mHoverPath = hoverPath; // save new hover path
	}


	///
	/// Draw text in editor from cached information
	///
	void LabelModelTextObject::drawTextInEditor( QPainter* painter, const QColor& color ) const
	{
		if ( mText.isEmpty() )
		{
			QColor mutedColor = color;
			mutedColor.setAlphaF( 0.5 * color.alphaF() );
			painter->setPen( QPen( mutedColor ) );
		}
		else
		{
			painter->setPen( QPen( color ) );
		}

		foreach ( QTextLayout* layout, mEditorLayouts )
		{
			layout->draw( painter, QPointF( 0, 0 ) );
		}
	}


	///
	/// Draw text in final printout or preview
	///
	void
	LabelModelTextObject::drawText( QPainter*      painter,
	                                const QColor&  color,
	                                merge::Record* record ) const
	{
		QFont font;
		font.setFamily( mFontFamily );
		font.setPointSizeF( mFontSize );
		font.setWeight( mFontWeight );
		font.setItalic( mFontItalicFlag );
		font.setUnderline( mFontUnderlineFlag );

		QTextOption textOption;
		textOption.setAlignment( mTextHAlign );
		textOption.setWrapMode( QTextOption::WordWrap );

		QFontMetricsF fontMetrics( font );
		double dy = fontMetrics.lineSpacing() * mTextLineSpacing;

		QTextDocument document( expandText( mText, record ) );

		QList<QTextLayout*> layouts;

		// Pass #1 -- do initial layouts
		double x = 0;
		double y = 0;
		QRectF boundingRect;
		for ( int i = 0; i < document.blockCount(); i++ )
		{
			QTextLayout* layout = new QTextLayout( document.findBlockByNumber(i).text() );
		
			layout->setFont( font );
			layout->setTextOption( textOption );
			layout->setCacheEnabled(true);

			layout->beginLayout();
			for ( QTextLine l = layout->createLine(); l.isValid(); l = layout->createLine() )
			{
				l.setLineWidth( mW.pt() - 2*marginPts );
				l.setPosition( QPointF( x, y ) );
				y += dy;
			}
			layout->endLayout();

			layouts.append( layout );

			boundingRect = layout->boundingRect().united( boundingRect );
		}
		double h = boundingRect.height();


		// Pass #2 -- adjust layout positions for vertical alignment and create hover path
		x = marginPts;
		switch ( mTextVAlign )
		{
		case Qt::AlignVCenter:
			y = mH.pt()/2 - h/2;
			break;
		case Qt::AlignBottom:
			y = mH.pt() - h - marginPts;
			break;
		default:
			y = marginPts;
			break;
		}
		foreach ( QTextLayout* layout, layouts )
		{
			for ( int j = 0; j < layout->lineCount(); j++ )
			{
				QTextLine l = layout->lineAt(j);
				l.setPosition( QPointF( x, y ) );
				y += dy;
			}
		}

		// Draw layouts
		painter->setPen( QPen( color ) );
		foreach ( QTextLayout* layout, layouts )
		{
			layout->draw( painter, QPointF( 0, 0 ) );
		}

		// Cleanup
		qDeleteAll( layouts );
	}


	///
	/// Expand text by replacing fields with their values from the given record
	///
	QString LabelModelTextObject::expandText( QString text, merge::Record* record ) const
	{
		if ( record )
		{
			foreach ( QString key, record->keys() )
			{
				// Special case: remove line when it contains only an empty field.
				// e.g. an optional ${ADDR2} line.  To bypass this case, include
				// whitespace at end of line.
				if ( record->value(key).isEmpty() )
				{
					QStringList v = text.split( '\n' );
					v.removeAll( "${"+key+"}" );
					text = v.join( '\n' );
				}

				// Nominal case: simple replacement
				text.replace( "${"+key+"}", record->value(key) );
			}
		}

		return text;
	}

}
