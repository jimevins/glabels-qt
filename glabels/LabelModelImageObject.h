/*  LabelModelImageObject.h
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

#ifndef LabelModelImageObject_h
#define LabelModelImageObject_h


#include "LabelModelObject.h"

#include <QSvgRenderer>


namespace glabels
{

	///
	/// Label Model Image Object
	///
	class LabelModelImageObject : public LabelModelObject
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	public:
		LabelModelImageObject();
		LabelModelImageObject( const LabelModelImageObject* object );
		~LabelModelImageObject() override;


		///////////////////////////////////////////////////////////////
		// Object duplication
		///////////////////////////////////////////////////////////////
		LabelModelImageObject* clone() const override;


		///////////////////////////////////////////////////////////////
		// Property Implementations
		///////////////////////////////////////////////////////////////
	public:
		//
		// Image Property: filenameNode
		//
		TextNode filenameNode() const override;
		void setFilenameNode( const TextNode& value ) override;

		//
		// Image Property: image
		//
		const QImage* image() const override;
		void setImage( const QImage& value ) override;
		void setImage( const QString& name, const QImage& value ) override;

		//
		// Image Property: svg
		//
		QByteArray svg() const override;
		void setSvg( const QString& name, const QByteArray& value ) override;

		//
		// Property: naturalSize
		//
		Size naturalSize() const override;
	

		///////////////////////////////////////////////////////////////
		// Capability Implementations
		///////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////
		// Drawing operations
		///////////////////////////////////////////////////////////////
	protected:
		void drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const override;
		void drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const override;
		QPainterPath hoverPath( double scale ) const override;


		///////////////////////////////////////////////////////////////
		// Private
		///////////////////////////////////////////////////////////////
		void loadImage();
		QImage* createShadowImage( const QColor& color ) const;
	

		///////////////////////////////////////////////////////////////
		// Private Members
		///////////////////////////////////////////////////////////////
	protected:
		TextNode       mFilenameNode;
		QImage*        mImage;
		QSvgRenderer*  mSvgRenderer;
		QByteArray     mSvg;

		static QImage* smDefaultImage;

	};

}


#endif // LabelModelImageObject_h
