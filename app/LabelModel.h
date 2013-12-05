/*  LabelModel.h
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

#ifndef glabels_LabelModel_h
#define glabels_LabelModel_h

#include <QObject>
#include <QList>

#include "libglabels/Template.h"
#include "LabelModelObject.h"


namespace glabels
{

	class LabelModel : public QObject
	{
		Q_OBJECT

	public:
		LabelModel();
		virtual ~LabelModel() {}

	signals:
		void changed();
		void nameChanged();
		void sizeChanged();
		void selectionChanged();
		void objectChanged( LabelModelObject* object );
		void objectMoved( LabelModelObject* object );
		void objectAdded( LabelModelObject* object );
		void objectDeleted( LabelModelObject* object );
		void objectToTop( LabelModelObject* object );
		void objectToBottom( LabelModelObject* object );

	public:
		bool isModified() const { return mModified; }
		void clearModified() { mModified = false; }

		const QString &filename() const { return mFilename; }
		void setFilename( const QString &filename )
		{
			if ( mFilename != filename )
			{
				mFilename = filename;
				emit nameChanged();
			}
		}

		int compressionLevel() const { return mCompressionLevel; }
		void setCompressionLevel( int compressionLevel ) { mCompressionLevel = compressionLevel; }

		const libglabels::Template* tmplate() const { return mTmplate; }
		void setTmplate( const libglabels::Template* tmplate )
		{
			if (mTmplate != tmplate)
			{
				mTmplate = tmplate;
				mFrame = tmplate->frames().first();
				mModified = true;
				emit changed();
				emit sizeChanged();
			}
		}

		bool rotate() const { return mRotate; }
		void setRotate( bool rotate )
		{
			if (mRotate != rotate)
			{
				mRotate = rotate;
				mModified = true;
				emit changed();
				emit sizeChanged();
			}
		}

		double w() const { return mRotate ? mFrame->h() : mFrame->w(); }
		double h() const { return mRotate ? mFrame->w() : mFrame->h(); }


		void addObject( LabelModelObject* object );

		void deleteObject( LabelModelObject* object );


		void selectObject( LabelModelObject* object );

		void unselectObject( LabelModelObject* object );

		void selectAll();

		void unselectAll();

		void selectRegion( const LabelRegion &region );

		bool isSelectionEmpty();

		bool isSelectionAtomic();


		QList<LabelModelObject*> getSelection();

		LabelModelObject* getFirstSelectedObject();


		bool canSelectionText();
		bool canSelectionFill();
		bool canSelectionLineColor();
		bool canSelectionLineWidth();


		void deleteSelection();
		void raiseSelectionToTop();
		void lowerSelectionToBottom();
		void rotateSelection( double thetaDegs );
		void rotateSelectionLeft();
		void rotateSelectionRight();
		void flipSelectionHoriz();
		void flipSelectionVert();
		void alignSelectionLeft();
		void alignSelectionRight();
		void alignSelectionHCenter();
		void alignSelectionTop();
		void alignSelectionBottom();
		void alignSelectionVCenter();
		void centerSelectionHoriz();
		void centerSelectionVert();
		void moveSelection( double dx, double dy );
		void setSelectionFontFamily( const QString &fontFamily );
		void setSelectionFontSize( double fontSize );
		void setSelectionFontWeight( QFont::Weight fontWeight );
		void setSelectionFontItalicFlag( bool fontItalicFlag );
		void setSelectionTextHAlign( Qt::Alignment textHAlign );
		void setSelectionTextVAlign( Qt::Alignment textVAlign );
		void setSelectionTextLineSpacing( double textLineSpacing );
		void setSelectionTextColorNode( ColorNode textColorNode );
		void setSelectionLineWidth( double lineWidth );
		void setSelectionLineColorNode( ColorNode lineColorNode );
		void setSelectionFillColorNode( ColorNode fillColorNode );


	private slots:
		void onObjectChanged( LabelModelObject* object );
		void onObjectMoved( LabelModelObject* object );


	private:

		QList<LabelModelObject*> mObjectList;

		bool                         mModified;
		QString                      mFilename;
		int                          mCompressionLevel;
		const libglabels::Template*  mTmplate;
		const libglabels::Frame*     mFrame;
		bool                         mRotate;
	};

}

#endif // glabels_LabelModel_h
