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


		/////////////////////////////////
		// Lifecycle
		/////////////////////////////////
	public:
		LabelModel();
		virtual ~LabelModel() {}


		/////////////////////////////////
		// Signals
		/////////////////////////////////
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


		/////////////////////////////////
		// Properties
		/////////////////////////////////
	public:
		inline bool isModified() const;
		inline void clearModified();

		inline const QString& filename() const;
		inline void setFilename( const QString &filename );

		inline int compressionLevel() const;
		inline void setCompressionLevel( int compressionLevel );

		inline const libglabels::Template* tmplate() const;
		inline void setTmplate( const libglabels::Template* tmplate );

		inline bool rotate() const;
		inline void setRotate( bool rotate );

		inline double w() const;
		inline double h() const;

		inline const QList<LabelModelObject*>& objectList() const;

		
		/////////////////////////////////
		// Manage objects
		/////////////////////////////////
	public:
		void addObject( LabelModelObject* object );
		void deleteObject( LabelModelObject* object );


		/////////////////////////////////
		// Manipulate selection
		/////////////////////////////////
	public:
		void selectObject( LabelModelObject* object );
		void unselectObject( LabelModelObject* object );
		void selectAll();
		void unselectAll();
		void selectRegion( const LabelRegion& region );
		bool isSelectionEmpty();
		bool isSelectionAtomic();


		/////////////////////////////////
		// Get selected objects
		/////////////////////////////////
	public:
		QList<LabelModelObject*> getSelection();
		LabelModelObject* getFirstSelectedObject();


		/////////////////////////////////
		// Query selection capabilities
		/////////////////////////////////
	public:
		bool canSelectionText();
		bool canSelectionFill();
		bool canSelectionLineColor();
		bool canSelectionLineWidth();


		/////////////////////////////////
		// Operations on selections
		/////////////////////////////////
	public:
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
		void setSelectionFontFamily( const QString& fontFamily );
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

		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:
		void onObjectChanged( LabelModelObject* object );
		void onObjectMoved( LabelModelObject* object );


		/////////////////////////////////
		// Private data
		/////////////////////////////////
	private:
		bool                         mModified;
		QString                      mFilename;
		int                          mCompressionLevel;
		const libglabels::Template*  mTmplate;
		const libglabels::Frame*     mFrame;
		bool                         mRotate;

		QList<LabelModelObject*>     mObjectList;

	};



	/////////////////////////////////
	// INLINE METHODS
	/////////////////////////////////

	inline bool LabelModel::isModified() const
	{
		return mModified;
	}


	inline void LabelModel::clearModified()
	{
		mModified = false;
	}


	inline const QString& LabelModel::filename() const
	{
		return mFilename;
	}


	inline void LabelModel::setFilename( const QString &filename )
	{
		if ( mFilename != filename )
		{
			mFilename = filename;
			emit nameChanged();
		}
	}


	inline int LabelModel::compressionLevel() const
	{
		return mCompressionLevel;
	}


	inline void LabelModel::setCompressionLevel( int compressionLevel )
	{
		mCompressionLevel = compressionLevel;
	}


	inline const libglabels::Template* LabelModel::tmplate() const
	{
		return mTmplate;
	}


	inline void LabelModel::setTmplate( const libglabels::Template* tmplate )
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


	inline bool LabelModel::rotate() const
	{
		return mRotate;
	}


	inline void LabelModel::setRotate( bool rotate )
	{
		if (mRotate != rotate)
		{
			mRotate = rotate;
			mModified = true;
			emit changed();
			emit sizeChanged();
		}
	}


	inline double LabelModel::w() const
	{
		return mRotate ? mFrame->h() : mFrame->w();
	}


	inline double LabelModel::h() const
	{
		return mRotate ? mFrame->w() : mFrame->h();
	}


	inline const QList<LabelModelObject*>& LabelModel::objectList() const
	{
		return mObjectList;
	}


}

#endif // glabels_LabelModel_h
